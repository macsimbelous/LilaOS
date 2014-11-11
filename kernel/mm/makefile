OBJS=pmm.o heap.o

default: mm.o

.PHONY: dep clean

clean:
	$(DEL) *.o
	$(DEL) depend

dep:
	$(CC) $(DEPFLAGS) -I$(INCDIR) $(wildcard   *.S) $(wildcard   *.s) $(wildcard   *.c) > depend


mm.o: $(OBJS)
	$(LD) $(LDFLAGS_O) -omm.o $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) $<

%.o: %.S
	$(CC) $(CFLAGS) -I$(INCDIR) $<

%.o: %.s
	$(CC) $(CFLAGS) -I$(INCDIR) $<

include $(wildcard   depend)

