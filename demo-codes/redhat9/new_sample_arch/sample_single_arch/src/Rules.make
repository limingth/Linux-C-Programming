#
# This file contains rules which are shared between multiple Makefiles.
#

include ../dir.config
include $(SRC_DIR)/arch.config

ALL_INC_DIR = -I$(SRC_DIR)/serial -I$(SRC_DIR)/net -I$(SRC_DIR)/chat -I$(SRC_DIR)/room

all_targets:  $(O_OBJS) $(O_TARGET) $(ARCH).test_$(PRJ)

%.o: %.c
	@echo -e "\nCompiling... $<"
	$(CC) $(ALL_INC_DIR) $(CFLAGS) $(EXTRA_CFLAGS) -c -o $@ $<

# Rule to compile a set of .o files into one .o file
#
ifeq (.depend,$(wildcard .depend))
include .depend
else
.depend:	fastdep	
endif

ifneq ($(O_TARGET),$(O_OBJS))
$(O_TARGET): .depend $(O_OBJS)
	@echo -e "\nArchieving..."
	@echo $(O_OBJS) " ==> " $@
#	$(AR) $(EXTRA_LDFLAGS) -rv $@ $(O_OBJS)
	$(LD) $(LDFLAGS) -r -o $@ $(O_OBJS)
else
$(O_TARGET): .depend
endif
#

SYSLIBS=-lpthread

all:	$(O_OBJS)
	echo all

$(ARCH).test_$(PRJ):    $(O_TARGET) $(TEST_OBJS) $(DEP_OBJS)
	@echo -e "\nLinking... $^ --> $@"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(ARCH).test_$(PRJ) $(TEST_OBJS) $(SYSLIBS) $(DEP_OBJS) $(O_TARGET) 
	@echo "Next you can put image to board and test it! "

.PHONY: test
test:   
	echo test
	make $(ARCH).test_$(PRJ)
	@echo -e "\nTesting... $^"
	./$(ARCH).test_$(PRJ) 

# Rule to compile a set of .o files into one .a file
#
ifdef L_TARGET
$(L_TARGET): $(LX_OBJS) $(L_OBJS) 
	rm -f $@
	$(AR) $(EXTRA_ARFLAGS) rcs $@ $(LX_OBJS) $(L_OBJS)
endif

#
# This make dependencies quickly
#
fastdep: dummy
	@echo "make fastdep"
	if [ -n "$(wildcard *.[chS])" ]; then \
	$(SCRIPTS_DIR)/mkdep *.[chS] > .depend; fi
	if [ -n "$(wildcard *.cpp)" ]; then \
	$(SCRIPTS_DIR)/mkdep *.cpp >> .depend; fi

#
# A rule to make subdirectories
#
sub_dirs: dummy
ifdef SUB_DIRS
	set -e; for i in $(SUB_DIRS); do $(MAKE) -C $$i; done
endif
#
# A rule to do nothing
#
dummy:

config:
	cd $(ROOT_DIR); make config

c clean:
	rm -f *.o
	rm -f *.a
	rm -f *.gdb
	rm -f .depend
	rm -f test
	rm -f core
	rm -f *.elf
	rm -f *.elf2flt	
	rm -f i386*.*
	rm -f arm*.*

