
all:
	gcc -Iled -Idip -c main.c
	make -C led
	make -C dip
	make -C int
	gcc main.o led/led.o dip/dip.o int/int.o -o demo

clean:
	make -C led clean
	make -C dip clean
	make -C int clean
	#make -C beep clean
	-rm -rf *.o
	-rm *.gdb
