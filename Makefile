C_SOURCES = ${wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c}
HEADERS = ${wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h}

OBJ = ${C_SOURCES:.c=.o}

CC = i686-elf-gcc

C_FLAGS = -g -masm=intel -ffreestanding

run: kernel.elf
	qemu-system-i386 -kernel kernel.elf

debug: kernel.elf
	qemu-system-i386 -s -S -kernel kernel.elf


kernel.elf: boot/boot.o ${OBJ}
	i686-elf-ld -o $@ $^ --script linker.ld

kernel.bin: boot/boot.o ${OBJ}
	i686-elf-ld -T linker.ld -o $@ $^  --oformat binary

%.o: %.c
	${CC} ${C_FLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

clean:
	rm -rf *.bin *.o *.elf
	rm -rf ${OBJ}
	rm -rf boot/boot.o