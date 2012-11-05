/*
 * convert elf to pkg
 */
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define MAX_FILEPATH    128

/* global sections name table */
char *name_table = NULL;
/* global name table for the symbol table */
char *sym_name_table = NULL;

int elf_valid(char *image)
{
	unsigned char *magic;

	magic = (unsigned char *)image;

	if ((magic[0] == 0x7F) && (strncmp((magic+1), "ELF", 3) == 0))
		return 1;
	else
		return 0;
}

/* Loads the string table section pointed to by the ELF header's
 * e_shstrndx field and also loads the symbol table's string table */
void elf_load_names(Elf32_Ehdr *header, char *image)
{
    Elf32_Shdr *ptr;
    int i;
    
    /* load the section names string table */
    ptr = (Elf32_Shdr *)(image + header->e_shoff);
    
    for (i=0;i < header->e_shstrndx; i++)
      ptr++;

	name_table = (char *)(image + ptr->sh_offset);

    /* load the general string table */
    ptr = (Elf32_Shdr *)(image + header->e_shoff);
    for (i=0; i < (int)header->e_shnum; i++)
	{
		if (strncmp((name_table+ptr->sh_name), ".strtab", 7) == 0)
		{
			sym_name_table = (char *)(image + ptr->sh_offset);
			break;
		}
		else
		{
			ptr++;
		}
    }
    
    if (sym_name_table == NULL)
	{
		fprintf(stdout, "\nNo symbol table defined!\n");
    }
}

/* Function that returns a static string describing a symbol's type.
 * DO NOT FREE THE RETURNED POINTER! */
char *elf_get_symbol_type(Elf32_Sym *symbol)
{
    static char sym_type[32];
    
    switch (ELF32_ST_TYPE(symbol->st_info))
	{
    case STT_NOTYPE:
		strncpy(sym_type, "No type", 32);
		break;
	case STT_OBJECT:
		strncpy(sym_type, "Data object", 32);
		break;
	case STT_FUNC:
		strncpy(sym_type, "Function", 32);
		break;
	case STT_SECTION:
		strncpy(sym_type, "Section", 32);
		break;
	case STT_FILE:
		strncpy(sym_type, "File", 32);
		break;
	default:
		sprintf(sym_type, "Unknown");
		break;
    }

    return sym_type;
}

/* Procedure to display information about a program symbol */
void elf_dump_symbol(Elf32_Sym *symbol, int n)
{
    if (symbol == NULL) return;
    
    if (symbol->st_name != 0 && sym_name_table != NULL)
	{
		if ( ELF32_ST_TYPE(symbol->st_info) == STT_OBJECT )
		{
		}
		else if ( ELF32_ST_TYPE(symbol->st_info) == STT_FUNC )
		{
			fprintf(stdout, "\tfinc_insert_func(self, \"%s\", %s, \"pointer\", NULL);\n", sym_name_table + symbol->st_name, sym_name_table + symbol->st_name);
		}
    }
}

void elf_extern_symbol(Elf32_Sym* symbol, int n)
{
    if (symbol == NULL) return;
    
    if (symbol->st_name != 0 && sym_name_table != NULL)
	{
		if ( ELF32_ST_TYPE(symbol->st_info) == STT_OBJECT )
		{
		}
		else if ( ELF32_ST_TYPE(symbol->st_info) == STT_FUNC )
		{
			fprintf(stdout, "extern void* %s();\n", sym_name_table + symbol->st_name);
		}
    }
}

/* reads and displays information from the symbol table */
void elf_display_symbols(Elf32_Ehdr *header, char *image)
{
    Elf32_Shdr *sectab;                /* section table offset */
    Elf32_Half sectab_size;            /* section table size */
    int num_syms;						/* number of symbols */
    int i = 0;
    Elf32_Shdr *ptr;                   /* segment table buffer */
    Elf32_Shdr *sym_tab;		       /* current symbol */
    Elf32_Sym *symbol;

    /* if no string table can be found for the symbols then die */
    if (sym_name_table == NULL)
    {
		fprintf(stdout, "Symbol table not found, possibly a stripped"
			" binary.\n");
		return;
    }
    
    /* find the symbol table section */
    sectab = (Elf32_Shdr *)(image + header->e_shoff);
    sectab_size = (header->e_shnum * header->e_shentsize);
        
    ptr = (Elf32_Shdr *)sectab;
    while (ptr->sh_type != SHT_SYMTAB)
	{
		ptr++;
    }

    num_syms = (ptr->sh_size) / (ptr->sh_entsize);
    sym_tab = (Elf32_Shdr *)(image + ptr->sh_offset);
    
	(void *)symbol = (void *)sym_tab;
    for (i=0; i<num_syms; i++)
	{
		elf_extern_symbol(symbol, i);
		symbol++;
    }

	fprintf(stdout, "\n");
    (void *)symbol = (void *)sym_tab;
	for (i=0; i<num_syms; i++)
	{
		elf_dump_symbol(symbol, i);
		symbol++;
    }
}

void usage()
{
}

int main(int argc, char** argv)
{
    Elf32_Ehdr *elf_head;	       /* ELF header structure */
    char elf_path[MAX_FILEPATH];       /* path for the file */
    int elf_fp; 		       /* fd for the file */
    struct stat elf_stat;	       /* used with stat() */
    char *elf_image;		       /* used with mmap() */

    if (argc < 3)
	{
		usage();
    }

    /* 
     * get the filename and attempt to open it
     */
    strncpy(elf_path, argv[1], MAX_FILEPATH);
    
    if ((elf_fp = open(elf_path, O_RDONLY)) < 0)
	{
		fprintf(stderr, "Failed opening\n" );
		exit(1);
    }

    /*
     * use stat() to get the file size
     */
    if (stat(elf_path, &elf_stat) < 0)
	{
		fprintf(stderr, "Failed determining file size!\n");
		exit(1);
    }

    /*
     * attempt to mmap() the file to an address
     */
    if ((elf_image = mmap(0, elf_stat.st_size, PROT_READ, MAP_PRIVATE,
		elf_fp, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "Failed mapping ELF file to memory!\n" );
		exit(1);
    }
    
    /* 
     * check it's a valid ELF file, close and exit if not
     */
    if (!elf_valid(elf_image))
	{
		fprintf(stderr, "%s is not a valid ELF file!\n", elf_path);
		exit(1);
    }

    /* 
     * fill the header structure
     */
    elf_head = (Elf32_Ehdr *)elf_image;

    /*
     * load the string table pointed out by the segment header
     */
    elf_load_names(elf_head, elf_image);

	elf_display_symbols(elf_head, elf_image);

    if (munmap(elf_image, elf_stat.st_size) < 0)
	{
		fprintf(stderr, "Failed unmapping ELF file!\n");
		exit(1);
    }

	return 0;
}
