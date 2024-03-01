#pragma once
#include "../../Typedefs.hpp"
#include "../../StringUtil.cpp"
#include "../IO.cpp"
#include "../Screen.cpp"
#include "Keymap.cpp" // KB sets
#include "Keys.hpp" // All constants for scancodes

struct IDT64
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t types_attr;
    uint16_t offset_mid;
    uint32_t offset_hight;
    uint32_t zero;
};

extern IDT64 _idt[256];
extern uint64_t isr1;
extern "C" void LoadIDT();
void handleCharacter(char chr);
void handleEnter();
void handleBackspace();
extern bool capsLockPressed;

void InitializeIDT()
{

    _idt[1].zero = 0;
    _idt[1].offset_low = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
    _idt[1].offset_mid = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
    _idt[1].offset_hight = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
    _idt[1].ist = 0;
    _idt[1].selector = 0x08;
    _idt[1].types_attr = 0x8e;

    remapPic();

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    LoadIDT();
}

extern "C" void isr1_handler()
{
    uint8_t scanCode = inb(0x60);
    switch (scanCode) {
        case ENTER:
            handleEnter();
            break;

        case BACKSPACE:
            handleBackspace();
            break;

        case CAPS:
            capsLockPressed = !capsLockPressed;
            break;

        default:
            if (scanCode < 0x3A)
            {
                if (capsLockPressed) {
                    handleCharacter(charToUpper(KBset1::ScanCodeLookupTable[scanCode]));
                } else {
                    handleCharacter(charToLower(KBset1::ScanCodeLookupTable[scanCode]));
                }
            }
            break;
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}