####################################
# This intends to be a simple test suit for RISC-V Vector Extension (RVV)
# licensed under BSD-3-Clause
####################################

####################
# basic info
####################

CROSS_PATH = /Users/cgk/ownCloud/课程/一生一芯/ict/rvv-llvm/dir/bin
PREFIX = llvm-
CC = ${CROSS_PATH}/clang
OBJCOPY = ${CROSS_PATH}/${PREFIX}objcopy
OBJDUMP = ${CROSS_PATH}/${PREFIX}objdump
LDSCRIPT = linker.ld

C_SOURCES = $(shell find ./ -name '*.S')

# BUILD_DIR = build

# Note that we use clang to compile RVV assembly
CFLAGS = -menable-experimental-extensions -march=rv64gv1p0 -nostdlib -T ${LDSCRIPT}

####################
# build rules
####################

OBJECTS = $(notdir $(C_SOURCES:.S=.elf))
OBJECTS_BIN = $(OBJECTS:.elf=.bin)
OBJECTS_DISASSEMBLY = $(OBJECTS:.elf=.disass)

all: VIRTUAL_TARGET

${OBJECTS}: %.elf: %.S
	$(CC) $< $(CFLAGS) -o $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.disass: %.elf
	$(OBJDUMP) -d $< > $@

DEBUG: ${OBJECTS}
	@echo "DEBUG"
	@echo $<

VIRTUAL_TARGET: ${DEBUG} ${OBJECTS} ${OBJECTS_BIN} ${OBJECTS_DISASSEMBLY}
	@echo "Volia!"

clean:
	rm *.elf
	rm *.bin
	rm *.disass