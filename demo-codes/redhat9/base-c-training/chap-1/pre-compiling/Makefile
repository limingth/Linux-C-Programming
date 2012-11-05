
simple:
	gcc -o hello hello.c 

all: step1 step2 step3 step4 step5

step1:
	gcc -E -o hello.cpp hello.c

step2:
	gcc -S -o hello.s hello.cpp

step3:
	gcc -c -o hello.o hello.s

step4:
	gcc -o hello.elf hello.o 

step5:
	gcc -static -o hello.static.elf hello.c
	
