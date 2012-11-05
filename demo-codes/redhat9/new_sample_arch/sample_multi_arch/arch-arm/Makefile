#
#  makefile 
#  the makefile for a very simple AT91 port 
#
#  Bugs Report:  li ming (lmcs00@mails.tsinghua.edu.cn)
#  Release:      2003-02-13 19:43:33
#

# define this project information
PRJ_NAME = sample_test

# define building objs for this project

APP_FILES	= ../src/main/main.c ../src/serial/serial.c ../src/net/net.c

OBJS_FILES	= $(ARCH_FILES) $(LIB_FILES) $(APP_FILES)

OBJS 		= $(notdir $(OBJS_FILES:.c=.o))

# define include dir-names
INCDIR	= -I../src/serial -I../src/net

# define compiling and linking FLAGS
CPFLAGS := -Wall -Wstrict-prototypes -Wno-trigraphs -g  -fno-strict-aliasing -fno-common -fno-common -pipe -fno-builtin -g -mapcs-32 -march=armv4 -mtune=arm7tdmi 
ASFLAGS := -D__ASSEMBLY__ -DNO_MM -g -mapcs-32 -marmv4 -msoft-float -mno-fpu -g
LDFLAGS := -elf2flt

# include the all-project-shared file 
include Rules.make
