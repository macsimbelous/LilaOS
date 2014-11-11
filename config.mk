export CPU=-march=pentium4
export CC=gcc -c
export CFLAGS=$(CPU) -Wall -nostdinc -ffreestanding -O2
export LD=ld
export LDFLAGS_O=-r -nostdlib
export LDFLAGS_B=-Ttext 0x00100000 -nostdlib
export OBJCOPY=objcopy -O binary
export COPY=cp
export DEL=rm -f
export TOPDIR:=$(shell pwd)
export INCDIR:=$(TOPDIR)/include
export VPATH:=$(INCDIR)
export DEPFLAGS=-M

