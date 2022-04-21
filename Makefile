SOURCES = ${wildcard boot.s kernel/*.c kernel/*.s drivers/*.c drivers/*.s cpu/*.c cpu/*.s util/*.c util/*.s}

__OBJ = ${SOURCES:.c=.o}
_OBJ = ${__OBJ:.s=.o}
OBJ = ${_OBJ:%=build/%}

CC = i686-elf-gcc
AS = nasm
LD = i686-elf-gcc
QEMU = qemu-system-i386
GDB = gdb

CFLAGS = -g -masm=intel -ffreestanding -c -Wall -Wextra -Werror
NASM_FLAGS = -f elf -g -O0
LDFLAGS = -T linker.ld -nostdlib -lgcc

KERNEL = isodir/boot/kernel.elf
ISO = os.iso
ISODIR = ${shell find isodir}

${ISO}: ${ISODIR} ${KERNEL}
	grub-mkrescue -o $@ isodir

run: ${ISO}
	${QEMU} -boot d -cdrom ${ISO}

debug: ${ISO}
	${QEMU} -s -S -boot d -cdrom ${ISO} \
	& ${GDB} -q -symbols=${KERNEL} -ex "target remote localhost:1234"

${KERNEL}: ${OBJ}
	${LD} ${LDFLAGS} -o $@ ${OBJ}

build/%.o: %.c
	${CC} ${CFLAGS} $< -o $@

build/%.o: %.s
	${AS} ${NASM_FLAGS} $< -o $@

clean:
	rm -rf build/os.iso
	rm -rf ${KERNEL}
	rm -rf ${OBJ}