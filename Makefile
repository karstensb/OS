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

CFLAGS = -g -masm=intel -ffreestanding -c -I$(CURDIR) -O0 -mgeneral-regs-only
CFLAGS += -Wall -Wextra -Werror
ASFLAGS = -f elf -g -O0 -Wall -Werror
LDFLAGS = -nostdlib -lgcc

ISO = out/os.iso
KERNEL = out/kernel.elf
SYMBOLS = out/symbols.sym

all: iso

run: iso
	$(QEMU) -boot d -cdrom $(ISO) -m 128M

debug: iso
	$(QEMU) -boot d -d int -D qemu.log -s -S -cdrom $(ISO) -m 128M\
	& $(GDB) -q -symbols=$(KERNEL) -ex "target remote localhost:1234"

bochs: iso symbols
	$(BOCHS) -f bochsrc -q


iso: isodir kernel
	cp $(KERNEL) isodir/boot/kernel.elf
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue isodir -o $(ISO)

kernel: build out linker.ld $(OBJ)
	$(LD) $(LDFLAGS) -T linker.ld -o $(KERNEL) $(OBJ)

symbols: kernel
	nm -a $(KERNEL) | sed "s/ . / /" > $(SYMBOLS)


build:
	mkdir -p build/cpu
	mkdir -p build/drivers
	mkdir -p build/kernel
	mkdir -p build/util

out:
	mkdir -p out

isodir:
	mkdir -p isodir/boot/grub


build/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

build/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@


clean:
	$(RM) build
	$(RM) out
	$(RM) isodir
	$(RM) bochs.log
	$(RM) qemu.log