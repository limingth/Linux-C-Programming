# Makefile for building FinC
#     Project: FinC

include config.mk

DATE = $(shell date +%Y%m%d)
PWD  = $(shell basename $(shell pwd))

all: libfinc.a

clean:
	rm -f core
	make -C tiny clean
	make -C finc clean

sample: libfinc.a
	make -C embedded-sample

test:
	make -C test

libfinc.a:
	make -C tiny
	make -C finc
	$(AR) rcs lib/libfinc.a \
		finc/fincsys.o finc/fincdata.o finc/fincnode.o finc/fincfield.o finc/fincfunc.o finc/finclang.o finc/finccontext.o finc/finctype.o finc/fincvar.o finc/fincstruct.o finc/finclib.o finc/fincdebug.o finc/finctoken.o finc/fincparser.o \
		finc/finapi/fincarray.o finc/finapi/fincstring.o finc/finapi/netapi.o finc/finapi/fincutil.o \
		finc/avcall/avcall.o finc/avcall/structcpy.o \
		tiny/list.o tiny/mem.o tiny/object.o tiny/string.o tiny/hash.o tiny/vector.o tiny/stack.o tiny/library.o tiny/thread.o
	$(RANLIB) lib/libfinc.a

snapshort:
	rm -rf core
	rm -rf lib/libfinc.a
	make -C tiny clean
	make -C finc clean
	cd ..; tar jcvf $(PWD)-$(DATE).tar.bz2 $(PWD)

release:
	rm -rf core
	rm -rf lib/libfinc.a
	make -C tiny clean
	make -C finc clean
	cd ..; tar jcvf $(PWD).tar.bz2 $(PWD)