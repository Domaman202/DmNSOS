C_FILES = $(wildcard *.c)
CPP_FILES = $(wildcard *.cpp)
temp = $(notdir $(C_FILES))
temp_ = $(notdir $(CPP_FILES))
O_FILES = ${temp:.c=.o}
OPP_FILES = ${temp_:.cpp=.o}

build:
	nasm -f elf32 -o kasm.o kernel.asm
	gcc ${GCC_CONFIG} -c ${C_FILES}
	g++ ${GPP_CONFIG} -c ${CPP_FILES}
	ld -m elf_i386 -relocatable -o kernel_b.o kasm.o ${O_FILES} ${OPP_FILES}
	mv kernel_b.o ..
	rm *.o