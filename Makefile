PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
GCC_CONFIG := "-m32 -std=gnu17 -w -fno-pie -nostdlib -ffreestanding -I"$(CURDIR)"/std/"
GPP_CONFIG := ${GCC_CONFIG}" -fno-exceptions -fno-rtti -fpermissive"

OBJS = test.o

all:
	echo "git repository => https://github.com/Domaman202/DmNSOS"

build:
	make -C ./std build GCC_CONFIG=${GCC_CONFIG} GPP_CONFIG=${GPP_CONFIG}
	make -C ./kernel build GCC_CONFIG=${GCC_CONFIG} GPP_CONFIG=${GPP_CONFIG}
	make -C ./bootloader build

	ld -m elf_i386 -o kernel.bin -T link.ld kernel_b.o std.o --oformat binary --entry main

	dd if=./kernel.bin of=kernel_.bin conv=sync &> /dev/null && sync
	cat ./bootloader.bin ./kernel_.bin > os.bin
	dd if=os.bin of=disk.img conv=notrunc

	rm *.o
	rm *.bin