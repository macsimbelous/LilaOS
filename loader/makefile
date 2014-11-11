include ../config.mk

LDFLAGS_B=-Ttext 0x00008000 -nostdlib

OBJS=asm.o main.o disk_io.o

default: loader

.PHONY: dep clean

clean:
	$(DEL) *.o
	$(DEL) loader
	$(DEL) depend

dep:
	$(CC) $(DEPFLAGS) -I$(INCDIR) $(wildcard   *.S) $(wildcard   *.s) $(wildcard   *.c) > depend


loader: $(OBJS)
	$(LD) $(LDFLAGS_B) -oloader $(OBJS)
	$(OBJCOPY) loader

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) $<

%.o: %.S
	$(CC) $(CFLAGS) -I$(INCDIR) $<

%.o: %.s
	$(CC) $(CFLAGS) -I$(INCDIR) $<

include $(wildcard depend)
