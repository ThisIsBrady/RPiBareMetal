CPPFILES = $(wildcard *.cpp */*.cpp)
SFILES = $(wildcard boot/*.S)
CFILES = $(wildcard cpp_support/*.c)
OFILES = $(CPPFILES:.cpp=.o) $(SFILES:.S=.o) $(CFILES:.c=.o)
GCCFLAGS = -Wall -O0 -ffreestanding -nostdinc -nostdlib -nostartfiles -fno-rtti -g
CRTBEGIN_OBJ:=$(shell aarch64-none-elf-gcc $(GCCFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell aarch64-none-elf-gcc $(GCCFLAGS) -print-file-name=crtend.o)
LIBM_A:==$(shell aarch64-none-elf-gcc $(GCCFLAGS) -print-file-name=libm.a)

all: clean kernel8.img

%.o: %.c
	aarch64-none-elf-gcc -std=c99 -c $< -o $@

%.o: %.S
	aarch64-none-elf-g++ $(GCCFLAGS) -c $< -o $@

%.o: %.cpp
	aarch64-none-elf-g++ $(GCCFLAGS) -c $< -o $@

kernel8.img: $(OFILES)
	aarch64-none-elf-ld -g -T boot/link.ld $(CRTBEGIN_OBJ) $(OFILES) -o kernel8.elf --start-group $(LIBM_A) --end-group  $(CRTEND_OBJ)
	aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf */*.o *.img > /dev/null 2> /dev/null || true
