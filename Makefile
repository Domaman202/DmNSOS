GCC_CONFIG := "-m32 -std=gnu17 -nostdinc -w -fno-pie -nostdlib -ffreestanding -I"$(CURDIR)"/inc/"
GPP_CONFIG := ${GCC_CONFIG}" -nostdinc++ -fno-exceptions -fno-rtti -fpermissive"

all:
	echo "git repository => https://github.com/Domaman202/DmNSOS"

compile:
	