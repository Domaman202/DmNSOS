C_FILES = $(wildcard *.c)
CPP_FILES = $(wildcard *.cpp)
temp = $(notdir $(C_FILES))
temp_ = $(notdir $(CPP_FILES))
O_FILES = ${temp:.c=.o}
OPP_FILES = ${temp_:.cpp=.o}

build:
	nasm -f elf32 -o kasm.o kernel.asm
	gcc -w -m32 -fno-pie -nostdlib -ffreestanding -c ${C_FILES}
	g++ -fno-exceptions -fno-rtti -fpermissive -w -m32 -fno-pie -nostdlib -ffreestanding -c ${CPP_FILES}
	gcc-ar cr kernel.a kasm.o ${O_FILES} ${OPP_FILES}
	rm *.o