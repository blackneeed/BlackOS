#pragma once

// Note: this is a really bad approach to reboot the system, when i will add acpi then this solution will be deleted.
void reboot() {
    asm volatile ("jmp 0xFFFF:0");
}