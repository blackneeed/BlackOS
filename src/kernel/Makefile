BUILD?=build
ASM?=nasm

$(PHONY): build clean

build:
	$(ASM) -f elf64 modules/IDT/IDT.asm -o $(BUILD)/IDT.o
	$(ASM) -f elf64 sys/api/api.asm -o $(BUILD)/API.o
	/usr/local/x86_64elfgcc/bin/x86_64-elf-g++ -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -fpermissive -I . -c "main.cpp" -o "$(BUILD)/main.o"
	/usr/local/x86_64elfgcc/bin/x86_64-elf-ld -T"linker.ld"

clean:
	rm -rf $(BUILD)/entry.o
	rm -rf $(BUILD)/kernel.bin
	rm -rf $(BUILD)/IDT.o