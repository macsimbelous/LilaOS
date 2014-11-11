OBJS=start.o main.o entry.o ints.o irq.o exceptions.o video.o timer.o cmd.o syscall.o dm.o fsm.o rd.o\
	rtc.o

default: core.o

.PHONY: dep clean

clean:
	$(DEL) *.o
	$(DEL) depend

dep:
	$(CC) $(DEPFLAGS) -I$(INCDIR) $(wildcard   *.S) $(wildcard   *.s) $(wildcard   *.c) > depend


core.o: $(OBJS)
	$(LD) $(LDFLAGS_O) -ocore.o $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) $<

%.o: %.S
	$(CC) $(CFLAGS) -I$(INCDIR) $<

%.o: %.s
	$(CC) $(CFLAGS) -I$(INCDIR) $<

include $(wildcard depend)
