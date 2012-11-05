#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <malloc.h>
#include <string.h>

void main (int argc, char **argv)
 {
   void delete_tree(void);

   char buffer[128];

   char drive[_MAX_DRIVE], directory[_MAX_DIR],
      filename[_MAX_FNAME], ext[_MAX_EXT];

   if (argc < 2)
     {
       printf ("Syntax error\n");
       exit(0);
     }


   _splitpath (argv[1], drive, directory, filename, ext);
   getcwd (buffer, sizeof(buffer));

   if (drive[0] == NULL)
     {
       _splitpath (buffer, drive, directory, filename, ext);
       strcpy (buffer, directory);
       strcat (buffer, filename);
       strcat (buffer, ext);
     }
   else
     { 
       printf ("Do not specify drive letter\n");
       exit (1);
     }

   if (strcmpi(buffer, argv[1]) == 0)
     {
       printf ("Cannot delete current directory\n");
       exit (1);
     }
		  
   getcwd (directory, 64);

   if (chdir (argv[1]))
     printf ("Invalid directory %s\n", argv[1]);
   else
     delete_tree(); 

   chdir (directory);
   rmdir (argv[1]);
 }

union REGS inregs, outregs;
struct SREGS segs;

void delete_tree(void)
 {
   struct find_t fileinfo;
	
   int result;
	
   char far *buffer;

   unsigned dta_seg, dta_ofs;

   result = _dos_findfirst("*.*", 16, &fileinfo);

   inregs.h.ah = 0x2f;
   intdosx (&inregs, &outregs, &segs);
   dta_seg = segs.es;
   dta_ofs = outregs.x.bx;

   while (! result)
    {
      if ((fileinfo.attrib & 16) && (fileinfo.name[0] != '.'))
	{
	   buffer = _fmalloc (256);
	   if (buffer == NULL)
	     {
	       printf ("Insufficient memory\n");
	       exit(1);    
	     }
	   inregs.h.ah = 0x1A;
	   inregs.x.dx = FP_SEG(buffer);
	   segread(&segs);
	   intdosx (&inregs, &outregs, &segs);
		
	   chdir (fileinfo.name);
	   delete_tree(); 
	   chdir ("..");

	   inregs.h.ah = 0x1A;
	   inregs.x.dx = dta_ofs;
	   segs.ds = dta_seg;
	   _ffree (buffer);
	   rmdir (fileinfo.name);
	}
      else if (fileinfo.name[0] != '.')
	{
	   _dos_setfileattr(fileinfo.name, 0);
	   remove (fileinfo.name);
	}
	  
      result = _dos_findnext (&fileinfo);
    }
 }
