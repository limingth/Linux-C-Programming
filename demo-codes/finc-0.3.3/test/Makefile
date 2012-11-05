# Makefile for building FinC
#     Project: FinC

CC		=gcc

#CFLAGS		=-O2 -I../src -I./ -I../tinylib
#LFLAGS		=
CFLAGS		=-g 
LFLAGS		=-g
PROJECT 	=pkgtest.so

OBJECTS = pkgtest.o

all: $(PROJECT)

$(PROJECT):$(OBJECTS)
	$(CC) -shared -o $(PROJECT) $(OBJECTS)

clean:
	-rm -f $(OBJECTS) $(PROJECT)
	-rm -f *~ core
