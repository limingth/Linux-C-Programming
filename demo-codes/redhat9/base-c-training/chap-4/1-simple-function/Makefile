
all:
	gcc -S -o main.s main.c 
	gcc -c -o main.o main.c 
	gcc -o main main.c 
	objdump -d main > main.lst 
	objdump -d main.o > main.o.lst 

