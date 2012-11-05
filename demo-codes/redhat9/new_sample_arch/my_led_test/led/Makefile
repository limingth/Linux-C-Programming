
all:
	gcc -c led_api.c -o led_api.o
	gcc -c led_driver.c -o led_driver.o
	ld -r led_api.o led_driver.o -o led.o

clean:
	-rm -rf *.o 
