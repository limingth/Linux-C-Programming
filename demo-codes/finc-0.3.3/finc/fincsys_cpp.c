# 1 "fincsys.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "fincsys.c"
# 1 "../include/finc/fincsys.h" 1



# 1 "../include/tiny/global.h" 1



# 1 "D:/Bernard/DDE/mingw/include/stdio.h" 1 3
# 35 "D:/Bernard/DDE/mingw/include/stdio.h" 3
# 1 "D:/Bernard/DDE/mingw/include/_mingw.h" 1 3
# 36 "D:/Bernard/DDE/mingw/include/stdio.h" 2 3






# 1 "D:/Bernard/DDE/mingw/include/stddef.h" 1 3





# 1 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stddef.h" 1 3
# 215 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stddef.h" 3
typedef unsigned int size_t;
# 327 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stddef.h" 3
typedef short unsigned int wchar_t;
# 356 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stddef.h" 3
typedef short unsigned int wint_t;
# 7 "D:/Bernard/DDE/mingw/include/stddef.h" 2 3
# 43 "D:/Bernard/DDE/mingw/include/stdio.h" 2 3

# 1 "D:/Bernard/DDE/mingw/include/stdarg.h" 1 3





# 1 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stdarg.h" 1 3
# 44 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stdarg.h" 3
typedef __builtin_va_list __gnuc_va_list;
# 7 "D:/Bernard/DDE/mingw/include/stdarg.h" 2 3
# 45 "D:/Bernard/DDE/mingw/include/stdio.h" 2 3
# 151 "D:/Bernard/DDE/mingw/include/stdio.h" 3
typedef struct _iobuf
{
        char* _ptr;
        int _cnt;
        char* _base;
        int _flag;
        int _file;
        int _charbuf;
        int _bufsiz;
        char* _tmpfname;
} FILE;
# 176 "D:/Bernard/DDE/mingw/include/stdio.h" 3
__attribute__((dllimport)) FILE _iob[];
# 191 "D:/Bernard/DDE/mingw/include/stdio.h" 3
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) fopen (const char*, const char*);
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) freopen (const char*, const char*, FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) fflush (FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) fclose (FILE*);

__attribute__((dllimport)) int __attribute__((__cdecl__)) remove (const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) rename (const char*, const char*);
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) tmpfile (void);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) tmpnam (char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _tempnam (const char*, const char*);


__attribute__((dllimport)) char* __attribute__((__cdecl__)) tempnam (const char*, const char*);


__attribute__((dllimport)) int __attribute__((__cdecl__)) setvbuf (FILE*, char*, int, size_t);

__attribute__((dllimport)) void __attribute__((__cdecl__)) setbuf (FILE*, char*);





__attribute__((dllimport)) int __attribute__((__cdecl__)) fprintf (FILE*, const char*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) printf (const char*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) sprintf (char*, const char*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _snprintf (char*, size_t, const char*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) vfprintf (FILE*, const char*, char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) vprintf (const char*, char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) vsprintf (char*, const char*, char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _vsnprintf (char*, size_t, const char*, char*);


int __attribute__((__cdecl__)) snprintf(char* s, size_t n, const char* format, ...);
extern __inline__ int __attribute__((__cdecl__))
vsnprintf (char* s, size_t n, const char* format, char* arg)
  { return _vsnprintf ( s, n, format, arg); }
int __attribute__((__cdecl__)) vscanf (const char * __restrict__, char*);
int __attribute__((__cdecl__)) vfscanf (FILE * __restrict__, const char * __restrict__,
                     char*);
int __attribute__((__cdecl__)) vsscanf (const char * __restrict__,
                     const char * __restrict__, char*);






__attribute__((dllimport)) int __attribute__((__cdecl__)) fscanf (FILE*, const char*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) scanf (const char*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) sscanf (const char*, const char*, ...);




__attribute__((dllimport)) int __attribute__((__cdecl__)) fgetc (FILE*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) fgets (char*, int, FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) fputc (int, FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) fputs (const char*, FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) getc (FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) getchar (void);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) gets (char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) putc (int, FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) putchar (int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) puts (const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) ungetc (int, FILE*);





__attribute__((dllimport)) size_t __attribute__((__cdecl__)) fread (void*, size_t, size_t, FILE*);
__attribute__((dllimport)) size_t __attribute__((__cdecl__)) fwrite (const void*, size_t, size_t, FILE*);





__attribute__((dllimport)) int __attribute__((__cdecl__)) fseek (FILE*, long, int);
__attribute__((dllimport)) long __attribute__((__cdecl__)) ftell (FILE*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) rewind (FILE*);
# 295 "D:/Bernard/DDE/mingw/include/stdio.h" 3
typedef long long fpos_t;




__attribute__((dllimport)) int __attribute__((__cdecl__)) fgetpos (FILE*, fpos_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) fsetpos (FILE*, const fpos_t*);





__attribute__((dllimport)) void __attribute__((__cdecl__)) clearerr (FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) feof (FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) ferror (FILE*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) perror (const char*);






__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) _popen (const char*, const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _pclose (FILE*);


__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) popen (const char*, const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) pclose (FILE*);





__attribute__((dllimport)) int __attribute__((__cdecl__)) _flushall (void);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _fgetchar (void);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _fputchar (int);
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) _fdopen (int, const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _fileno (FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _fcloseall(void);

__attribute__((dllimport)) int __attribute__((__cdecl__)) _getmaxstdio(void);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _setmaxstdio(int);



__attribute__((dllimport)) int __attribute__((__cdecl__)) fgetchar (void);
__attribute__((dllimport)) int __attribute__((__cdecl__)) fputchar (int);
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) fdopen (int, const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) fileno (FILE*);
# 352 "D:/Bernard/DDE/mingw/include/stdio.h" 3
__attribute__((dllimport)) int __attribute__((__cdecl__)) fwprintf (FILE*, const wchar_t*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) wprintf (const wchar_t*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) swprintf (wchar_t*, const wchar_t*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _snwprintf (wchar_t*, size_t, const wchar_t*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) vfwprintf (FILE*, const wchar_t*, char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) vwprintf (const wchar_t*, char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) vswprintf (wchar_t*, const wchar_t*, char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _vsnwprintf (wchar_t*, size_t, const wchar_t*, char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) fwscanf (FILE*, const wchar_t*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) wscanf (const wchar_t*, ...);
__attribute__((dllimport)) int __attribute__((__cdecl__)) swscanf (const wchar_t*, const wchar_t*, ...);
__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) fgetwc (FILE*);
__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) fputwc (wchar_t, FILE*);
__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) ungetwc (wchar_t, FILE*);


__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) fgetws (wchar_t*, int, FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) fputws (const wchar_t*, FILE*);
__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) getwc (FILE*);
__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) getwchar (void);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _getws (wchar_t*);
__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) putwc (wint_t, FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _putws (const wchar_t*);
__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) putwchar (wint_t);
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) _wfdopen(int, wchar_t *);
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) _wfopen (const wchar_t*, const wchar_t*);
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) _wfreopen (const wchar_t*, const wchar_t*, FILE*);
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) _wfsopen (const wchar_t*, const wchar_t*, int);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wtmpnam (wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wtempnam (const wchar_t*, const wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _wrename (const wchar_t*, const wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _wremove (const wchar_t*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) _wperror (const wchar_t*);
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) _wpopen (const wchar_t*, const wchar_t*);



int __attribute__((__cdecl__)) snwprintf (wchar_t* s, size_t n, const wchar_t* format, ...);
extern __inline__ int __attribute__((__cdecl__))
vsnwprintf (wchar_t* s, size_t n, const wchar_t* format, char* arg)
  { return _vsnwprintf ( s, n, format, arg);}
int __attribute__((__cdecl__)) vwscanf (const wchar_t * __restrict__, char*);
int __attribute__((__cdecl__)) vfwscanf (FILE * __restrict__,
                       const wchar_t * __restrict__, char*);
int __attribute__((__cdecl__)) vswscanf (const wchar_t * __restrict__,
                       const wchar_t * __restrict__, char*);
# 406 "D:/Bernard/DDE/mingw/include/stdio.h" 3
__attribute__((dllimport)) FILE* __attribute__((__cdecl__)) wpopen (const wchar_t*, const wchar_t*);






__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) _fgetwchar (void);
__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) _fputwchar (wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _getw (FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _putw (int, FILE*);


__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) fgetwchar (void);
__attribute__((dllimport)) wint_t __attribute__((__cdecl__)) fputwchar (wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) getw (FILE*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) putw (int, FILE*);
# 5 "../include/tiny/global.h" 2
# 1 "D:/Bernard/DDE/mingw/include/stdlib.h" 1 3
# 38 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
# 1 "D:/Bernard/DDE/mingw/include/stddef.h" 1 3





# 1 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stddef.h" 1 3
# 7 "D:/Bernard/DDE/mingw/include/stddef.h" 2 3
# 39 "D:/Bernard/DDE/mingw/include/stdlib.h" 2 3
# 86 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
extern int _argc;
extern char** _argv;




extern int* __attribute__((__cdecl__)) __p___argc(void);
extern char*** __attribute__((__cdecl__)) __p___argv(void);
extern wchar_t*** __attribute__((__cdecl__)) __p___wargv(void);
# 127 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
   __attribute__((dllimport)) int __mb_cur_max;
# 152 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
 __attribute__((dllimport)) int* __attribute__((__cdecl__)) _errno(void);


 __attribute__((dllimport)) int* __attribute__((__cdecl__)) __doserrno(void);







  extern __attribute__((dllimport)) char *** __attribute__((__cdecl__)) __p__environ(void);
  extern __attribute__((dllimport)) wchar_t *** __attribute__((__cdecl__)) __p__wenviron(void);
# 186 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
  __attribute__((dllimport)) int _sys_nerr;
# 210 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
__attribute__((dllimport)) char* _sys_errlist[];
# 224 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
extern __attribute__((dllimport)) unsigned __attribute__((__cdecl__)) int* __p__osver(void);
extern __attribute__((dllimport)) unsigned __attribute__((__cdecl__)) int* __p__winver(void);
extern __attribute__((dllimport)) unsigned __attribute__((__cdecl__)) int* __p__winmajor(void);
extern __attribute__((dllimport)) unsigned __attribute__((__cdecl__)) int* __p__winminor(void);







__attribute__((dllimport)) unsigned int _osver;
__attribute__((dllimport)) unsigned int _winver;
__attribute__((dllimport)) unsigned int _winmajor;
__attribute__((dllimport)) unsigned int _winminor;
# 275 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
__attribute__((dllimport)) char** __attribute__((__cdecl__)) __p__pgmptr(void);

__attribute__((dllimport)) wchar_t** __attribute__((__cdecl__)) __p__wpgmptr(void);
# 308 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
__attribute__((dllimport)) int _fmode;
# 324 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
__attribute__((dllimport)) double __attribute__((__cdecl__)) atof (const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) atoi (const char*);
__attribute__((dllimport)) long __attribute__((__cdecl__)) atol (const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _wtoi (const wchar_t *);
__attribute__((dllimport)) long __attribute__((__cdecl__)) _wtol (const wchar_t *);

__attribute__((dllimport)) double __attribute__((__cdecl__)) strtod (const char*, char**);

extern __inline__ float __attribute__((__cdecl__)) strtof (const char *nptr, char **endptr)
  { return (strtod (nptr, endptr));}
long double __attribute__((__cdecl__)) strtold (const char * __restrict__, char ** __restrict__);


__attribute__((dllimport)) long __attribute__((__cdecl__)) strtol (const char*, char**, int);
__attribute__((dllimport)) unsigned long __attribute__((__cdecl__)) strtoul (const char*, char**, int);



__attribute__((dllimport)) double __attribute__((__cdecl__)) wcstod (const wchar_t*, wchar_t**);

extern __inline__ float __attribute__((__cdecl__)) wcstof( const wchar_t *nptr, wchar_t **endptr)
{ return (wcstod(nptr, endptr)); }
long double __attribute__((__cdecl__)) wcstold (const wchar_t * __restrict__, wchar_t ** __restrict__);


__attribute__((dllimport)) long __attribute__((__cdecl__)) wcstol (const wchar_t*, wchar_t**, int);
__attribute__((dllimport)) unsigned long __attribute__((__cdecl__)) wcstoul (const wchar_t*, wchar_t**, int);



__attribute__((dllimport)) size_t __attribute__((__cdecl__)) wcstombs (char*, const wchar_t*, size_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) wctomb (char*, wchar_t);

__attribute__((dllimport)) int __attribute__((__cdecl__)) mblen (const char*, size_t);
__attribute__((dllimport)) size_t __attribute__((__cdecl__)) mbstowcs (wchar_t*, const char*, size_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) mbtowc (wchar_t*, const char*, size_t);

__attribute__((dllimport)) int __attribute__((__cdecl__)) rand (void);
__attribute__((dllimport)) void __attribute__((__cdecl__)) srand (unsigned int);

__attribute__((dllimport)) void* __attribute__((__cdecl__)) calloc (size_t, size_t);
__attribute__((dllimport)) void* __attribute__((__cdecl__)) malloc (size_t);
__attribute__((dllimport)) void* __attribute__((__cdecl__)) realloc (void*, size_t);
__attribute__((dllimport)) void __attribute__((__cdecl__)) free (void*);

__attribute__((dllimport)) void __attribute__((__cdecl__)) abort (void) ;
__attribute__((dllimport)) void __attribute__((__cdecl__)) exit (int) ;


int __attribute__((__cdecl__)) atexit (void (*)(void));

__attribute__((dllimport)) int __attribute__((__cdecl__)) system (const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) getenv (const char*);


__attribute__((dllimport)) void* __attribute__((__cdecl__)) bsearch (const void*, const void*, size_t, size_t,
                                 int (*)(const void*, const void*));
__attribute__((dllimport)) void __attribute__((__cdecl__)) qsort (void*, size_t, size_t,
                                 int (*)(const void*, const void*));

__attribute__((dllimport)) int __attribute__((__cdecl__)) abs (int);
__attribute__((dllimport)) long __attribute__((__cdecl__)) labs (long);
# 395 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

__attribute__((dllimport)) div_t __attribute__((__cdecl__)) div (int, int);
__attribute__((dllimport)) ldiv_t __attribute__((__cdecl__)) ldiv (long, long);







__attribute__((dllimport)) void __attribute__((__cdecl__)) _beep (unsigned int, unsigned int);
__attribute__((dllimport)) void __attribute__((__cdecl__)) _seterrormode (int);
__attribute__((dllimport)) void __attribute__((__cdecl__)) _sleep (unsigned long);

__attribute__((dllimport)) void __attribute__((__cdecl__)) _exit (int) ;



typedef int (* _onexit_t)(void);
_onexit_t __attribute__((__cdecl__)) _onexit( _onexit_t );

__attribute__((dllimport)) int __attribute__((__cdecl__)) _putenv (const char*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) _searchenv (const char*, const char*, char*);


__attribute__((dllimport)) char* __attribute__((__cdecl__)) _ecvt (double, int, int*, int*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _fcvt (double, int, int*, int*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _gcvt (double, int, char*);

__attribute__((dllimport)) void __attribute__((__cdecl__)) _makepath (char*, const char*, const char*, const char*, const char*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) _splitpath (const char*, char*, char*, char*, char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _fullpath (char*, const char*, size_t);

__attribute__((dllimport)) char* __attribute__((__cdecl__)) _itoa (int, char*, int);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _ltoa (long, char*, int);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _ultoa(unsigned long, char*, int);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _itow (int, wchar_t*, int);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _ltow (long, wchar_t*, int);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _ultow (unsigned long, wchar_t*, int);


__attribute__((dllimport)) __int64 __attribute__((__cdecl__)) _atoi64(const char *);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _i64toa(__int64, char *, int);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _ui64toa(unsigned __int64, char *, int);
__attribute__((dllimport)) __int64 __attribute__((__cdecl__)) _wtoi64(const wchar_t *);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _i64tow(__int64, wchar_t *, int);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _ui64tow(unsigned __int64, wchar_t *, int);

__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wgetenv(const wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _wputenv(const wchar_t*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) _wsearchenv(const wchar_t*, const wchar_t*, wchar_t*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) _wmakepath(wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) _wsplitpath (const wchar_t*, wchar_t*, wchar_t*, wchar_t*, wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wfullpath (wchar_t*, const wchar_t*, size_t);

__attribute__((dllimport)) unsigned int __attribute__((__cdecl__)) _rotl(unsigned int, int);
__attribute__((dllimport)) unsigned int __attribute__((__cdecl__)) _rotr(unsigned int, int);
__attribute__((dllimport)) unsigned long __attribute__((__cdecl__)) _lrotl(unsigned long, int);
__attribute__((dllimport)) unsigned long __attribute__((__cdecl__)) _lrotr(unsigned long, int);




__attribute__((dllimport)) int __attribute__((__cdecl__)) putenv (const char*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) searchenv (const char*, const char*, char*);

__attribute__((dllimport)) char* __attribute__((__cdecl__)) itoa (int, char*, int);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) ltoa (long, char*, int);


__attribute__((dllimport)) char* __attribute__((__cdecl__)) ecvt (double, int, int*, int*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) fcvt (double, int, int*, int*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) gcvt (double, int, char*);
# 480 "D:/Bernard/DDE/mingw/include/stdlib.h" 3
void __attribute__((__cdecl__)) _Exit(int) ;

extern __inline__ void __attribute__((__cdecl__)) _Exit(int status)
        { _exit(status); }


typedef struct { long long quot, rem; } lldiv_t;

lldiv_t __attribute__((__cdecl__)) lldiv (long long, long long);

extern __inline__ long long __attribute__((__cdecl__)) llabs(long long _j)
  {return (_j >= 0 ? _j : -_j);}

long long __attribute__((__cdecl__)) strtoll (const char* __restrict__, char** __restrict, int);
unsigned long long __attribute__((__cdecl__)) strtoull (const char* __restrict__, char** __restrict__, int);


long long __attribute__((__cdecl__)) atoll (const char *);


long long __attribute__((__cdecl__)) wtoll (const wchar_t *);
char* __attribute__((__cdecl__)) lltoa (long long, char *, int);
char* __attribute__((__cdecl__)) ulltoa (unsigned long long , char *, int);
wchar_t* __attribute__((__cdecl__)) lltow (long long, wchar_t *, int);
wchar_t* __attribute__((__cdecl__)) ulltow (unsigned long long, wchar_t *, int);


extern __inline__ long long __attribute__((__cdecl__)) atoll (const char * _c)
        { return _atoi64 (_c); }
extern __inline__ char* __attribute__((__cdecl__)) lltoa (long long _n, char * _c, int _i)
        { return _i64toa (_n, _c, _i); }
extern __inline__ char* __attribute__((__cdecl__)) ulltoa (unsigned long long _n, char * _c, int _i)
        { return _ui64toa (_n, _c, _i); }
extern __inline__ long long __attribute__((__cdecl__)) wtoll (const wchar_t * _w)
        { return _wtoi64 (_w); }
extern __inline__ wchar_t* __attribute__((__cdecl__)) lltow (long long _n, wchar_t * _w, int _i)
        { return _i64tow (_n, _w, _i); }
extern __inline__ wchar_t* __attribute__((__cdecl__)) ulltow (unsigned long long _n, wchar_t * _w, int _i)
        { return _ui64tow (_n, _w, _i); }
# 6 "../include/tiny/global.h" 2
# 1 "D:/Bernard/DDE/mingw/include/string.h" 1 3
# 40 "D:/Bernard/DDE/mingw/include/string.h" 3
# 1 "D:/Bernard/DDE/mingw/include/stddef.h" 1 3





# 1 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stddef.h" 1 3
# 7 "D:/Bernard/DDE/mingw/include/stddef.h" 2 3
# 41 "D:/Bernard/DDE/mingw/include/string.h" 2 3
# 52 "D:/Bernard/DDE/mingw/include/string.h" 3
__attribute__((dllimport)) void* __attribute__((__cdecl__)) memchr (const void*, int, size_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) memcmp (const void*, const void*, size_t);
__attribute__((dllimport)) void* __attribute__((__cdecl__)) memcpy (void*, const void*, size_t);
__attribute__((dllimport)) void* __attribute__((__cdecl__)) memmove (void*, const void*, size_t);
__attribute__((dllimport)) void* __attribute__((__cdecl__)) memset (void*, int, size_t);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strcat (char*, const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strchr (const char*, int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) strcmp (const char*, const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) strcoll (const char*, const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strcpy (char*, const char*);
__attribute__((dllimport)) size_t __attribute__((__cdecl__)) strcspn (const char*, const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strerror (int);

__attribute__((dllimport)) size_t __attribute__((__cdecl__)) strlen (const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strncat (char*, const char*, size_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) strncmp (const char*, const char*, size_t);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strncpy (char*, const char*, size_t);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strpbrk (const char*, const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strrchr (const char*, int);
__attribute__((dllimport)) size_t __attribute__((__cdecl__)) strspn (const char*, const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strstr (const char*, const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strtok (char*, const char*);
__attribute__((dllimport)) size_t __attribute__((__cdecl__)) strxfrm (char*, const char*, size_t);





__attribute__((dllimport)) char* __attribute__((__cdecl__)) _strerror (const char *);
__attribute__((dllimport)) void* __attribute__((__cdecl__)) _memccpy (void*, const void*, int, size_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _memicmp (const void*, const void*, size_t);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _strdup (const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _strcmpi (const char*, const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _stricmp (const char*, const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _stricoll (const char*, const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _strlwr (char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _strnicmp (const char*, const char*, size_t);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _strnset (char*, int, size_t);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _strrev (char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _strset (char*, int);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) _strupr (char*);
__attribute__((dllimport)) void __attribute__((__cdecl__)) _swab (const char*, char*, size_t);


__attribute__((dllimport)) int __attribute__((__cdecl__)) _strncoll(const char*, const char*, size_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _strnicoll(const char*, const char*, size_t);







__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcscat (wchar_t*, const wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcschr (const wchar_t*, wchar_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) wcscmp (const wchar_t*, const wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) wcscoll (const wchar_t*, const wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcscpy (wchar_t*, const wchar_t*);
__attribute__((dllimport)) size_t __attribute__((__cdecl__)) wcscspn (const wchar_t*, const wchar_t*);

__attribute__((dllimport)) size_t __attribute__((__cdecl__)) wcslen (const wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcsncat (wchar_t*, const wchar_t*, size_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) wcsncmp(const wchar_t*, const wchar_t*, size_t);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcsncpy(wchar_t*, const wchar_t*, size_t);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcspbrk(const wchar_t*, const wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcsrchr(const wchar_t*, wchar_t);
__attribute__((dllimport)) size_t __attribute__((__cdecl__)) wcsspn(const wchar_t*, const wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcsstr(const wchar_t*, const wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcstok(wchar_t*, const wchar_t*);
__attribute__((dllimport)) size_t __attribute__((__cdecl__)) wcsxfrm(wchar_t*, const wchar_t*, size_t);
# 131 "D:/Bernard/DDE/mingw/include/string.h" 3
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wcsdup (const wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _wcsicmp (const wchar_t*, const wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _wcsicoll (const wchar_t*, const wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wcslwr (wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _wcsnicmp (const wchar_t*, const wchar_t*, size_t);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wcsnset (wchar_t*, wchar_t, size_t);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wcsrev (wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wcsset (wchar_t*, wchar_t);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) _wcsupr (wchar_t*);


__attribute__((dllimport)) int __attribute__((__cdecl__)) _wcsncoll(const wchar_t*, const wchar_t*, size_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _wcsnicoll(const wchar_t*, const wchar_t*, size_t);
# 159 "D:/Bernard/DDE/mingw/include/string.h" 3
__attribute__((dllimport)) void* __attribute__((__cdecl__)) memccpy (void*, const void*, int, size_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) memicmp (const void*, const void*, size_t);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strdup (const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) strcmpi (const char*, const char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) stricmp (const char*, const char*);
extern __inline__ int __attribute__((__cdecl__))
strcasecmp (const char * __sz1, const char * __sz2)
  {return _stricmp (__sz1, __sz2);}
__attribute__((dllimport)) int __attribute__((__cdecl__)) stricoll (const char*, const char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strlwr (char*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) strnicmp (const char*, const char*, size_t);
extern __inline__ int __attribute__((__cdecl__))
strncasecmp (const char * __sz1, const char * __sz2, size_t __sizeMaxCompare)
  {return _strnicmp (__sz1, __sz2, __sizeMaxCompare);}
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strnset (char*, int, size_t);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strrev (char*);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strset (char*, int);
__attribute__((dllimport)) char* __attribute__((__cdecl__)) strupr (char*);

__attribute__((dllimport)) void __attribute__((__cdecl__)) swab (const char*, char*, size_t);



extern __inline__ int __attribute__((__cdecl__))
wcscmpi (const wchar_t * __ws1, const wchar_t * __ws2)
  {return _wcsicmp (__ws1, __ws2);}
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcsdup (wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) wcsicmp (const wchar_t*, const wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) wcsicoll (const wchar_t*, const wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcslwr (wchar_t*);
__attribute__((dllimport)) int __attribute__((__cdecl__)) wcsnicmp (const wchar_t*, const wchar_t*, size_t);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcsnset (wchar_t*, wchar_t, size_t);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcsrev (wchar_t*);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcsset (wchar_t*, wchar_t);
__attribute__((dllimport)) wchar_t* __attribute__((__cdecl__)) wcsupr (wchar_t*);
# 7 "../include/tiny/global.h" 2

# 1 "../include/tiny/config.h" 1
# 9 "../include/tiny/global.h" 2
# 18 "../include/tiny/global.h"
typedef void* ADT;
typedef short Bool;

typedef Bool (*EqualFunc) (ADT a, ADT b);
typedef void (*UserFunc) (ADT value, ADT data);

# 1 "../include/tiny/mem.h" 1



# 1 "../include/tiny/global.h" 1
# 5 "../include/tiny/mem.h" 2





ADT mem_new (int p_size);

ADT mem_resize (ADT p_ptr, int p_size);

void mem_destroy (ADT p_ptr);

void mem_copy (ADT p_src, ADT p_dst, int p_size);

void mem_move (ADT p_src, ADT p_dst, int p_size);

void mem_set (ADT s, char c, int size);

void mem_debug ();
# 25 "../include/tiny/global.h" 2
# 1 "../include/tiny/object.h" 1







typedef struct _Object Object;
typedef void (*ObjectDestroy) (Object* self);
struct _Object
{
        int refcount;

        ObjectDestroy destroy;
};

Object* object_new ();

void object_destroy (Object* self);

void object_init_object (Object* self, ObjectDestroy p_destroy);

Object* object_addref (Object* self);

void object_unref (Object* self);
# 26 "../include/tiny/global.h" 2
# 5 "../include/finc/fincsys.h" 2
# 1 "../include/tiny/string.h" 1






typedef struct _String String;
struct _String
{
        Object parent;
        unsigned char* data;
};

String* string_new ();
String* string_new_str (unsigned char* text);

void string_destroy (String* self);

unsigned int string_hash(void* self);

void string_clear (String* self);

void string_set (String* self, String* p_text);

void string_set_str (String* self, unsigned char* p_text);

unsigned char string_at (String* self, int index);

Bool string_is_empty(String* self);

void string_add (String* self, String* p_text);

void string_add_str (String* self, unsigned char* p_text);

void string_add_char (String* self, signed char p_char);

signed int string_cmp (String* self, String* p_text);

signed int string_cmp_str (String* self, unsigned char* p_text);

Bool string_equal(void* self, void* other);

signed int string_ncmp (String* self, String* p_text, unsigned int p_pos, unsigned int p_size);

signed int string_ncmp_str (String* self, unsigned char* p_text, unsigned int p_pos, unsigned int p_size);

unsigned int string_get_size (String* self);

signed char string_get_char (String* self, unsigned int p_index);

unsigned char* string_get_str (String* self);

String* string_extract (String* self, unsigned int p_index, unsigned int p_size);
# 6 "../include/finc/fincsys.h" 2
# 1 "../include/tiny/vector.h" 1







typedef struct _Vector Vector;
struct _Vector
{
        Object parent;

        Object** data;
        unsigned int size;
};

Vector* vector_new ();

void vector_destroy (Object* self);

void vector_clear (Vector* self);

Bool vector_is_empty(Vector* self);



void vector_resize (Vector* self, int p_newsize);

ADT vector_at (Vector* self, int p_index);

void vector_set_at (Vector* self, int p_index, ADT p_item);

void vector_append (Vector* self, ADT p_item);

void vector_preppend (Vector* self, ADT p_item);

void vector_insert (Vector* self, ADT p_item, int p_index);

void vector_remove (Vector* self, int p_index);

void vector_foreach(Vector* self, UserFunc user_func, ADT data);
# 7 "../include/finc/fincsys.h" 2

# 1 "../include/finc/fincconfig.h" 1
# 9 "../include/finc/fincsys.h" 2
# 1 "../include/finc/fincnode.h" 1
# 9 "../include/finc/fincnode.h"
# 1 "../include/finc/fincdata.h" 1
# 9 "../include/finc/fincdata.h"
# 1 "../include/finc/finctype.h" 1
# 12 "../include/finc/finctype.h"
typedef enum {
        FinCType_Void = 1 <<0,
        FinCType_Char = 1 <<1,
        FinCType_Short = 1 <<2,
        FinCType_Int = 1 <<3,
        FinCType_Float = 1 <<4,
        FinCType_Double = 1 <<5,
        FinCType_Bool = 1 <<6,
        FinCType_Pointer = 1 <<7,
        FinCType_String = 1 <<8,
        FinCType_Struct = 1 <<9,
        FinCType_Func = 1 <<10
} FinCTypeType;

typedef enum {
        FinCArrayType_None,
        FinCArrayType_Fixed,
        FinCArrayType_Dynamic
} FinCArrayType;

typedef struct _FinCData FinCData;
typedef struct _FinCField FinCField;
typedef struct _FinCType FinCType;
struct _FinCType
{
        Object parent;

        String* name;
        FinCTypeType type;

        FinCArrayType array_type;
        unsigned int array_size;
};

FinCType* finc_type_new (FinCTypeType p_type, FinCArrayType p_array_type, unsigned int p_array_size);
FinCType* finc_type_new_name (unsigned char* p_name, FinCArrayType p_array_type, unsigned int p_array_size);
FinCType* finc_type_new_copy(FinCType* other);

void finc_type_destroy (Object* self);

unsigned int finc_type_get_size (FinCType* self);
# 10 "../include/finc/fincdata.h" 2



struct _FinCData
{
    Object parent;

    FinCType* type;
    Vector* vector_child;
    FinCData* pointer;

    Bool ref;
    int array_stand;
        ADT raw;
};

FinCData* finc_data_new (FinCType* p_type, ADT p_ref);
FinCData* finc_data_new_data ( FinCType* p_type, ADT p_ref );
FinCData* finc_data_new_copy (FinCData* p_data);
FinCData* finc_data_new_string (unsigned char* p_str);
FinCData* finc_data_new_raw_string (unsigned char* p_str);

void finc_data_destroy (Object* self);

void finc_data_init_data (ADT self, ADT data);

String* finc_data_get_string (FinCData* self);

void finc_data_set_string (FinCData* self, String* p_value);
void finc_data_assign (FinCData* self, FinCData* p_src);

FinCData* finc_data_get_index (FinCData* self, int p_index);

ADT finc_data_get_ptr (FinCData* self);

void finc_data_set_pointer (FinCData* self, FinCData* p_raw);





FinCData* finc_data_get_field (FinCData* self, int p_index);
# 10 "../include/finc/fincnode.h" 2

typedef struct _FinCFunc FinCFunc;
typedef struct _FinCNode FinCNode;

# 1 "../include/finc/fincfunc.h" 1






# 1 "../include/tiny/list.h" 1







typedef struct _List List;




List* list_new();



void list_destroy(Object* self);




void list_clear(List* self);



Bool list_is_empty(List* self);




int list_get_size(List* self);




int list_current(List* self);



ADT list_at(List* self, int p_index);
Bool list_locate(List* self, int p_index);




ADT list_data(List* self);




ADT list_take(List* self, int p_index);



ADT list_take_current(List* self);




ADT list_find(List* self, EqualFunc p_func, ADT p_data);



ADT list_find_ref(List* self, EqualFunc p_func, ADT p_data);




void list_insert(List* self, int p_index, ADT p_data);



void list_insert_before(List* self, ADT p_data);



void list_insert_after(List* self, ADT p_data);




void list_prepend(List* self, ADT p_data);



void list_append(List* self, ADT p_data);




void list_remove(List* self, int p_index);




void list_remove_ref(List* self, EqualFunc p_func, ADT p_data);



void list_remove_current(List* self);





ADT list_prev(List* self);
ADT list_prev_unref(List* self);





ADT list_next(List* self);
ADT list_next_unref(List* self);




ADT list_first(List* self);
ADT list_first_unref(List* self);




ADT list_last(List* self);
ADT list_last_unref(List* self);




void list_foreach(List* self, UserFunc p_func, ADT data);
# 8 "../include/finc/fincfunc.h" 2



# 1 "../include/finc/fincnode.h" 1
# 12 "../include/finc/fincfunc.h" 2
# 1 "../include/finc/fincfield.h" 1
# 13 "../include/finc/fincfield.h"
struct _FinCField
{
        Object parent;

        String* name;
        FinCType* type;

        int offset;
        int index;
};

FinCField* finc_field_new (String* p_name, FinCType* p_type);
void finc_field_destroy (Object* self);
# 13 "../include/finc/fincfunc.h" 2

typedef enum {
        FinCFuncType_None,
        FinCFuncType_Sys,
        FinCFuncType_Sys_Api,
        FinCFuncType_Native,



        FinCFuncType_Node
} FinCFuncType;

typedef void (*FinCFuncSys)(FinCNode* p_node);
struct _FinCFunc
{
        Object parent;
        FinCFuncType type;

        String* name;
        FinCType* ret_type;

        FinCNode* node;
        FinCFuncSys sys;
        ADT native;

        Bool opt_param;

        Vector* vector_params;
};
# 68 "../include/finc/fincfunc.h"
extern FinCData* g_finc_func_return;

FinCFunc* finc_func_new ();
void finc_func_destroy (Object* self);

void finc_func_set_sys (FinCFunc* self, String* p_name, FinCFuncSys p_sys);
void finc_func_set_sys_api (FinCFunc* self, String* p_name, ADT sys_api);
void finc_func_set_native (FinCFunc* self, String* p_name, void* p_native);
void finc_func_set_node (FinCFunc* self, String* p_name, FinCNode* p_node);

void finc_func_add_param (FinCFunc* self, FinCField* p_param);

FinCData* finc_func_call (FinCFunc* self, FinCNode* p_node);
FinCData* finc_func_native_call (FinCFunc* self, FinCNode* node);
FinCData* finc_func_native_call_f (FinCFunc* self, FinCNode* node);
# 15 "../include/finc/fincnode.h" 2



typedef enum
{
        FinCNodeType_None,
        FinCNodeType_Block,
        FinCNodeType_Data,
        FinCNodeType_Func,
        FinCNodeType_Type,
        FinCNodeType_Identifier
} FinCNodeType;

struct _FinCNode
{
    Object parent;

    FinCNodeType node_type;
    FinCData* data;
    FinCFunc* func;
    FinCType* type;
    String* identifier;
    Bool check;
    Bool constant;

    String* source_file;
    unsigned int source_line;

    Vector* vector_node;
};

FinCNode* finc_node_new ();
FinCNode* finc_node_new_func (unsigned char* p_name);
FinCNode* finc_node_new_name (unsigned char* p_name);
FinCNode* finc_node_new_type (String* p_typename, FinCArrayType p_array, unsigned int p_size);
FinCNode* finc_node_new_char (unsigned char p_char);
FinCNode* finc_node_new_string (unsigned char* p_text);
FinCNode* finc_node_new_integer (unsigned int p_int);

FinCNode* finc_node_new_float (float p_value);




FinCNode* finc_node_new_long (long p_long);
FinCNode* finc_node_new_bool (Bool p_bool);
FinCNode* finc_node_new_pointer (void* p_ptr);

void finc_node_destroy (Object* self);




void finc_node_evaluate (FinCNode* self);




FinCData* finc_node_take_data (FinCNode* self);




void finc_node_set_data (FinCNode* self, FinCData* p_data);
void finc_node_set_func (FinCNode* self, String* p_name);
void finc_node_set_type (FinCNode* self, FinCType* p_type);
void finc_node_set_identifier (FinCNode* self, String* p_identifier);
# 10 "../include/finc/fincsys.h" 2
# 1 "../include/finc/finclang.h" 1






# 1 "../include/tiny/stack.h" 1







typedef struct _Stack Stack;
struct _Stack
{
        Object parent;

        List* stack;
};

Stack* stack_new();
void stack_destroy(Object* self);

ADT stack_pop(Stack* self);
void stack_push(Stack* self, ADT item);

ADT stack_take(Stack* self);

int stack_get_size(Stack* self);

Bool stack_is_empty(Stack* self);
# 8 "../include/finc/finclang.h" 2
# 1 "../include/tiny/library.h" 1
# 9 "../include/finc/finclang.h" 2



# 1 "../include/finc/finctoken.h" 1



# 1 "D:/Bernard/DDE/mingw/include/ctype.h" 1 3
# 36 "D:/Bernard/DDE/mingw/include/ctype.h" 3
# 1 "D:/Bernard/DDE/mingw/include/stddef.h" 1 3





# 1 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stddef.h" 1 3
# 7 "D:/Bernard/DDE/mingw/include/stddef.h" 2 3
# 37 "D:/Bernard/DDE/mingw/include/ctype.h" 2 3
# 62 "D:/Bernard/DDE/mingw/include/ctype.h" 3
__attribute__((dllimport)) int __attribute__((__cdecl__)) isalnum(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) isalpha(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iscntrl(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) isdigit(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) isgraph(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) islower(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) isprint(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) ispunct(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) isspace(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) isupper(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) isxdigit(int);


__attribute__((dllimport)) int __attribute__((__cdecl__)) _isctype (int, int);



__attribute__((dllimport)) int __attribute__((__cdecl__)) tolower(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) toupper(int);
# 92 "D:/Bernard/DDE/mingw/include/ctype.h" 3
__attribute__((dllimport)) int __attribute__((__cdecl__)) _tolower(int);
__attribute__((dllimport)) int __attribute__((__cdecl__)) _toupper(int);
# 120 "D:/Bernard/DDE/mingw/include/ctype.h" 3
__attribute__((dllimport)) unsigned short _ctype[];

  __attribute__((dllimport)) unsigned short* _pctype;
# 187 "D:/Bernard/DDE/mingw/include/ctype.h" 3
typedef wchar_t wctype_t;



__attribute__((dllimport)) int __attribute__((__cdecl__)) iswalnum(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswalpha(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswascii(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswcntrl(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswctype(wint_t, wctype_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) is_wctype(wint_t, wctype_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswdigit(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswgraph(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswlower(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswprint(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswpunct(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswspace(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswupper(wint_t);
__attribute__((dllimport)) int __attribute__((__cdecl__)) iswxdigit(wint_t);

__attribute__((dllimport)) wchar_t __attribute__((__cdecl__)) towlower(wchar_t);
__attribute__((dllimport)) wchar_t __attribute__((__cdecl__)) towupper(wchar_t);

__attribute__((dllimport)) int __attribute__((__cdecl__)) isleadbyte (int);
# 231 "D:/Bernard/DDE/mingw/include/ctype.h" 3
int __attribute__((__cdecl__)) __isascii (int);
int __attribute__((__cdecl__)) __toascii (int);
int __attribute__((__cdecl__)) __iscsymf (int);
int __attribute__((__cdecl__)) __iscsym (int);
# 245 "D:/Bernard/DDE/mingw/include/ctype.h" 3
int __attribute__((__cdecl__)) isascii (int);
int __attribute__((__cdecl__)) toascii (int);
int __attribute__((__cdecl__)) iscsymf (int);
int __attribute__((__cdecl__)) iscsym (int);
# 5 "../include/finc/finctoken.h" 2
# 13 "../include/finc/finctoken.h"
enum _FinCTokenType
{
        FinCTokenType_Left_Paren ,
        FinCTokenType_Right_Paren ,
        FinCTokenType_Left_Curly ,
        FinCTokenType_Right_Curly ,
        FinCTokenType_Left_Brace ,
        FinCTokenType_Right_Brace ,
        FinCTokenType_Comma ,
        FinCTokenType_Colon ,
        FinCTokenType_Scope ,
        FinCTokenType_Semicolon ,
        FinCTokenType_Dot ,
        FinCTokenType_Question ,
        FinCTokenType_Not ,
        FinCTokenType_Not_Eqs,
        FinCTokenType_Mul ,
        FinCTokenType_Add ,
        FinCTokenType_Inc,
        FinCTokenType_Sub ,
        FinCTokenType_Dec,
        FinCTokenType_Div ,
        FinCTokenType_Mod ,
        FinCTokenType_Assign ,
        FinCTokenType_Eq,
        FinCTokenType_GT ,
        FinCTokenType_Greater_Eqs,
        FinCTokenType_LT ,
        FinCTokenType_Less_Eqs,
        FinCTokenType_Logic_And,
        FinCTokenType_Logic_Or,
        FinCTokenType_And,
        FinCTokenType_Or,
        FinCTokenType_XOR,
        FinCTokenType_Bitwise,
        FinCTokenType_SHL,
        FinCTokenType_SHR,

        FinCTokenType_Char,
        FinCTokenType_String,
        FinCTokenType_Short,
        FinCTokenType_Int,

        FinCTokenType_Float,




        FinCTokenType_Long,

        FinCTokenType_Type_Void,
        FinCTokenType_Type_Int,
        FinCTokenType_Type_Char,
        FinCTokenType_Type_Short,







        FinCTokenType_Type_Float,

        FinCTokenType_Type_Bool,
        FinCTokenType_Type_Pointer,
        FinCTokenType_Type_String,


        FinCTokenType_Static,
        FinCTokenType_Unsigned,
        FinCTokenType_Struct,






        FinCTokenType_False,
        FinCTokenType_True,
        FinCTokenType_Null,
        FinCTokenType_For,
        FinCTokenType_While,
        FinCTokenType_If,
        FinCTokenType_Else,
        FinCTokenType_Return,
        FinCTokenType_Break,
        FinCTokenType_Continue,
        FinCTokenType_Import,
        FinCTokenType_Package,
        FinCTokenType_Addrof,
        FinCTokenType_Valueof,
        FinCTokenType_Identifier,
        FinCTokenType_Eof,
        FinCTokenType_Bad
};
typedef enum _FinCTokenType FinCTokenType;

typedef struct _FinCTokenEnv FinCTokenEnv;
struct _FinCTokenEnv
{
        Object parent;

        Bool eof;
        Bool replay;

        int line;
        int position;

        FinCTokenType current_token;

        String* line_str;

        String* last_str;
        char last_char;



        long last_double;

        float last_float;
        long last_long;

        unsigned char* (*read_line)(const char* arg);
        const char* arg;
};

FinCTokenEnv* finc_token_new();
void finc_token_destroy(Object* self);

FinCTokenType finc_token_token(FinCTokenEnv* self);
String* finc_token_get_token(FinCTokenEnv* self);
# 13 "../include/finc/finclang.h" 2

typedef struct _FinCLangEnv FinCLangEnv;
struct _FinCLangEnv
{
    Object parent;

    FinCNode* tree_root;
    List* list_pkg;





    unsigned int nb_error;
};

extern FinCLangEnv* g_finc_lang_env;
extern int g_lang_nberr;

FinCLangEnv* finc_lang_new ();
void finc_lang_destroy(Object* self);

void finc_lang_error_line (FinCTokenEnv* lex, char* msg);

Bool finc_lang_check_type (FinCLangEnv* self, String* p_type);






void finc_lang_proc_import(FinCLangEnv* self, FinCNode* p_node);


void finc_lang_proc_struct(FinCLangEnv* self, FinCNode* p_node);
void finc_lang_proc_func (FinCLangEnv* self, FinCNode* p_node );
# 11 "../include/finc/fincsys.h" 2

typedef struct _FinCSys FinCSys;
struct _FinCSys
{
        Object parent;

        FinCLangEnv* env;
};

FinCSys* finc_sys_new();
void finc_sys_destroy(Object* self);
void finc_sys_init (FinCSys* self);
# 2 "fincsys.c" 2

# 1 "../include/finc/finccontext.h" 1







# 1 "../include/tiny/hash.h" 1





typedef unsigned int (*HashFunc) (void* key);

typedef struct _HashTable HashTable;




HashTable* hash_table_new (HashFunc hash_func, EqualFunc key_equal_func);

void hash_table_destroy (Object* hash_table);

void* hash_table_find (HashTable* hash_table, void* key);

void hash_table_insert (HashTable* hash_table, void* key, void* value);

Bool hash_table_remove (HashTable* hash_table, void* key);

void hash_table_foreach(HashTable* hash_table, UserFunc user_func, void* data);

unsigned int hash_table_get_size (HashTable* hash_table);



unsigned int direct_hash (void* v);
# 9 "../include/finc/finccontext.h" 2


# 1 "../include/finc/fincdebug.h" 1
# 12 "../include/finc/finccontext.h" 2

# 1 "../include/finc/fincvar.h" 1
# 13 "../include/finc/fincvar.h"
typedef struct _FinCVar FinCVar;
struct _FinCVar
{
        Object parent;

        String* name;
        FinCData* data;
};

FinCVar* finc_var_new (String* p_name, FinCData* p_data);
FinCVar* finc_var_new_copy (String* p_name, FinCData* p_data);

void finc_var_destroy (Object* self);
# 14 "../include/finc/finccontext.h" 2
# 1 "../include/finc/fincstruct.h" 1
# 14 "../include/finc/fincstruct.h"
typedef struct _FinCStruct FinCStruct;
struct _FinCStruct
{
        Object parent;
        String* name;

        HashTable* hash_field;

        int size;
        int next_index;
};

FinCStruct* finc_struct_new(String* p_name);
void finc_struct_destroy(Object* self);

Vector* finc_struct_init_data(FinCStruct* self, ADT p_raw);

void finc_struct_add_field (FinCStruct* self, FinCField* p_field);






int finc_struct_get_field_offset (FinCStruct* self, String* p_name);
int finc_struct_get_field_index (FinCStruct* self, String* p_name);
# 15 "../include/finc/finccontext.h" 2

typedef struct _FinCContext FinCContext;
struct _FinCContext
{
        Object parent;

        Bool script_return;
        Bool script_continue;
        Bool script_break;
        Bool script_in_cycle;

        HashTable* hash_global;
        HashTable* hash_local;
        HashTable* hash_functions;
        HashTable* hash_struct;

        int error;
};

extern FinCContext* g_finc_context;

FinCContext* finc_context_new ();
void finc_context_destroy (Object* self);




FinCFunc* finc_context_add_func_sys (FinCContext* self, unsigned char* p_name, FinCFuncSys p_sys);
FinCFunc* finc_context_add_func_sys_api (FinCContext* self, unsigned char* p_name, void* p_func);
FinCFunc* finc_context_add_func_native (FinCContext* self, unsigned char* p_name, void* p_native);
FinCFunc* finc_context_add_func_node (FinCContext* self, unsigned char* p_name, FinCNode* p_node);



void finc_context_add_var (FinCContext* self, FinCVar* p_var, Bool p_global);
FinCVar* finc_context_get_var (FinCContext* self, String* p_name);






HashTable* finc_context_func_enter (FinCContext* self);
void finc_context_func_leave (FinCContext* self, HashTable* p_hash);
# 4 "fincsys.c" 2

# 1 "../include/finc/finclib.h" 1




# 1 "D:/Bernard/DDE/mingw/include/stdarg.h" 1 3





# 1 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stdarg.h" 1 3
# 111 "D:/Bernard/DDE/mingw/lib/gcc-lib/mingw32/3.2.3/include/stdarg.h" 3
typedef __gnuc_va_list va_list;
# 7 "D:/Bernard/DDE/mingw/include/stdarg.h" 2 3
# 6 "../include/finc/finclib.h" 2
# 14 "../include/finc/finclib.h"
# 1 "../include/finc/fincparser.h" 1
# 13 "../include/finc/fincparser.h"
typedef struct _FinCParser FinCParser;
struct _FinCParser
{
    Object parent;
    FinCNode* tree_root;
    FinCTokenEnv* lex;

    String* parse_string;

    FinCLangEnv* lang_env;

    Stack* stack_call;
    Stack* stack_block;

    FinCNode* current_func;
    FinCNode* current_block;
    FinCNode* current_call;
    FinCNode* current_type;
    FinCNode* current_pkg;
    FinCNode* current_struct;
        FinCNode* current_class;
};

FinCParser* finc_parser_new();
void finc_parser_destroy(Object* self);
void finc_parser_set_env (FinCParser* self, FinCLangEnv* env);

void finc_parser_parser(FinCParser* self, String* stream);
void finc_parser_parser_string(FinCParser* self, String* str);


void finc_parser_parser_file(FinCParser* self, const char* filename);
# 15 "../include/finc/finclib.h" 2





typedef struct _FinC FinC;
struct _FinC
{
        Object parent;

        FinCLangEnv* env;
        FinCSys* sys_func;

        FinCContext* context;
};

typedef struct _FinCMethodItem FinCMethodItem;
typedef struct _FinCMethodItem* FinCMethodTable;
struct _FinCMethodItem
{
        const char* method_name;
        void* method_ptr;
};

typedef struct _FinCFieldItem FinCFieldItem;
typedef struct _FinCFieldItem* FinCFieldTable;
struct _FinCFieldItem
{
        const char* field_name;
        void* field_ptr;
        char size;
};

FinC* finc_init();
void finc_exit(FinC* self);

void finc_insert_var(FinC* self, unsigned char* type, unsigned char* name, ADT data);
void finc_remove_var(FinC* self, unsigned char* name);
ADT finc_get_var(FinC* self, unsigned char* name);

void finc_insert_func(FinC* self, unsigned char* p_name, void* p_func, unsigned char* p_rettype, ...);
void finc_insert_sys_api(FinC* self, unsigned char* p_name, void* p_func, unsigned char* p_rettype);
ADT finc_call_func(FinC* self, unsigned char* func);

void finc_proc_method_table(FinC* self, FinCMethodTable table, int size);


void finc_run_script(FinC* self, unsigned char* filename);


void finc_run_string(FinC* self, unsigned char* str);
# 6 "fincsys.c" 2





void finc_sys_global (FinCNode* p_node);
void finc_sys_local (FinCNode* p_node);



void finc_sys_addr_of (FinCNode* p_node);
void finc_sys_value_of (FinCNode* p_node);
void finc_sys_access (FinCNode* p_node);



void finc_sys_assign (FinCNode* p_node);
void finc_sys_cast (FinCNode* p_node);



void finc_sys_logic_or (FinCNode* p_node);
void finc_sys_logic_and (FinCNode* p_node);

void finc_sys_not ( FinCNode* p_node );

void finc_sys_or (FinCNode* p_node);
void finc_sys_and (FinCNode* p_node);
void finc_sys_xor (FinCNode* p_node);
void finc_sys_bitwise (FinCNode* p_node);
void finc_sys_shl (FinCNode* p_node);
void finc_sys_shr (FinCNode* p_node);



void finc_sys_add (FinCNode* p_node);
void finc_sys_sub (FinCNode* p_node);
void finc_sys_mul (FinCNode* p_node);
void finc_sys_div (FinCNode* p_node);
void finc_sys_mod (FinCNode* p_node);
void finc_sys_inc (FinCNode* p_node);
void finc_sys_dec (FinCNode* p_node);

void finc_sys_preinc (FinCNode* p_node);
void finc_sys_predec (FinCNode* p_node);



void finc_sys_block (FinCNode* p_node);
void finc_sys_if (FinCNode* p_node);
void finc_sys_for (FinCNode* p_node);
void finc_sys_while (FinCNode* p_node);
void finc_sys_return (FinCNode* p_node);
void finc_sys_break (FinCNode* p_node);
void finc_sys_continue (FinCNode* p_node);



void finc_sys_cmp_l (FinCNode* p_node);
void finc_sys_cmp_g (FinCNode* p_node);
void finc_sys_cmp_le (FinCNode* p_node);
void finc_sys_cmp_ge (FinCNode* p_node);
void finc_sys_cmp_ne (FinCNode* p_node);
void finc_sys_cmp_e (FinCNode* p_node);



void finc_sys_import (FinCNode* p_node);
void finc_sys_array (FinCNode* p_node);
void finc_sys_condition (FinCNode* p_node);
void finc_sys_comma (FinCNode* p_node);

void finc_sys_negative( FinCNode* p_node );

FinCSys* finc_sys_new()
{
        FinCSys* self;

        self = (FinCSys*)mem_new(sizeof(FinCSys));

        self->env = ((void *)0);

        object_init_object((Object*)self, finc_sys_destroy);

        return self;
}

void finc_sys_destroy(Object* self)
{
        object_unref ((Object*) ((FinCSys*)self)->env);

        mem_destroy(self);
}

void finc_sys_init (FinCSys* self)
{


        finc_context_add_func_sys ( g_finc_context, "global", finc_sys_global );
        finc_context_add_func_sys ( g_finc_context, "local", finc_sys_local );

        finc_context_add_func_sys ( g_finc_context, "cast", finc_sys_cast );
        finc_context_add_func_sys ( g_finc_context, "addr_of", finc_sys_addr_of );
        finc_context_add_func_sys ( g_finc_context, "value_of", finc_sys_value_of );

        finc_context_add_func_sys ( g_finc_context, ".", finc_sys_access );

        finc_context_add_func_sys ( g_finc_context, "||", finc_sys_logic_or );
        finc_context_add_func_sys ( g_finc_context, "&&", finc_sys_logic_and );

        finc_context_add_func_sys ( g_finc_context, "!", finc_sys_not );

        finc_context_add_func_sys ( g_finc_context, "|", finc_sys_or );
        finc_context_add_func_sys ( g_finc_context, "&", finc_sys_and );
        finc_context_add_func_sys ( g_finc_context, "^", finc_sys_xor );
        finc_context_add_func_sys ( g_finc_context, "~", finc_sys_bitwise );

        finc_context_add_func_sys ( g_finc_context, "<<", finc_sys_shl );
        finc_context_add_func_sys ( g_finc_context, ">>", finc_sys_shr );

        finc_context_add_func_sys ( g_finc_context, ",", finc_sys_comma );
        finc_context_add_func_sys ( g_finc_context, "?", finc_sys_condition );

        finc_context_add_func_sys ( g_finc_context, "+", finc_sys_add );
        finc_context_add_func_sys ( g_finc_context, "-", finc_sys_sub );
        finc_context_add_func_sys ( g_finc_context, "*", finc_sys_mul );
        finc_context_add_func_sys ( g_finc_context, "/", finc_sys_div );
        finc_context_add_func_sys ( g_finc_context, "%", finc_sys_mod );

        finc_context_add_func_sys ( g_finc_context, "negative", finc_sys_negative );

        finc_context_add_func_sys ( g_finc_context, "++", finc_sys_inc );
        finc_context_add_func_sys ( g_finc_context, "--", finc_sys_dec );

        finc_context_add_func_sys ( g_finc_context, "preinc", finc_sys_preinc );
        finc_context_add_func_sys ( g_finc_context, "predec", finc_sys_predec );

        finc_context_add_func_sys ( g_finc_context, "[]", finc_sys_array );

        finc_context_add_func_sys ( g_finc_context, "if", finc_sys_if );
        finc_context_add_func_sys ( g_finc_context, "for", finc_sys_for );
        finc_context_add_func_sys ( g_finc_context, "while", finc_sys_while );
        finc_context_add_func_sys ( g_finc_context, "return", finc_sys_return );
        finc_context_add_func_sys ( g_finc_context, "continue", finc_sys_continue );
        finc_context_add_func_sys ( g_finc_context, "break", finc_sys_break );

        finc_context_add_func_sys ( g_finc_context, "<", finc_sys_cmp_l );
        finc_context_add_func_sys ( g_finc_context, ">", finc_sys_cmp_g );
        finc_context_add_func_sys ( g_finc_context, "<=", finc_sys_cmp_le );
        finc_context_add_func_sys ( g_finc_context, ">=", finc_sys_cmp_ge );
        finc_context_add_func_sys ( g_finc_context, "!=", finc_sys_cmp_ne );
        finc_context_add_func_sys ( g_finc_context, "==", finc_sys_cmp_e );

        finc_context_add_func_sys ( g_finc_context, "=", finc_sys_assign );

        finc_context_add_func_sys ( g_finc_context, "++", finc_sys_inc );
        finc_context_add_func_sys ( g_finc_context, "--", finc_sys_dec );

        finc_context_add_func_sys ( g_finc_context, "@", finc_sys_block );
}

void finc_sys_global ( FinCNode* p_node )
{
        FinCNode* l_node;
        FinCNode* node_var;
        FinCType* l_type;
        String* l_name;
        FinCData* l_data;
        FinCVar* l_var;
        FinCNode* l_init_node;
        int l_size, i;

        l_node = (FinCNode*) vector_at ( p_node->vector_node, 0 ) ;
        l_type = l_node->type;

        l_size = ((l_node)->vector_node)->size;

        for ( i=0; i<l_size; i++)
        {
                node_var = (FinCNode*) vector_at ( l_node->vector_node, i );
                l_name = node_var->identifier;

                l_data = finc_data_new ( l_type, ((void *)0) );
                if ( (node_var->vector_node)->size!=0 )
                {
                        l_init_node = (FinCNode*) vector_at( node_var->vector_node, 0);
                        finc_node_evaluate (l_init_node);
                        finc_data_assign (l_data, l_init_node->data);
                        object_unref ((Object*) l_init_node);
                }
                object_unref ((Object*) node_var);

                l_var = finc_var_new ( l_name, l_data );

                finc_context_add_var ( g_finc_context, l_var, 1 );

                object_unref ((Object*) l_data);
                object_unref ((Object*) l_var);
        }
        object_unref ((Object*) l_node);
}

void finc_sys_local ( FinCNode* p_node )
{
        FinCNode* l_node;
        FinCNode* node_var;
        FinCType* l_type;
        String* l_name;
        FinCData* l_data;
        FinCVar* l_var;
        FinCNode* l_init_node;
        int l_size, i;

        l_node = (FinCNode*) vector_at ( p_node->vector_node, 0 ) ;
        l_type = l_node->type;

        l_size = ((l_node)->vector_node)->size;

        for ( i=0; i<l_size; i++)
        {
                node_var = (FinCNode*) vector_at ( l_node->vector_node, i );
                l_name = node_var->identifier;

                l_data = finc_data_new ( l_type, ((void *)0) );

                if ( (node_var->vector_node)->size!=0 )
                {
                        l_init_node = (FinCNode*) vector_at( node_var->vector_node, 0);
                        finc_node_evaluate (l_init_node);
                        finc_data_assign (l_data, l_init_node->data);
                        object_unref ((Object*) l_init_node);
                }
                object_unref ((Object*) node_var);

                l_var = finc_var_new ( l_name, l_data );

                finc_context_add_var ( g_finc_context, l_var, 0 );

                object_unref ((Object*) l_data);
                object_unref ((Object*) l_var);
        }
        object_unref ((Object*) l_node);
}

void finc_sys_access ( FinCNode* p_node )
{
        FinCNode* l_main;
        FinCNode* l_sub;

        FinCData* l_data;
        FinCData* l_field;

        FinCStruct* l_struct;
        int l_index;

        l_main = (FinCNode*) vector_at (p_node->vector_node, 0);
        l_sub = (FinCNode*) vector_at (p_node->vector_node, 1);

        finc_node_evaluate (l_main);

        if (!(l_sub)->node_type == (FinCNodeType_Identifier)? 1 : 0)
        {
                printf("Error:struct access, right must be a identifer!\n");
                object_unref ((Object*) l_main);
                object_unref ((Object*) l_sub);
                return;
        }

        l_data = (FinCData*) object_addref (((Object*) l_main->data));
        if (!l_data)
        {
                printf("Runtime Error:struct variable not founded.\n");
                (g_finc_context)->error ++;
                object_unref ((Object*) l_main);
                object_unref ((Object*) l_sub);
                return;
        }
        l_struct = hash_table_find( (g_finc_context)->hash_struct, (ADT)(l_data->type->name));
        l_index = finc_struct_get_field_index (l_struct, l_sub->identifier);
        l_field = finc_data_get_field(l_data, l_index);

        p_node->data = (FinCData*) object_addref (((Object*) l_field));

        object_unref ((Object*) l_main);
        object_unref ((Object*) l_sub);
        object_unref ((Object*) l_data);
        object_unref ((Object*) l_field);
        object_unref ((Object*) l_struct);
}

void finc_sys_array ( FinCNode* p_node )
{
        FinCNode * l_node;

        FinCData* l_data;
        FinCData* l_index;
        int index;

        l_node = (FinCNode*) vector_at ( p_node->vector_node, 0 );
        finc_node_evaluate ( l_node );
        l_data = (FinCData*) object_addref (((Object*) l_node->data));
        object_unref ((Object*) l_node);

        l_node = (FinCNode*) vector_at ( p_node->vector_node, 1 );
        finc_node_evaluate ( l_node );
        l_index = (FinCData*) object_addref (((Object*) l_node->data));
        object_unref ((Object*) l_node);

        index = (*(int*)((unsigned char*)l_index->raw + 0));

        if ( (index<0) || (index>(l_data->type->array_size-1)) )
        {
                printf("Runtime Error: array out of range.\n");
                (g_finc_context)->error ++;
                object_unref ((Object*) l_data);
                object_unref ((Object*) l_index);
                return;
        }

        object_unref ((Object*) p_node->data);
        p_node->data = finc_data_get_index ( l_data, index );
        l_data->array_stand = index;

        object_unref ((Object*) l_data);
        object_unref ((Object*) l_index);
}

void finc_sys_assign ( FinCNode* p_node )
{
        FinCNode * l_node;
        FinCData* l_src;
        FinCData* l_dst;

        l_node = ((FinCNode*) vector_at ( p_node->vector_node, 0 ));
        finc_node_evaluate ( l_node );
        l_dst = finc_node_take_data(l_node);
        object_unref ((Object*) l_node);

        l_node = ((FinCNode*) vector_at ( p_node->vector_node, 1 ));
        finc_node_evaluate ( l_node );
        l_src = finc_node_take_data(l_node);

        if ( l_node->node_type ==FinCNodeType_Func )
        {
                if (strcmp(string_get_str(l_node->identifier), "cast") ==0 ||
                        strcmp(string_get_str(l_node->identifier), "contentof") == 0 )

                {
                        l_dst = (FinCData*) object_addref (((Object*) l_src));
                }
                else
                {
                        finc_data_assign ( l_dst, l_src );
                }
        }
        else
        {
                finc_data_assign ( l_dst, l_src );
        }

        object_unref ((Object*) p_node->data);
        p_node->data = l_src;

        object_unref ((Object*) l_node);
        object_unref ((Object*) l_dst);
}

void finc_sys_cast ( FinCNode* p_node )
{
        FinCNode* l_type_node;
        FinCNode* l_data_node;
        FinCData* l_data;

        l_type_node = (FinCNode*) vector_at ( p_node->vector_node, 0 );
        l_data_node = (FinCNode*) vector_at ( p_node->vector_node, 1 );
        finc_node_evaluate ( l_data_node );

        l_data = finc_data_new ( l_type_node->type, l_data_node->data->raw );
        object_unref ((Object*) l_type_node);
        object_unref ((Object*) l_data_node);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_addr_of ( FinCNode* p_node )
{
        FinCNode * l_node;
        FinCType* l_type;
        FinCData* l_data;

        l_type = finc_type_new ( FinCType_Pointer, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );
        object_unref ((Object*) l_type);

        l_node = (FinCNode*) vector_at ( p_node->vector_node, 0 );
        finc_node_evaluate ( l_node );

        finc_data_set_pointer (l_data, l_node->data);

        object_unref ((Object*) l_node);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_value_of( FinCNode* p_node)
{
        FinCNode * l_node;

        l_node = (FinCNode*) vector_at (p_node->vector_node, 0);
        finc_node_evaluate (l_node);

        object_unref ((Object*) p_node->data);
        p_node->data = (FinCData*) object_addref (((Object*) l_node->data->pointer));
        object_unref ((Object*) l_node);
}

void finc_sys_if ( FinCNode* p_node )
{
        FinCNode * l_test;
        FinCNode* l_true;
        FinCNode* l_false;
        FinCData* l_data_test;

        l_test = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_true = (FinCNode*)vector_at ( p_node->vector_node, 1 );
        l_false = (FinCNode*)vector_at ( p_node->vector_node, 2 );

        finc_node_evaluate ( l_test );
        l_data_test = finc_node_take_data(l_test);

        if ( (*(Bool*)((unsigned char*)l_data_test? ((ADT)(l_data_test)->raw) : ((void *)0) + 0)) )
        {
                finc_node_evaluate ( l_true );
        }
        else
        {
                if ( l_false ) finc_node_evaluate ( l_false );
        }

        object_unref ((Object*) l_test);
        object_unref ((Object*) l_data_test);
        object_unref ((Object*) l_true);
        object_unref ((Object*) l_false);
}

void finc_sys_for ( FinCNode* p_node )
{
        FinCNode * node1;
        FinCNode* node2;
        FinCNode* node3;
        FinCNode* code;
        Bool old_continue, old_break, old_in_cycle;

        node1 = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        node2 = (FinCNode*)vector_at ( p_node->vector_node, 1 );
        node3 = (FinCNode*)vector_at ( p_node->vector_node, 2 );

        code = (FinCNode*)vector_at ( p_node->vector_node, 3 );

        finc_node_evaluate ( node1 );
        finc_node_evaluate ( node2 );

        old_continue = g_finc_context->script_continue;
        old_break = g_finc_context->script_break;
        old_in_cycle = g_finc_context->script_in_cycle;

        while ( (*(Bool*)((unsigned char*)node2->data? ((ADT)(node2->data)->raw) : ((void *)0) + 0)) )
        {
                g_finc_context->script_in_cycle = 1;
                finc_node_evaluate ( code );
                if (g_finc_context->script_break)
                {
                        g_finc_context->script_break = 0;
                        g_finc_context->script_in_cycle = 0;
                        break;
                }
                g_finc_context->script_continue = 0;
                finc_node_evaluate ( node3 );
                finc_node_evaluate ( node2 );
                g_finc_context->script_in_cycle = 0;
        }

        object_unref ((Object*) node1);
        object_unref ((Object*) node2);
        object_unref ((Object*) node3);
        object_unref ((Object*) code);

        g_finc_context->script_continue = old_continue;
        g_finc_context->script_break = old_break;
        g_finc_context->script_in_cycle = old_in_cycle;
}

void finc_sys_while ( FinCNode* p_node )
{
        FinCNode * l_test;
        FinCNode* l_code;
        Bool old_continue, old_break, old_in_cycle;

        l_test = ((FinCNode*) vector_at ( p_node->vector_node, 0 ));
        l_code = ((FinCNode*) vector_at ( p_node->vector_node, 1 ));

        finc_node_evaluate ( l_test );

        old_continue = g_finc_context->script_continue;
        old_break = g_finc_context->script_break;
        old_in_cycle = g_finc_context->script_in_cycle;

        while ( (*(Bool*)((unsigned char*)l_test->data? ((ADT)(l_test->data)->raw) : ((void *)0) + 0)) )
        {
                g_finc_context->script_in_cycle = 1;
                finc_node_evaluate ( l_code );
                if (g_finc_context->script_break)
                {
                        g_finc_context->script_break = 0;
                        g_finc_context->script_in_cycle = 0;
                        break;
                }
                g_finc_context->script_continue = 0;
                finc_node_evaluate ( l_test );
                g_finc_context->script_in_cycle = 0;
        }

        object_unref ((Object*) l_test);
        object_unref ((Object*) l_code);
        g_finc_context->script_continue = old_continue;
        g_finc_context->script_break = old_break;
        g_finc_context->script_in_cycle = old_in_cycle;
}

void finc_sys_return ( FinCNode* p_node )
{
        FinCNode * l_node;

        l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        finc_node_evaluate ( l_node );

        if (l_node) g_finc_func_return = (FinCData*) object_addref (((Object*) l_node->data));
        else g_finc_func_return = ((void *)0);

        object_unref ((Object*) l_node);

        g_finc_context->script_return = 1;
}

void finc_sys_continue ( FinCNode* p_node )
{
        if ( g_finc_context->script_in_cycle )
        {
                g_finc_context->script_continue = 1;
                return;
        }
        printf("Runtime Error: can't use continue not in a cycle.\n");
        (g_finc_context)->error ++;
}

void finc_sys_break ( FinCNode* p_node )
{
        if ( g_finc_context->script_in_cycle )
        {
                g_finc_context->script_break = 1;
                return;
        }
        printf("Runtime Error: can't use break not in a cycle.\n");
        (g_finc_context)->error ++;
}

void finc_sys_preinc ( FinCNode* p_node)
{
        FinCNode * l_node;

        l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        finc_node_evaluate ( l_node );

        (*(unsigned int*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0))
                = (*(unsigned int*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0)) + 1;

        object_unref ((Object*) p_node->data);
        p_node->data = finc_data_new_copy(l_node->data);
        object_unref ((Object*) l_node);
}

void finc_sys_inc ( FinCNode* p_node )
{
        FinCNode * l_node;

        l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        finc_node_evaluate ( l_node );

        object_unref ((Object*) p_node->data);
        p_node->data = finc_data_new_copy(l_node->data);

        (*(unsigned int*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0))
                = (*(unsigned int*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0)) + 1;
        object_unref ((Object*) l_node);
}

void finc_sys_predec ( FinCNode* p_node )
{
        FinCNode * l_node;

        l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        finc_node_evaluate ( l_node );

        (*(unsigned int*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0))
                = (*(unsigned int*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0)) - 1;

        object_unref ((Object*) p_node->data);
        p_node->data = finc_data_new_copy(l_node->data);
        object_unref ((Object*) l_node);
}

void finc_sys_dec ( FinCNode* p_node )
{
        FinCNode * l_node;

        l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        finc_node_evaluate ( l_node );
        p_node->data = finc_data_new_copy(l_node->data);

        (*(unsigned int*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0))
                = (*(unsigned int*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0)) - 1;
        object_unref ((Object*) l_node);
}

void finc_sys_cmp_l ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data;
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );
        object_unref ((Object*) l_type);

        if ( (*(unsigned int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0))
            < (*(unsigned int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0)) )
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 1;
        else
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 0;

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_cmp_g ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data;
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );
        object_unref ((Object*) l_type);

        if ( (*(unsigned int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0))
            > (*(unsigned int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0)) )
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 1;
        else
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 0;

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_cmp_le ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data;
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );
        object_unref ((Object*) l_type);

        if ( (*(unsigned int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0))
                <= (*(unsigned int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0)) )
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 1;
        else
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 0;

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_cmp_ge ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data;
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );
        object_unref ((Object*) l_type);

        if ( (*(unsigned int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0))
                >= (*(unsigned int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0)) )
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 1;
        else
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 0;

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_cmp_ne ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data;
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );
        object_unref ((Object*) l_type);

        if ( (*(unsigned int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0))
            != (*(unsigned int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0)) )
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 1;
        else
            (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 0;

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_cmp_e ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data;
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );
        object_unref ((Object*) l_type);

        if ( (*(unsigned int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0))
                == (*(unsigned int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0)) )
                (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 1;
        else
                (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) = 0;

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_block ( FinCNode* p_node )
{
        FinCNode * l_node;
        unsigned int l_size;
        unsigned int i;

        l_size = (p_node->vector_node)->size;

        for ( i = 0; i < l_size; i++ )
        {
                l_node = (FinCNode*)vector_at ( p_node->vector_node, i );
                finc_node_evaluate ( l_node );
                object_unref ((Object*) l_node);
        }
}

void finc_sys_comma( FinCNode* p_node)
{
        FinCNode* l_node1;
        FinCNode* l_node2;
        FinCType* l_type;
        FinCData* l_data;

        l_node1 = (FinCNode*)vector_at (p_node->vector_node, 0);
        l_node2 = (FinCNode*)vector_at (p_node->vector_node, 1);

        finc_node_evaluate (l_node1);
        finc_node_evaluate (l_node2);

        l_type = finc_type_new (l_node2->data->type->type, FinCArrayType_None, 0);
        l_data = finc_data_new (l_type, ((void *)0));
        object_unref ((Object*) l_type);
        object_unref ((Object*) l_node1);

        object_unref ((Object*) p_node->data);
        finc_data_assign(l_data, l_node2->data);
        object_unref ((Object*) l_node2);

        p_node->data = l_data;
}

void finc_sys_condition( FinCNode* p_node )
{
        FinCNode* l_node1;
        FinCNode* l_node2;
        FinCNode* l_node3;
        FinCType* l_type;
        FinCData* l_data;

        l_node1 = (FinCNode*)vector_at (p_node->vector_node, 0);
        l_node2 = (FinCNode*)vector_at (p_node->vector_node, 1);
        l_node3 = (FinCNode*)vector_at (p_node->vector_node, 2);

        finc_node_evaluate (l_node1);
        if ( (*(Bool*)((unsigned char*)l_node1->data? ((ADT)(l_node1->data)->raw) : ((void *)0) + 0)) )
        {
                finc_node_evaluate ( l_node2 );
                l_type = finc_type_new(l_node2->data->type->type, FinCArrayType_None, 0);
                l_data = finc_data_new(l_type, ((void *)0));
                object_unref ((Object*) l_type);

                finc_data_assign(l_data, l_node2->data);
                p_node->data = l_data;
        }
        else
        {
                finc_node_evaluate ( l_node3 );
                l_type = finc_type_new(l_node3->data->type->type, FinCArrayType_None, 0);
                l_data = finc_data_new(l_type, ((void *)0));
                object_unref ((Object*) l_type);

                finc_data_assign(l_data, l_node3->data);
                p_node->data = l_data;
        }

        object_unref ((Object*) l_node1);
        object_unref ((Object*) l_node2);
        object_unref ((Object*) l_node3);
}

void finc_sys_logic_or ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data;
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );
        object_unref ((Object*) l_type);

        (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) ||
                (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_logic_and ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data;
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );
        object_unref ((Object*) l_type);

        (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) &&
                (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_not ( FinCNode* p_node )
{
        FinCNode * l_node;
        FinCType* l_type;
        FinCData* l_data;

        l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        finc_node_evaluate ( l_node );

        l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
        l_data = finc_data_new ( l_type, ((void *)0) );

        (*(Bool*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0))
                = ! (*(Bool*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0));

        object_unref ((Object*) l_node);
        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_or ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) |
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) |
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) |
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1086 "fincsys.c"
        default:
                printf("this data type not support OR operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_and ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) &
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) &
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) &
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1170 "fincsys.c"
        default:
                printf("this data type not support AND operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_xor ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) ^
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) ^
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) ^
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1254 "fincsys.c"
        default:
                printf("this data type not support XOR operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_bitwise ( FinCNode* p_node )
{
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_right;

        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_right->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        ~ (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        ~ (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        ~ (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1328 "fincsys.c"
        default:
                printf("this data type not support BIT NEGATIVE operation.\n");
                break;
        }

        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_shl ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) <<
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) <<
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) <<
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1410 "fincsys.c"
        default:
                printf("this data type not support SHIFT LEFT operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_shr ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) >>
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) >>
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) >>
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1494 "fincsys.c"
        default:
                printf("this data type not support SHIFT RIGHT operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_add ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) +
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) +
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) +
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1568 "fincsys.c"
        case FinCType_Float:
                l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(float*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(float*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) +
                        (*(float*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1589 "fincsys.c"
        default:
                printf("this data type not support ADD operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_sub ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) -
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) -
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) -
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1663 "fincsys.c"
        case FinCType_Float:
                l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(float*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(float*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) -
                        (*(float*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1684 "fincsys.c"
        default:
                printf("this data type not support SUB operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_mul ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) *
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) *
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) *
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1758 "fincsys.c"
        case FinCType_Float:
                l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(float*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(float*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) *
                        (*(float*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1779 "fincsys.c"
        default:
                printf("this data type not support MUL operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_div ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) /
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) /
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) /
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1853 "fincsys.c"
        case FinCType_Float:
                l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(float*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(float*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) /
                        (*(float*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1874 "fincsys.c"
        default:
                printf("this data type not support DIV operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_mod ( FinCNode* p_node )
{
        FinCNode * l_left;
        FinCNode* l_right;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);
        FinCData* l_data_left;
        FinCData* l_data_right;

        l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

        finc_node_evaluate ( l_left );
        l_data_left = finc_node_take_data (l_left);
        finc_node_evaluate ( l_right );
        l_data_right = finc_node_take_data (l_right);

        switch ( l_data_left->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(int*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) %
                        (*(int*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(char*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) %
                        (*(char*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        (*(short*)((unsigned char*)l_data_left? ((ADT)(l_data_left)->raw) : ((void *)0) + 0)) %
                        (*(short*)((unsigned char*)l_data_right? ((ADT)(l_data_right)->raw) : ((void *)0) + 0));
                break;
# 1948 "fincsys.c"
        case FinCType_Float:
                l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(float*)((unsigned char*)l_data->raw + 0)) =
                        (*(float*)((unsigned char*)l_data_left->raw + 0)) %
                        (*(float*)((unsigned char*)l_data_right->raw + 0));
                break;
# 1969 "fincsys.c"
        default:
                printf("this data type not support MOD operation.\n");
                break;
        }

        object_unref ((Object*) l_left);
        object_unref ((Object*) l_right);
        object_unref ((Object*) l_data_left);
        object_unref ((Object*) l_data_right);

        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}

void finc_sys_negative( FinCNode* p_node )
{
        FinCNode* l_node;
        FinCType* l_type;
        FinCData* l_data = ((void *)0);

        l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
        finc_node_evaluate ( l_node );

        switch ( l_node->data->type->type )
        {
        case FinCType_Int:
                l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(int*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        - (*(int*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Char:
                l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(char*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        - (*(char*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0));
                break;

        case FinCType_Short:
                l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(short*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        - (*(short*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0));
                break;
# 2031 "fincsys.c"
        case FinCType_Float:
                l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
                l_data = finc_data_new ( l_type, ((void *)0) );
                object_unref ((Object*) l_type);

                (*(float*)((unsigned char*)l_data? ((ADT)(l_data)->raw) : ((void *)0) + 0)) =
                        - (*(float*)((unsigned char*)l_node->data? ((ADT)(l_node->data)->raw) : ((void *)0) + 0));
                break;
# 2050 "fincsys.c"
        default:
                printf("this data type not support MOD operation.\n");
                break;
        }

        object_unref ((Object*) l_node);
        object_unref ((Object*) p_node->data);
        p_node->data = l_data;
}
