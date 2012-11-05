
all: 
	gcc -c -o hello.o hello.c
	gcc -o hello hello.o
	gcc -static -o hello2 hello.o

all2:
	gcc -o hello hello.c 

list:
	objdump -D hello > hello.lst

test:
	./hello
