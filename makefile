include config.mk

default: kernel mbr

.PHONY: kernel mbr dep clean

kernel:
	$(MAKE) -C kernel

mbr:
	$(MAKE) -C mbr

dep:
	$(MAKE) -C kernel dep
	$(MAKE) -C mbr dep

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C mbr clean
