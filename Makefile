DIR_BOOT = ./bootloader
DIR_BOOTSTAGE1 = $(DIR_BOOT)/stage1
DIR_BOOTSTAGE2 = $(DIR_BOOT)/stage2

FLAGS_C = -m32 -w

compile: bootloader_compile kernel_compile
	cat ./build/bootloader.bin ./build/kernel.bin ./fs/fs > os.bin

kernel_compile:
	nasm -felf -o ./build/kasm.o ./src/kernel.asm
	i686-elf-gcc $(FLAGS_C) -c ./src/kernel.c -o ./build/kc.o
	i686-elf-ld -T ./src/link.ld -e entry --oformat binary -o ./build/kernel.bin ./build/kasm.o ./build/kc.o
	rm ./build/*.o

bootloader_compile: bootloader_stage1 bootloader_stage2
	rm ./build/*.o
	cat ./build/stage1.bin ./build/stage2.bin > ./build/bootloader.bin
	rm ./build/stage1.bin ./build/stage2.bin

bootloader_stage1:
	mkdir -p ./build
	nasm -fbin -o ./build/stage1.bin $(DIR_BOOTSTAGE1)/bootloader.asm -I $(DIR_BOOTSTAGE1)

bootloader_stage2:
	i686-elf-gcc $(FLAGS_C) -c $(DIR_BOOTSTAGE2)/main.c -I $(DIR_BOOTSTAGE2) -o ./build/stage2c0.o
	i686-elf-gcc $(FLAGS_C) -c $(DIR_BOOTSTAGE2)/io.c -I $(DIR_BOOTSTAGE2) -o ./build/stage2c1.o
	nasm -felf -i $(DIR_BOOTSTAGE2) $(DIR_BOOTSTAGE2)/sections.asm -o ./build/stage2a0.o
	nasm -felf -i $(DIR_BOOTSTAGE2) $(DIR_BOOTSTAGE2)/ports.asm -o ./build/stage2a1.o
	i686-elf-ld -T $(DIR_BOOTSTAGE2)/link.ld -e main --oformat binary -o ./build/stage2.bin ./build/stage2a0.o ./build/stage2a1.o ./build/stage2c0.o ./build/stage2c1.o

# --- Fs --- #
build_fs:
	@echo "--- Creating an empty file system named 'OS2020FS' (64 MiB) ---"
	mkdir -p ./fs
	dd if=/dev/zero of=./fs/fs bs=512 count=128K
	mkfs.fat -F 32 -s 1 -n OS2020FS ./fs/fs