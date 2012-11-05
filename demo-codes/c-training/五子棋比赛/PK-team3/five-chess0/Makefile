all:
	gcc -Wall five_chess.c -o demo -g

clean:
	-rm *.o *.gz *.bak

run:
	./demo

release:
	make clean
	tar zcvf five-chess.0.1.tar.gz ../five-chess/*
