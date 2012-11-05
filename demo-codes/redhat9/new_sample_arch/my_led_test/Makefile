
all:
	gcc -Iled -c main.c -o main.o
	make -C led
	gcc main.o led/led.o -o myled

clean:
	-rm -rf *.o
	make -C led clean

test:
	gcc -Iled main.c led/led_api.c led/led_driver.c -o myled
