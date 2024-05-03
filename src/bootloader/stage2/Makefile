BUILD?=build
ASM?=nasm
FORMAT?=elf64

$(PHONY): build clean

build:
	$(ASM) -f $(FORMAT) entry.asm -o $(BUILD)/stage2.o

clean:
	rm -rf $(BUILD)/stage2.o