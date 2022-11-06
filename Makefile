SOURCES = $(wildcard */*.c */*.S)
OBJ = $(SOURCES:%=build/%.o)

CC = i686-elf-gcc
QEMU = qemu-system-i386
GDB = gdb
RM = rm -rf

CFLAGS += -g -ffreestanding -I$(CURDIR) -Og -mgeneral-regs-only
CFLAGS += -std=gnu17 -Wall -Wextra -Werror -Wno-unused-function
CFLAGS += -nostdlib -lgcc
QEMU_FLAGS += -m 128M -machine q35 -cdrom $(ISO) -boot d -no-reboot
QEMU_FLAGS += -d int -M smm=off -trace events=trace_events.cfg -D qemu.log

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
	$(CC) $(CFLAGS) -T linker.ld -o $(KERNEL) $(OBJ)

dirs:
	mkdir -p build/cpu
	mkdir -p build/drivers
	mkdir -p build/kernel
	mkdir -p build/util
	mkdir -p out

isodir: dirs
	mkdir -p build/isodir/boot/grub


build/%.o: %
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) build
	$(RM) out
	$(RM) qemu.log
