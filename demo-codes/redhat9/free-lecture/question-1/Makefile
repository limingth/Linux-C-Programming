all:
	gcc main1.c -o demo1
	gcc main2.c -o demo2

t:
	ls -l 

lst:
	objdump -d demo1 > 1.lst
	objdump -d demo2 > 2.lst
	objdump -S -j .rodata demo2 >> 2.lst
	objdump -S -j .data demo2 >> 2.lst

clean:
	rm *.lst
