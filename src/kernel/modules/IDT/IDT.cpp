#pragma once
#include "../../std/stdlib.hpp"
#include "../../std/stdport.cpp"
#include "../kb/keyboard.cpp"

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

EXPORT IDT64 _idt[256];
EXPORT uint64_t isr1;
CNAME void LoadIDT();

void remapPic();

void initializeIDT()
{

    _idt[0x01].zero = 0;
    _idt[0x01].offset_low = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
    _idt[0x01].offset_mid = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
    _idt[0x01].offset_high = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
    _idt[0x01].ist = 0;
    _idt[0x01].selector = 0x08;
    _idt[0x01].types_attr = 0x8e;

    remapPic();

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    LoadIDT();
}

void remapPic()
{
    uint8_t a1, a2;
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DATA, 0);
    outb(PIC2_DATA, 8);
    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}