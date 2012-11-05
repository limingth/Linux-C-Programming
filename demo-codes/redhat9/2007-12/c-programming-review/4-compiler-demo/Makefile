
all:
	gcc main.c add.c sub.c -o demo

all2:
	gcc -c main.c -o main.o
	gcc -c add.c -o add.o
	gcc -c sub.c -o sub.o
	gcc main.o add.o sub.o -o demo2

step: step1 step2 step3 step4 step5

step1:
	gcc -E main.c -o main.i
	gcc -E add.c -o add.i
	gcc -E sub.c -o sub.i
	#cpp main.c 
	#cpp add.c
	#cpp sub.c

step2:
	gcc -S main.c -o main.s
	gcc -S add.c -o add.s
	gcc -S sub.c -o sub.s

step3:
	as main.s -o main.o 
	as add.s -o add.o 
	as sub.s -o sub.o 

step4:
	ld -static /usr/lib/crt1.o /usr/lib/crti.o \
	main.o add.o sub.o -o demo3 \
	/usr/lib/libc.a /usr/lib/gcc-lib/i386-redhat-linux/3.2.2/libgcc.a /usr/lib/crtn.o 

step5:
	ld -dynamic-linker /lib/ld-linux.so.2 -o demo4 \
	/usr/lib/crt1.o \
	/usr/lib/crti.o \
	/usr/lib/gcc-lib/i386-redhat-linux/3.2.2/crtbegin.o \
	-L /usr/lib \
	-L /usr/lib/gcc-lib/i386-redhat-linux/3.2.2 \
	main.o add.o sub.o -lgcc -lc /usr/lib/gcc-lib/i386-redhat-linux/3.2.2/crtend.o \
	/usr/lib/crtn.o	
	
clean:
	-rm *.o -rf
	-rm *.i -rf
	-rm *.s -rf
	-rm demo* -rf
