SRC=src
BUILD=build

$(PHONY): all

all: always bootloader makeimg run clean
build_all: always bootloader makeimg clean

always:
	mkdir -p $(BUILD)

bootloader: stage1 stage2

stage1:
	$(MAKE) -C $(SRC)/bootloader/stage1 build BUILD=$(abspath $(BUILD))

stage2:
	$(MAKE) -C $(SRC)/bootloader/stage2 build BUILD=$(abspath $(BUILD))

kernel:
	$(MAKE) -C $(SRC)/kernel build BUILD=$(abspath $(BUILD))

makeimg: bootloader kernel
	cat $(BUILD)/krnlload.bin $(BUILD)/kernel.bin > $(BUILD)/BlackOSBuild.bin
	truncate -s 1200k $(BUILD)/BlackOSBuild.bin
	genisoimage -b $(BUILD)/BlackOSBuild.bin -o $(BUILD)/BlackOS.iso -input-charset utf-8 ./

run:
	qemu-system-x86_64 -cdrom $(BUILD)/BlackOS.iso -boot d -monitor stdio -d guest_errors,cpu_reset -debugcon file:/dev/stdout 

clean:
	$(MAKE) -C $(SRC)/bootloader/stage1 clean BUILD=$(abspath $(BUILD))
	$(MAKE) -C $(SRC)/bootloader/stage2 clean BUILD=$(abspath $(BUILD))
	$(MAKE) -C $(SRC)/kernel clean BUILD=$(abspath $(BUILD))
	rm -rf $(BUILD)/BlackOSBuild.bin