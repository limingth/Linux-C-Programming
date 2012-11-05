
all: step1 step2 step3 step4 step5

simple:
	gcc -o hello hello.c 

step1:
	gcc -E -o hello.cpp hello.c

step2:
	gcc -O0 -S -o hello.s hello.cpp

step3:
	gcc -c -o hello.o hello.s
	as -o hello-as.o hello.s

step4:
	gcc -dynamic -o hello-dynamic.elf hello.o 

	ld -dynamic-linker /lib/ld-linux.so.2 -o hello-ld.elf \
	/usr/lib/crt1.o \
	/usr/lib/crti.o \
	/usr/lib/gcc-lib/i386-redhat-linux/3.2.2/crtbegin.o \
	-L /usr/lib \
	-L /usr/lib/gcc-lib/i386-redhat-linux/3.2.2 \
	hello-as.o -lgcc -lc /usr/lib/gcc-lib/i386-redhat-linux/3.2.2/crtend.o \
	/usr/lib/crtn.o

	ld -O0 -static \
	/usr/lib/crt1.o \
	/usr/lib/crti.o \
	-o hello-static.elf hello-as.o \
	/usr/lib/libc.a \
	/usr/lib/gcc-lib/i386-redhat-linux/3.2.2/libgcc.a \
	/usr/lib/crtn.o


step5:
	gcc -O0 -static -o hello.elf hello.c
	
clean:
	rm *.elf
	rm *.o
