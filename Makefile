SOURCES = $(wildcard kernel/*.c kernel/*.s drivers/*.c drivers/*.s cpu/*.c cpu/*.s util/*.c util/*.s)

__OBJ = $(SOURCES:.c=.o)
_OBJ = $(__OBJ:.s=.o)
OBJ = $(_OBJ:%=$(BUILD)/%)

CC = i686-elf-gcc
AS = nasm
LD = i686-elf-gcc
QEMU = qemu-system-i386
GDB = gdb
RM = rm -rf

CFLAGS = -g -masm=intel -ffreestanding -c -I$(CURDIR) -Wall -Wextra -Werror
ASFLAGS = -f elf -g -O0 -Wall -Werror
LDFLAGS = -nostdlib -lgcc
QEMU_FLAGS = -boot d -d int -D $(QEMU_LOG)

BUILD = build
KERNEL = kernel.elf
ISO = os.iso
ISODIR = $(shell find isodir)
LINKER_LD = linker.ld
QEMU_LOG = qemu_log.txt

$(ISO): $(ISODIR) $(KERNEL)
	cp $(KERNEL) isodir/boot/kernel.elf
	grub-mkrescue -o $@ $(ISODIR)

run: $(ISO)
	$(QEMU) $(QEMU_FLAGS) -cdrom $(ISO)

debug: $(ISO)
	$(QEMU) $(QEMU_FLAGS) -s -S -cdrom $(ISO)\
	& $(GDB) -q -symbols=$(KERNEL) -ex "target remote localhost:1234"

$(KERNEL): $(BUILD) $(OBJ) $(LINKER_LD)
	$(LD) $(LDFLAGS) -T $(LINKER_LD) -o $@ $(OBJ)

$(BUILD):
	mkdir -p $(BUILD)/cpu
	mkdir -p $(BUILD)/drivers
	mkdir -p $(BUILD)/kernel
	mkdir -p $(BUILD)/util

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(BUILD)
	$(RM) $(ISO)
	$(RM) $(QEMU_LOG)
	$(RM) $(KERNEL)
	$(RM) isodir/boot/kernel.elf
	$(RM) $(OBJ)