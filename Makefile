SOURCES = ${wildcard boot.s kernel/*.c kernel/*.s drivers/*.c drivers/*.s cpu/*.c cpu/*.s libc/*.c libc/*.s}

__OBJ = ${SOURCES:.c=.o}
_OBJ = ${__OBJ:.s=.o}
OBJ = ${_OBJ:%=build/%}

CC = i686-elf-gcc
AS = nasm
LD = i686-elf-gcc
QEMU = qemu-system-i386
GDB = gdb

CFLAGS = -g -masm=intel -ffreestanding -c
NASM_FLAGS = -f elf -g -O0
LDFLAGS = -T linker.ld -nostdlib -lgcc

KERNEL = isodir/boot/kernel.elf

run: ${KERNEL}
	${QEMU} -kernel ${KERNEL}

debug: ${KERNEL}
	${QEMU} -s -S -kernel ${KERNEL} \
	& ${GDB} -q -symbols=${KERNEL} -ex "target remote localhost:1234" 

boot: build/os.iso
	${QEMU} -boot d -cdrom build/os.iso

boot-debug: build/os.iso
	${QEMU} -s -S -boot d -cdrom build/os.iso \
	& ${GDB} -q -symbols=${KERNEL} -ex "target remote localhost:1234"

build/os.iso: isodir ${KERNEL}
	grub-mkrescue -o $@ isodir

isodir/boot/kernel.elf: ${OBJ}
	${LD} ${LDFLAGS} -o $@ ${OBJ}

build/%.o: %.c
	${CC} ${CFLAGS} $< -o $@

build/%.o: %.s
	${AS} ${NASM_FLAGS} $< -o $@

clean:
	rm -rf build/os.iso
	rm -rf ${KERNEL}
	rm -rf ${OBJ}