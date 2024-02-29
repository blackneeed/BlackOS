BUILD?=build
ASM?=nasm

$(PHONY): build clean

build:
	$(ASM) -f elf64 modules/drivers/IDT.asm -o $(BUILD)/IDT.o
	/usr/local/x86_64elfgcc/bin/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "entry.cpp" -o "$(BUILD)/entry.o"
	/usr/local/x86_64elfgcc/bin/x86_64-elf-ld -T"linker.ld"

clean:
	rm -rf $(BUILD)/entry.o
	rm -rf $(BUILD)/kernel.bin
	rm -rf $(BUILD)/IDT.o