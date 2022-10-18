SOURCES = $(wildcard kernel/*.c kernel/*.s drivers/*.c drivers/*.s cpu/*.c cpu/*.s util/*.c util/*.s)

OBJ = $(SOURCES:%=build/%.o)

CC = i686-elf-gcc
AS = nasm
LD = i686-elf-gcc
QEMU = qemu-system-i386
GDB = gdb
RM = rm -rf

CFLAGS = -g -masm=intel -ffreestanding -c -I$(CURDIR) -O0 -mgeneral-regs-only
CFLAGS += -std=gnu17 -Wall -Wextra -Werror
ASFLAGS = -f elf -g -O0 -Wall -Werror
LDFLAGS = -nostdlib -lgcc
QEMU_FLAGS = -d int -M smm=off -D qemu.log -m 128M -machine q35
QEMU_FLAGS += -cdrom $(ISO) -boot d

ISO = out/os.iso
KERNEL = out/kernel.elf

all: iso

run: iso
	$(QEMU) $(QEMU_FLAGS) 

debug: iso
	$(QEMU) $(QEMU_FLAGS) -s -S \
	& $(GDB) -q -symbols=$(KERNEL) -ex "target remote localhost:1234"

iso: kernel isodir
	cp $(KERNEL) build/isodir/boot/kernel.elf
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	grub-mkrescue build/isodir -o $(ISO)

kernel: dirs linker.ld $(OBJ)
	$(LD) $(LDFLAGS) -T linker.ld -o $(KERNEL) $(OBJ)

dirs:
	mkdir -p build/cpu
	mkdir -p build/drivers
	mkdir -p build/kernel
	mkdir -p build/util
	mkdir -p out

isodir: dirs
	mkdir -p build/isodir/boot/grub


build/%.c.o: %.c
	$(CC) $(CFLAGS) $< -o $@

build/%.s.o: %.s
	$(AS) $(ASFLAGS) $< -o $@


clean:
	$(RM) build
	$(RM) out
	$(RM) qemu.log
