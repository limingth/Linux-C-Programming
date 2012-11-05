# Makefile for building FinC
#     Project: FinC

include ../config.mk

CFLAGS		+= -I../include
PROJECT 	=libfinc.a
AVCALL		=libavcall.a

SOURCE	= fincsys.c \
	fincdata.c \
	fincnode.c \
	fincfield.c \
	fincfunc.c \
	finclang.c \
	finccontext.c \
	finctype.c \
	fincvar.c  \
	fincstruct.c \
	finclib.c \
	fincdebug.c \
	finctoken.c \
	fincparser.c \
	finapi/fincarray.c \
	finapi/fincstring.c \
	finapi/netapi.c \
	finapi/fincutil.c

OBJECTS = $(SOURCE:.c=.o)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(PROJECT)

$(PROJECT):$(OBJECTS) $(AVCALL)
	$(AR) rcs $(PROJECT) $(OBJECTS) avcall/avcall.o avcall/structcpy.o
	$(RANLIB) $(PROJECT)

ifeq ($(OSTYPE), msys)
libavcall.a:
	make -C avcall -f Makefile.mingw
else
libavcall.a:
	make -C avcall
endif

ifeq ($(OSTYPE), msys)
clean:
	make -C avcall -f Makefile.mingw clean
	-rm -f $(OBJECTS) $(PROJECT)
	-rm -f *~ core
else
	make -C avcall clean
	-rm -f $(OBJECTS) $(PROJECT)
	-rm -f *~ core
endif

install: $(PROJECT)
	cp -f libfinc.a ../../../lib/
