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

run: kernel.elf
	${QEMU} -kernel kernel.elf

debug: kernel.elf
	${QEMU} -s -S -kernel kernel.elf \
	& ${GDB} -q -symbols=kernel.elf -ex "target remote localhost:1234" 

boot: os.iso isodir
	${QEMU} -boot d -cdrom os.iso

os.iso: kernel.elf
	cp kernel.elf isodir/boot
	grub-mkrescue -o os.iso isodir

kernel.elf: ${OBJ}
	${LD} ${LDFLAGS} -o $@ ${OBJ}

build/%.o: %.c
	${CC} ${CFLAGS} $< -o $@

build/%.o: %.s
	${AS} ${NASM_FLAGS} $< -o $@

clean:
	rm -rf *.bin *.o *.elf *.iso
	rm -rf ${OBJ}