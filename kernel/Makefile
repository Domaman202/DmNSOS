C_FILES = $(shell find *.c)
temp = $(notdir $(C_FILES))
O_FILES = ${temp:.c=.o}

build:
	nasm -f elf32 -o kasm.o kernel.asm
	gcc -m32 -fno-pie -nostdlib -ffreestanding -c ${C_FILES}
	ld -m elf_i386 -o kernel.bin -Ttext 0x8000 ./kasm.o ${O_FILES} --oformat binary --entry main
	mkdir ../iso
	mv kernel.bin ../iso

clean:
	rm *.o