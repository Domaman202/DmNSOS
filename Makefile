build:
	make -C ./kernel build
	make -C ./bootloader build

	ld -m elf_i386 -o kernel.bin -T link.ld ./kernel/kernel.a --oformat binary --entry main

	dd if=./kernel.bin of=kernel_.bin conv=sync &> /dev/null && sync
	cat ./bootloader.bin ./kernel_.bin > os.bin
	dd if=os.bin of=disk.img conv=notrunc

	rm ./kernel/kernel.a
	rm *.bin