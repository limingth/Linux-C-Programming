#include <stdio.h>

#include <finc/finclib.h>
#include <finc/finapi/fincstring.h>
#include <finc/finapi/fincarray.h>
#include <finc/finapi/netapi.h>

int float_test(float a)
{
	printf("%f\n", a);

	return 0;
}

void test_init(FinC* self)
{
	finc_insert_func(self, "ftest", float_test, "int", "float", "a", NULL);
}

void stdio_init(FinC* self)
{
/*
	finc_insert_var (self, "pointer", "stdin", &stdin);
	finc_insert_var (self, "pointer", "stdout", &stdout);
	finc_insert_var (self, "pointer", "stderr", &stderr);
*/
	finc_insert_func(self, "printf", printf, "int", "string", "format", "...", NULL);
	finc_insert_func(self, "sprintf", sprintf, "int", "string", "str", "string", "format", "...", NULL);
	finc_insert_func(self, "snprintf", snprintf, "int", "string", "str", "int", "size", "string", "format", "...", NULL);
	finc_insert_func(self, "scanf", scanf, "int", "string", "format", "...", NULL);
	finc_insert_func(self, "sscanf", sscanf, "int", "string", "str", "string", "format", "...", NULL);
}

#ifdef FILE_IO
void fileio_init(FinC* self)
{
	finc_insert_func(self, "fopen", fopen, "pointer", "string", "filename", "string", "mode", NULL);
	finc_insert_func(self, "fread", fread, "int", "pointer", "buf", "int", "size", "int", "nmemb", "pointer", "fd", NULL);
	finc_insert_func(self, "fwrite", fread, "int", "pointer", "buf", "int", "size", "int", "nmemb", "pointer", "fd", NULL);
	finc_insert_func(self, "feof", feof, "bool", "pointer", "fd", NULL);
	finc_insert_func(self, "fseek", fseek, "int", "pointer", "fd", "int", "offset", "int", "origin", NULL);
	finc_insert_func(self, "ftell", ftell, "int", "pointer", "fd", NULL);
	finc_insert_func(self, "fprintf", fprintf, "void", "pointer", "fd", "string", "format", "...", NULL);
	finc_insert_func(self, "fscanf", fscanf, "void", "pointer", "fd", "string", "format", "...", NULL);
	finc_insert_func(self, "fclose", fclose, "int", "pointer", "fd", NULL);

	finc_insert_func(self, "fputc", fputc, "int", "char", "c", "pointer", "fd", NULL);
}
#endif

void help()
{
	printf("Usage: finc file.fc\n");
}

void copyright()
{
	printf("FinC -- a programming langauge with C-like syntax, version 0.3.2\n");
	printf("2004.8 release under GPL.\n");
	printf("2002 - 2005 (C)opyright by Xiong puxiang(bernard.xiong@gmail.com).\n");

	fflush(stdout);
}

Bool is_quit(unsigned char* line)
{
    char buf[5], *p;/*quit*/
    int i;
    
    p = buf;
    i = 0;
    while ( line && i<5 )
    {
		if (isalpha(line[i]))
		{
			*p++ = line[i];
		}
		i++;
    }
    *p = '\0';

    if (strcmp(buf, "q") == 0) return TRUE;
    if (strcmp(buf, "quit") == 0) return TRUE;

    return FALSE;
}

int main (int argc, char** argv)
{
    FinC* finc_env;
    unsigned char line[256];
    
    finc_env = finc_init();
    stdio_init(finc_env);
	test_init(finc_env);
#ifdef FILE_IO
	fileio_init(finc_env);
#endif
#ifdef USING_STRING_API	
    finc_string_init(finc_env);
#endif
#ifdef USING_ARRAY_API	
    finc_array_init(finc_env);
#endif
#ifdef USING_NET_API    
	net_init(finc_env);
#endif

    copyright();

#ifdef USING_FILE
	if (argc > 1)
	{
		finc_run_script(finc_env, argv[1]);
	}
    else
#endif
	{
		while ( 1 )
		{
			printf("finsh>>");
			fflush(stdout);

			memset(line, 0, sizeof(line));
			fgets(line, sizeof(line), stdin);
			if (is_quit(line))break;
			finc_run_string(finc_env, line);
			finc_context_error_clear( g_finc_context );
		}
    }
    
    finc_exit(finc_env);
    mem_debug();
    return 0;
}
