
#########################
# Makefile for Orange'S #
#########################

# Entry point of Orange'S
# It must have the same value with 'KernelEntryPointPhyAddr' in load.inc!
ENTRYPOINT	= 0x30400

# Offset of entry point in kernel file
# It depends on ENTRYPOINT
ENTRYOFFSET	=   0x400

# Programs, flags, etc.
ASM		= nasm
DASM	= ndisasm
CC		= gcc
LD		= ld
ASMBFLAGS	= -I boot/include/
ASMKFLAGS	= -I include/ -I include/sys/ -f elf
CFLAGS		= -I include/ -I include/sys/ -c -m32 -fno-builtin -fno-stack-protector
LDFLAGS		= -m elf_i386 -s -Ttext $(ENTRYPOINT)
DASMFLAGS	= -u -o $(ENTRYPOINT) -e $(ENTRYOFFSET)

# This Program
OSBOOT		= boot/boot.bin
OSLOADER	= boot/loader.bin
OSKERNEL	= kernel.bin

OBJS		= kernel/kernel.o \
			  kernel/clock.o \
			  kernel/console.o \
			  kernel/global.o \
			  kernel/hd.o \
			  kernel/i8259.o \
			  kernel/keyboard.o \
			  kernel/main.o \
			  kernel/proc.o \
			  kernel/protect.o \
			  kernel/start.o \
			  kernel/systask.o \
			  kernel/tty.o \
			  fs/main.o \
			  fs/misc.o \
			  fs/open.o \
			  lib/close.o \
			  lib/klib.o \
			  lib/kliba.o \
			  lib/misc.o \
			  lib/open.o \
			  lib/printf.o \
			  lib/string.o \
			  lib/syscall.o \
			  lib/vsprintf.o \
			  
DASMOUTPUT	= kernel.bin.asm

# Floppy 
IMG		:= a.img
FLOPPY	:= /mnt/floppy/

# All Phony Targets
.PHONY : everything final image clean realclean disasm all buildimg

# Default starting position
everything :  $(OSBOOT) $(OSLOADER) $(OSKERNEL)


all : realclean everything
final : all clean
image : final buildimg

clean :
	rm -f $(OBJS)
realclean :
	rm -f $(OBJS) $(OSBOOT) $(OSLOADER) $(OSKERNEL)
disasm :
	$(DASM) $(DASMFLAGS) $(OSKERNEL) > $(DASMOUTPUT)

# We assume that "a.img" exists in current folder
buildimg:
	dd if=$(OSBOOT) of=$(IMG) bs=512 count=1 conv=notrunc
	sudo mount -o loop $(IMG) $(FLOPPY)
	sudo cp -fv $(OSLOADER) $(FLOPPY)
	sudo cp -fv $(OSKERNEL) $(FLOPPY)
	sudo umount $(FLOPPY)
# boot
$(OSBOOT) : boot/boot.asm boot/include/load.inc boot/include/fat12hdr.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

# loader
$(OSLOADER): boot/loader.asm boot/include/load.inc \
			boot/include/fat12hdr.inc boot/include/pm.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

# link to kernel file
$(OSKERNEL) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(OSKERNEL) $(OBJS)

# compile asm file
%.o : %.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

# compile c file 使用静态模式
%.o : %.c 
	$(CC) $(CFLAGS) -o $@ $<

# kernel/clock.o: kernel/clock.c
# 	$(CC) $(CFLAGS) -o $@ $<
# kernel/global.o: kernel/global.c
# 	$(CC) $(CFLAGS) -o $@ $<
# kernel/i8259.o: kernel/i8259.c
# 	$(CC) $(CFLAGS) -o $@ $<
# kernel/main.o: kernel/main.c 
# 	$(CC) $(CFLAGS) -o $@ $<
# kernel/protect.o: kernel/protect.c
# 	$(CC) $(CFLAGS) -o $@ $<
# kernel/start.o: kernel/start.c 
# 	$(CC) $(CFLAGS) -o $@ $<

# lib/klib.o: lib/klib.c
# 	$(CC) $(CFLAGS) -o $@ $<

# kernel/kernel.o : kernel/kernel.asm include/sconst.inc
# 	$(ASM) $(ASMKFLAGS) -o $@ $<

# lib/kliba.o : lib/kliba.asm include/sconst.inc
# 	$(ASM) $(ASMKFLAGS) -o $@ $<

# lib/string.o : lib/string.asm
# 	$(ASM) $(ASMKFLAGS) -o $@ $<