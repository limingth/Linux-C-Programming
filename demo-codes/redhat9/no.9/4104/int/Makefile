
all:
	gcc -c -DTARGET_PC int.c
	gcc -c -DTARGET_PC test_int.c
	gcc int.o test_int.o -o int_test

clean:
	-rm -rf *.o
	-rm *_test
