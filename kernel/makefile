include config.mk

OBJS=core/core.o mm/mm.o lib/lib.o

default: kernel

.PHONY: dep clean

clean:
	$(MAKE) -C mm clean
	$(MAKE) -C core clean
	$(MAKE) -C lib clean
	$(DEL) kernel
	$(DEL) depend

dep:
	$(MAKE) -C mm dep
	$(MAKE) -C core dep
	$(MAKE) -C lib dep

kernel: $(OBJS)
	$(LD) $(LDFLAGS_B) -okernel $(OBJS)
	$(OBJCOPY) kernel

.PHONY: mm/mm.o

mm/mm.o:
	$(MAKE) -C mm

.PHONY: core/core.o

core/core.o:
	$(MAKE) -C core

.PHONY: lib/lib.o

lib/lib.o:
	$(MAKE) -C lib
