#CC = arm-elf-gcc
CC = gcc

all:	
	$(CC) main.c uart.c skyeye-printf.c skyeye-stdio.c -o demo
	$(CC) -DDEBUG main.c uart.c skyeye-printf.c skyeye-stdio.c -o debug-demo
	arm-elf-gcc -elf2flt -DEMBED main.c uart.c skyeye-printf.c skyeye-stdio.c -o uartprintf
clean:	
	-rm *.o -rf
	-rm demo -rf
