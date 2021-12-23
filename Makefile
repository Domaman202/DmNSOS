GCC_CONFIG := "-m32 -w -fno-pie -nostdlib -ffreestanding"
GPP_CONFIG := ${GCC_CONFIG}" -fno-exceptions -fno-rtti -fpermissive"

build:
	make -C ./kernel build GCC_CONFIG=${GCC_CONFIG} GPP_CONFIG=${GPP_CONFIG}
	make -C ./bootloader build

	ld -m elf_i386 -o kernel.bin -T link.ld kernel_b.o --oformat binary --entry main

	dd if=./kernel.bin of=kernel_.bin conv=sync &> /dev/null && sync
	cat ./bootloader.bin ./kernel_.bin > os.bin
	dd if=os.bin of=disk.img conv=notrunc

	rm *.o
	rm *.bin

all:
	echo "git repository => https://github.com/Domaman202/DmNSOS"