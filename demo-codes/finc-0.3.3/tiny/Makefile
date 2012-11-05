# Makefile for building FinC
#     Project: FinC

include ../config.mk

CFLAGS		+= -I../include
PROJECT 	=libtiny.a

OBJECTS =list.o \
	mem.o \
	object.o \
	string.o \
	hash.o \
	vector.o \
	stack.o \
	library.o \
	thread.o

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(PROJECT)

$(PROJECT):$(OBJECTS)
	$(AR) rcs $(PROJECT) $(OBJECTS)
	$(RANLIB) $(PROJECT)

clean:
	-rm -f $(OBJECTS) $(PROJECT)
	-rm -f *~ core
