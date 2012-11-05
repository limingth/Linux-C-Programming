
all:
	gcc main.c add.c sub.c -o demo

all2:
	gcc -c main.c -o main.o
	gcc -c add.c -o add.o
	gcc -c sub.c -o sub.o
	gcc main.o add.o sub.o -o demo2

step:
	objdump -S -j .text demo > text.lst	
	objdump -S -j .rodata demo > rodata.lst	
	objdump -S -j .data demo > data.lst

clean:
	-rm *.o -rf
	-rm *.i -rf
	-rm *.s -rf
	-rm *.lst -rf
	-rm demo* -rf
