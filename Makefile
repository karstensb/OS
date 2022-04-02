SOURCES = ${wildcard boot/boot.s kernel/*.c kernel/*.s drivers/*.c drivers/*.s cpu/*.c cpu/*.s libc/*.c libc/*.s}

_OBJ = ${SOURCES:.c=.o}
OBJ = ${_OBJ:.s=.o}


CC = i686-elf-gcc
LD = i686-elf-ld
AS = nasm

C_FLAGS = -gdwarf-4 -masm=intel -ffreestanding

run: kernel.elf
	qemu-system-i386 -kernel kernel.elf

debug: kernel.elf
	qemu-system-i386 -s -S -kernel kernel.elf \
	& gdb  -symbols=kernel.elf -ex "target remote localhost:1234" 

kernel.elf: ${OBJ}
	${LD} -o $@ $^ --script linker.ld

kernel.bin: ${OBJ}
	${LD} -o $@ $^ --script linker.ld  --oformat binary

%.o: %.c
	${CC} ${C_FLAGS} -c $< -o $@

%.o: %.s
	${AS} $< -f elf -g -o $@

clean:
	rm -rf *.bin *.o *.elf
	rm -rf ${OBJ}