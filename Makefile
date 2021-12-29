GCC_CONFIG := "-m32 -std=gnu17 -nostdinc -w -fno-pie -nostdlib -ffreestanding -I"$(CURDIR)"/inc/"
GPP_CONFIG := ${GCC_CONFIG}" -nostdinc++ -fno-exceptions -fno-rtti -fpermissive"

all:
	echo "git repository => https://github.com/Domaman202/DmNSOS"

compile:
	mkdir -p build
	nasm -felf32 src/kernel.asm -o ./build/kasm.o
	ld -melf_i386 -o kernel.bin -T link.ld ./build/kasm.o --oformat binary
	cat ./builded/maseBOOT.bin kernel.bin > os.bin
	dd if=/dev/zero of=disk.img bs=1024 count=1440
	dd if=os.bin of=disk.img conv=notrunc

clear:
	rm -r -d build
	rm *.bin
	rm *.img