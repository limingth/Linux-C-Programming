PRJ = ucos

START_OBJ = startup.o
OBJS = startup.o main_entry.o irq_ven.o ucos_ii.o os_cpu_c.o os_cpu_a.o
SRC_DIR = ..\

AXF = $(PRJ).axf
BIN = $(PRJ).bin
UUE = $(PRJ).uue
LST = $(PRJ).lst

all: $(UUE)
	dir ..\ADS\$(PRJ)\$(PRJ)_Data\DebugRel\$(BIN)
	dir $(BIN)
	
cmp:
	comp $(BIN) ..\ADS\$(PRJ)\$(PRJ)_Data\DebugRel\$(BIN) 
		
.SUFFIXES: .s .c
{$(SRC_DIR)}.s.o:
	@echo + compiling s file ... $<
	armasm -keep -g $<
	@echo ------------------------------------------------------
				
{$(SRC_DIR)}.c.o:
	@echo + compiling c file ... $<
	armcc -O0 -g+ -c $<
	@echo ------------------------------------------------------

$(AXF): $(OBJS)
	@echo + linking o file ... $(OBJS)
	armlink $(OBJS) -first $(START_OBJ) -o $(AXF)
	@echo ------------------------------------------------------

$(BIN): $(AXF)
	@echo + fromelf axf file ... $(AXF)
	fromelf -c -bin -output $(BIN) $(AXF)
	fromelf -c -s -o $(PRJ).lst $(AXF)
	@echo ------------------------------------------------------

$(UUE): $(BIN)
	@echo + uuencode bin file ... $(BIN)
	uuencode $(BIN) $(UUE)
	@echo ------------------------------------------------------
	
c clean:
	@echo + deleting all files ... 
	-del $(OBJS)
	-del $(AXF) $(BIN) $(UUE)
	@echo ------------------------------------------------------
