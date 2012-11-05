# Makefile for building FinC
#     Project: FinC

include ../config.mk

CFLAGS	+= -g -I../include
LFLAGS	+= -g

PROJECT	=interpreter

OBJECTS	=interpreter.o

FINCLIB =../lib/libfinc.a

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(PROJECT)

$(PROJECT):$(OBJECTS) $(FINCLIB)
	gcc -o $(PROJECT) $(LFLAGS) $(OBJECTS) $(FINCLIB)

$(FINCLIB):
	make -C ..

clean:
	-rm -f $(OBJECTS) $(PROJECT)
	-rm -f *~ core
