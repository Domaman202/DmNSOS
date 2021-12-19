build:
	make -C ./kernel build
	mv ./kernel/kernel.elf os.elf