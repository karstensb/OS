SOURCES = ${wildcard kernel/*.c kernel/*.s drivers/*.c drivers/*.s cpu/*.c cpu/*.s util/*.c util/*.s}

__OBJ = ${SOURCES:.c=.o}
_OBJ = ${__OBJ:.s=.o}
OBJ = ${_OBJ:%=build/%}

CC = i686-elf-gcc
AS = nasm
LD = i686-elf-gcc
QEMU = qemu-system-i386
GDB = gdb

CFLAGS = -g -masm=intel -ffreestanding -c -I${CURDIR} -Wall -Wextra -Werror
NASM_FLAGS = -f elf -g -O0 -Wall -Werror
LDFLAGS = -nostdlib -lgcc
QEMU_FLAGS = -boot d -d int -D ${QEMU_LOG}

KERNEL = isodir/boot/kernel.elf
ISO = os.iso
ISODIR = ${shell find isodir}
LINKER_LD = linker.ld
QEMU_LOG = qemu_log.txt

${ISO}: ${ISODIR} ${KERNEL}
	grub-mkrescue -o $@ ISODIR

run: ${ISO}
	${QEMU} ${QEMU_FLAGS} -cdrom ${ISO}

debug: ${ISO}
	${QEMU} ${QEMU_FLAGS} -s -S -cdrom ${ISO}\
	& ${GDB} -q -symbols=${KERNEL} -ex "target remote localhost:1234"

${KERNEL}: ${OBJ} ${LINKER_LD}
	${LD} ${LDFLAGS} -T ${LINKER_LD} -o $@ ${OBJ}

build/%.o: %.c
	${CC} ${CFLAGS} $< -o $@

build/%.o: %.s
	${AS} ${NASM_FLAGS} $< -o $@

clean:
	rm -rf ${ISO}
	rm -rf ${QEMU_LOG}
	rm -rf ${KERNEL}
	rm -rf ${OBJ}