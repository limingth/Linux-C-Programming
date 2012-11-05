CC = gcc
Project = elf2symbol
OBJ = elf2symbol.o

all: $(OBJ)
	$(CC) -O2 -o $(Project) $(OBJ)

elf2symbol.o: 
	$(CC) -O2 -c elf2symbol.c

clean:
	rm *.o $(Project)
