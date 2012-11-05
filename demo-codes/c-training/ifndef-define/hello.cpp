# 1 "hello.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "hello.c"
# 11 "hello.c"
# 1 "add.h" 1

# 1 "public.h" 1




int counter = 1;
# 3 "add.h" 2

int add( int, int );
# 12 "hello.c" 2
# 1 "sub.h" 1

# 1 "public.h" 1




int counter = 1;
# 3 "sub.h" 2

int sub( int, int );
# 13 "hello.c" 2

int main( int argc, char * argv[] )
{
        counter = 123;

        printf( "hello, Cruel World! \n" );
        printf( "MAX = %d \n", 5 );
        printf( "counter = %d \n", counter );

        return 0;
}
