ESDK=$(EPIPHANY_HOME)
ELIBS=$(ESDK)/tools/host/lib
EINCS=$(ESDK)/tools/host/include
ELDF=$(ESDK)/bsps/current/internal.ldf
BINS=benchmark tiempos 
DEPS=e_read.srec e_read_dma.srec
OBJS=e_read.elf  e_read_dma.elf

CC=gcc
ECC=e-gcc
EOC=e-objcopy
CFLAGS=-Wall -Wextra -pedantic -ggdb -O0 -std=c99 -Wl,-rpath,$(ELIBS)
EFLAGS=-funroll-loops -ffast-math
EOFLAGS=--srec-forceS3 --output-target srec


.PHONY: all clean


benchmark: benchmark.c sdram.h $(DEPS)
	$(CC) $(CFLAGS) -I$(EINCS) -L$(ELIBS) -o $@ $< -le-hal -lrt

%.elf: %.c
	$(ECC) $(CFLAGS) $(EFLAGS) -T $(ELDF) -o $@ $< -le-lib

%.srec: %.elf
	$(EOC) $(EOFLAGS) $< $@


all: $(BINS)

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(BINS)
