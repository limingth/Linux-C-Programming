all:
	gcc -Wall five_chess.c draw.c libm.so.6 -o demo

clean:
	-rm *.o *.gz *.bak

run:
	./demo

release:
	make clean
	tar zcvf five-chess.0.1.tar.gz ../five-chess/*
