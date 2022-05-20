SOURCES = $(wildcard kernel/*.c kernel/*.s drivers/*.c drivers/*.s cpu/*.c cpu/*.s util/*.c util/*.s)

__OBJ = $(SOURCES:.c=.o)
_OBJ = $(__OBJ:.s=.o)
OBJ = $(_OBJ:%=build/%)

CC = i686-elf-gcc
AS = nasm
LD = i686-elf-gcc
OBJCOPY = i686-elf-objcopy
QEMU = qemu-system-i386
BOCHS = bochs
GDB = gdb
RM = rm -rf

CFLAGS = -g -masm=intel -ffreestanding -c -I$(CURDIR) -Wall -Wextra -Werror
ASFLAGS = -f elf -g -O0 -Wall -Werror
LDFLAGS = -nostdlib -lgcc

ISO = os.iso
KERNEL = kernel.elf
SYMBOLS = symbols.sym
ISODIR = $(shell find isodir)
LINKER_LD = linker.ld
QEMU_LOG = qemu.log
BOCHS_LOG = bochs.log

iso: $(ISODIR) kernel
	cp $(KERNEL) isodir/boot/kernel.elf
	grub-mkrescue isodir -o $(ISO)

run: iso
	$(QEMU) -boot d -cdrom $(ISO) -m 128M

debug: iso
	$(QEMU) -boot d -d int -D $(QEMU_LOG) -s -S -cdrom $(ISO) -m 128M\
	& $(GDB) -q -symbols=$(KERNEL) -ex "target remote localhost:1234"

bochs: iso symbols
	$(BOCHS) -f bochsrc -q

kernel: build $(OBJ) $(LINKER_LD)
	$(LD) $(LDFLAGS) -T $(LINKER_LD) -o $(KERNEL) $(OBJ)

symbols: kernel
	nm -a $(KERNEL) | sed "s/ . / /" > $(SYMBOLS)

build:
	mkdir -p build/cpu
	mkdir -p build/drivers
	mkdir -p build/kernel
	mkdir -p build/util

build/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

build/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) build
	$(RM) $(ISO)
	$(RM) $(QEMU_LOG)
	$(RM) $(BOCHS_LOG)
	$(RM) $(KERNEL)
	$(RM) $(SYMBOLS)
	$(RM) isodir/boot/kernel.elf