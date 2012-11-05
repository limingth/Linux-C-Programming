
simple:
	gcc -o main main.c 
	gcc -S -o main.s main.c 
	gcc -E -o main.cpp main.c 
	gcc -c -o main.o main.c 

all:
	objdump -D main > main.lst

t:
	./main
