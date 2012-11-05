
all:
	gcc -c beep_api.c
	gcc -c beep_driver.c
	ld -r -o beep.o beep_api.o beep_driver.o

clean:
	rm -rf *.o
