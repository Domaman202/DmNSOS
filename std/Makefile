C_FILES = $(wildcard *.c)
CPP_FILES = $(wildcard *.cpp)
temp = $(notdir $(C_FILES))
temp_ = $(notdir $(CPP_FILES))
O_FILES = ${temp:.c=.o}
OPP_FILES = ${temp_:.cpp=.o}

build:
	gcc ${GCC_CONFIG} -c ${C_FILES}
	g++ ${GPP_CONFIG} -c ${CPP_FILES}
	ld -m elf_i386 -relocatable -o std.o ${O_FILES} ${OPP_FILES}
	mv std.o ..
	rm *.o