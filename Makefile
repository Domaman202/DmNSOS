build:
	make -C ./kernel build
	make -C ./bootloader build
	dd if=./iso/kernel.bin of=kernel.bin conv=sync &> /dev/null && sync
	cat ./iso/bootloader.bin ./kernel.bin > os.bin
	dd if=os.bin of=disk.img conv=notrunc

clean:
	make -C ./kernel clean
	make -C ./bootloader clean
	rm -d -r ./iso
	rm *.bin
	rm disk.img

cbuild:
	make clean
	make build