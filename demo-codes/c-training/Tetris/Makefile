# make
# 2010-8-30

obj = main.o fb.o rand.o draw_block.o
# obj += div.o

target = main

CC = gcc
#CC = amr-linux-gcc
CFLAGS = -Wall -g -c
LDFLAGS = -Wall -g

all: $(target)

$(target): $(obj)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	-rm -f $(obj)
	-rm -f $(target)

.PHONY: clean all
