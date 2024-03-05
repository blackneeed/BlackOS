#pragma once
#include "../../Typedefs.hpp"
#include "../../StringUtil.cpp"
#include "../IO.cpp"
#include "../Screen.cpp"
#include "../debug/E9.cpp"
#include "../keyboard/Keyboard.cpp"

struct IDT64
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t types_attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;
};

extern IDT64 _idt[256];
extern uint64_t isr1;
extern "C" void LoadIDT();

void InitializeIDT()
{

    _idt[1].zero = 0;
    _idt[1].offset_low = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
    _idt[1].offset_mid = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
    _idt[1].offset_high = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
    _idt[1].ist = 0;
    _idt[1].selector = 0x08;
    _idt[1].types_attr = 0x8e;

    remapPic();

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    LoadIDT();
}