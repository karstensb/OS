SOURCES = ${wildcard boot.s kernel/*.c kernel/*.s drivers/*.c drivers/*.s cpu/*.c cpu/*.s libc/*.c libc/*.s}

__OBJ = ${SOURCES:.c=.o}
_OBJ = ${__OBJ:.s=.o}

OBJ = ${_OBJ:%=build/%}

CC = i686-elf-gcc
LD = i686-elf-ld
AS = nasm

C_FLAGS = -gdwarf-4 -masm=intel -ffreestanding -c
NASM_FLAGS = -f elf -g -O0

run: kernel.elf
	qemu-system-i386 -kernel kernel.elf

debug: kernel.elf
	qemu-system-i386 -s -S -kernel kernel.elf \
	& gdb -q -symbols=kernel.elf -ex "target remote localhost:1234" 

kernel.elf: ${OBJ}
	${LD} -o $@ ${OBJ} --script linker.ld

kernel.bin: ${OBJ}
	${LD} -o $@ ${OBJ} --script linker.ld  --oformat binary

build/%.o: %.c
	${CC} ${C_FLAGS} $< -o $@

build/%.o: %.s
	${AS} ${NASM_FLAGS} $< -o $@

clean:
	rm -rf *.bin *.o *.elf
	rm -rf ${OBJ}