build:
	nasm -f bin bootloader0.asm
	nasm -f bin bootloader1.asm
	cat bootloader0 bootloader1 > bootloader.bin
	mv bootloader.bin ../iso
	rm bootloader0
	rm bootloader1