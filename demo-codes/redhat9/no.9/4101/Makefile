
all:
	gcc main.c add.c sub.c -o demo

t1:
	gcc -c main.c
	gcc -c add.c
	gcc -c sub.c
	gcc main.o add.o sub.o -o demo1

t2:
	gcc -S main.c
	gcc -S add.c
	gcc -S sub.c
	as -o main.o main.s
	as -o add.o add.s
	as -o sub.o sub.s
	gcc main.o add.o sub.o -o demo2
	ld main.o add.o sub.o -o demo3

t3:
	ld -static /usr/lib/crt1.o /usr/lib/crti.o \
	main.o add.o sub.o -o demo3 \
	/usr/lib/libc.a /usr/lib/crtn.o 

t31:
	ld /usr/lib/crt?.o  main.o add.o sub.o -o demo3 -lc -dynamic-linker /lib/ld-linux.so.2

t32:
	ld -static /usr/lib/crt1.o /usr/lib/crti.o \
	main.o add.o sub.o -o demo3 \
	/usr/lib/libc.a /usr/lib/gcc-lib/i386-redhat-linux/3.2.2/libgcc.a /usr/lib/crtn.o 

t4:
	ar -rv libmath.a add.o sub.o
	gcc main.o libmath.a -o demo4
	gcc main.o -o demo4 -lmath -L.
	
t5:
	nm add.o
	nm sub.o
	nm main.o
	nm demo

t6:
	objdump -d add.o > add.lst
	objdump -d sub.o > sub.lst
	objdump -d main.o > main.lst
	objdump -d demo > demo.lst

t7:
	objcopy -O binary --only-section=.text demo text.bin
	objcopy -O binary --only-section=.data demo data.bin
	objcopy -O binary --only-section=.rodata demo rodata.bin

t8:
	readelf -a add.o > add.readelf
	readelf -a demo	> demo.readelf

t9:
	ls -l demo
	strip demo
	ls -l demo
	./demo

clean:
	-rm *.o -rf
	-rm *.s -rf
	-rm demo*
	-rm *.a
	-rm *.lst
	-rm *.readelf
	-rm *.bin
