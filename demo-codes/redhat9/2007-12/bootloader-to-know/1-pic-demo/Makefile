
all:
	gcc main.c add.c sub.c -o demo

all2:
	gcc -c main.c -o main.o
	gcc -c add.c -o add.o
	gcc -c sub.c -o sub.o
	gcc main.o add.o sub.o -o demo2

step: all2
	objdump -d add.o > add.lst
	objdump -d sub.o > sub.lst
	objdump -d main.o > main.lst
	objdump -d demo > demo.lst

clean:
	-rm *.o -rf
	-rm *.i -rf
	-rm *.s -rf
	-rm *.lst -rf
	-rm demo* -rf
