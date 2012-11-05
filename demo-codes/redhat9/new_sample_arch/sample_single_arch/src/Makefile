
TARGET = sample_single_arch

all: $(TARGET)
	
SUBDIRS		= serial net chat room main

$(TARGET):	
	@set -e; for i in $(SUBDIRS); do $(MAKE) -C $$i all_targets; done

clean:
	@set -e; for i in $(SUBDIRS); do $(MAKE) -C $$i clean; done

dep:
	@set -e; for i in $(SUBDIRS); do $(MAKE) -C $$i fastdep; done

.PHONY: test
test:
	@set -e; for i in main; do $(MAKE) -C $$i test; done


