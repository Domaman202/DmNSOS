build:
	mkdir -p ./dist
	make -C ./kernel build
	make -C ./bootloader build
	cat ./iso/bootloader.bin ./iso/kernel.bin > os.bin
	dd if=os.bin of=disk.img conv=notrunc

	mv disk.img ./dist/disk.img
	mv os.bin ./dist/os.bin

	rm -d -r ./iso
	rm -rf *.bin

run:
	make -C . build
	qemu-system-i386 ./dist/disk.img