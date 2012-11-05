
all:
	gcc -c -DTARGET_PC beep.c
	gcc -c -DTARGET_PC test_beep.c
	gcc beep.o test_beep.o -o beep_test

clean:
	-rm -rf *.o
	-rm *_test
