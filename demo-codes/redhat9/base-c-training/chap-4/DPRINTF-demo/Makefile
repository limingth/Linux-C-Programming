
all:
	gcc -O1 -o hello hello.c 
	gcc -E -o hello.i hello.c 
	gcc -O1 -S -o hello.s hello.c 
	objdump -d hello > hello.lst

t:
	./hello
