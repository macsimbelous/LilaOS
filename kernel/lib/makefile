OBJS=printf.o string.o xtox.o stack.o

default: lib.o

.PHONY: dep clean

clean:
	$(DEL) *.o
	$(DEL) depend

dep:
	$(CC) $(DEPFLAGS) -I$(INCDIR) $(wildcard   *.S) $(wildcard   *.s) $(wildcard   *.c) > depend


lib.o: $(OBJS)
	$(LD) $(LDFLAGS_O) -olib.o $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) $<

%.o: %.S
	$(CC) $(CFLAGS) -I$(INCDIR) $<

%.o: %.s
	$(CC) $(CFLAGS) -I$(INCDIR) $<

include $(wildcard   depend)
