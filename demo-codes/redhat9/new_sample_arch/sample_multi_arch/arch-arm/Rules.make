#
#  Rules.make
#  the rules for making any sample project
#
#  Bugs Report:  li ming (lmcs00@mails.tsinghua.edu.cn)
#  Release:      2003-02-13 19:10:25
#


	
# for building this project both on linux or cygwin
#CROSS_COMPILE = arm-linux-
CROSS_COMPILE = arm-elf-

# define rule for making .depend 
ifneq (.depend, $(wildcard .depend))
depend: dep
	@echo "Help: you can use use \"make dep\" to create .depend"
	
	
endif

# define some compiler names
CC		= $(CROSS_COMPILE)gcc
AS		= $(CROSS_COMPILE)gcc
AR		= $(CROSS_COMPILE)ar
LD		= $(CROSS_COMPILE)ld	
NM		= $(CROSS_COMPILE)nm
OBJDUMP		= $(CROSS_COMPILE)objdump
READELF		= $(CROSS_COMPILE)readelf
RM		= rm -f
RN		= mv
BIN		= $(CROSS_COMPILE)objcopy
CCDEP		= $(CROSS_COMPILE)gcc


# define the default rule for building any sample test
all: 	$(PRJ_NAME).elf
	@echo "Hint: now you can \"make test\" to debug $(PRJ_NAME).elf"

test: all
	#/skyeye $(PRJ_NAME).elf 
	arm-elf-objdump -d $(PRJ_NAME).elf.gdb > $(PRJ_NAME).lst
	arm-elf-gdb $(PRJ_NAME).elf.gdb
	
# put include .depend here to make "all" at the first place! 
ifeq (.depend, $(wildcard .depend))	
include .depend
endif

# define rules for build *.c & *.S files
%.o:
	@echo + compiling c file with .depend ... : $< 	
	@echo $(CC) -c $(CPFLAGS) $(INCDIR) $(<:.o=.c)
	@$(CC) -c $(CPFLAGS) $(INCDIR) $(<:.o=.c)
	@echo
	
config: 
	@echo -n "building target platform is " 
	@if test $(OSTYPE) = cygwin ;	then \
		echo "on cgywin!"; \
		echo CROSS_COMPILE = arm-linux- > $(CFG_FILE); \
		echo LIBPATH = -L/lib/gcc-lib/arm-linux/2.95.3/ -L/usr/arm-linux/lib >> $(CFG_FILE); \
	elif test $(OSTYPE) = linux-gnu ; then \
		echo "on linux!"; \
		echo CROSS_COMPILE = arm-elf- > $(CFG_FILE); \
		echo LIBPATH = -L/usr/local/lib/gcc-lib/arm-elf/2.95.3/ >> $(CFG_FILE); \
	else \
		echo " ???" ; \
		echo " ------------------------------------------  " ; \
		echo " I can not guess the host operation system" ; \
		echo " please set OSTYPE variable in rules.make !" ; \
		echo " or execute command export OSTYPE=linux-gnu " ; \
		echo " in bash shell, if your host system is linux." ; \
		echo " or execute commands export OSTYPE=cygwin " ; \
		echo " in cygwin bash shell, if your host system is cgwin." ; \
		echo " Then you should try make config again!" ; \
		echo " ------------------------------------------  " ; \
	fi ; 
#	@echo "creating cross-compiler config file: $(CFG_FILE) ... "
	@echo "Hint: next, you can \"make dep\" this project now..."
	
dep:	$(START_FILE) $(OBJS_FILES)
	@echo + making dep file ... : .depend
	@$(CCDEP) $(CFLAGS) $(INCDIR) -MM $^ > .depend || rm -f .depend
	@echo "Hint: next, you can \"make\" this project now..."

$(PRJ_NAME).elf: .depend $(DEP_FILES) $(START_OBJ) $(OBJS) 
	@echo + linking o file ... : $(START_OBJ) $(OBJS) "->" $(PRJ_NAME).elf
	$(CC) $(LDFLAGS) $(OBJS) -o $(PRJ_NAME).elf
	@echo

clean:		
		rm -f *.stackdump
		rm -f $(PRJ_NAME).elf
		rm -f $(PRJ_NAME).elf.gdb
		rm -f $(PRJ_NAME).s
		rm -f $(PRJ_NAME).r
		rm -f $(PRJ_NAME).n
		rm -f $(PRJ_NAME).lst
		rm -f $(START_OBJ)
		rm -f $(OBJS)
		
cleanall:	clean		
		rm -f $(CFG_FILE)
		rm -f *.bak
		rm -f .depend
	
t:
		echo ahah
