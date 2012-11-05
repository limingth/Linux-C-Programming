
all:
	gcc main.c add.c sub.c -o demo

all2:
	gcc -c main.c -o main.o
	gcc -c add.c -o add.o
	gcc -c sub.c -o sub.o
	gcc main.o add.o sub.o -o demo2

clean:
	-rm *.o -rf
