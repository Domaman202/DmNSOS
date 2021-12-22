build_mls:
	gcc ${GCC_CONFIG} -c mls.c -o mls_c.o
	ld -m elf_i386 -relocatable mls_c.o -o mls.o
	mv mls.o ..
	rm *.o

build:
	gcc ${GCC_CONFIG} -c no_mls.c -o mls_c.o
	mv mls_c.o ../mls.o