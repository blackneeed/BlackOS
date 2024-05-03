#pragma once
#include <std/stdint.hpp>
#include <std/stddebug.cpp>
#include <std/stdport.cpp>
#include <modules/kb/keyboard.cpp>

struct IDT64
{
    u16 offset_low;
    u16 selector;
    u8 ist;
    u8 types_attr;
    u16 offset_mid;
    u32 offset_high;
    u32 zero = 0;
};

void handleSyscall() {
    u64 rax, rdi, rsi, rdx, r9, r8;
    asm volatile("movq %%rax, %0" : "=r" (rax));
    asm volatile("movq %%rdi, %0" : "=r" (rdi));
    asm volatile("movq %%rsi, %0" : "=r" (rsi));
    asm volatile("movq %%rdx, %0" : "=r" (rdx));
    asm volatile("movq %%r9, %0" : "=r" (r9));
    asm volatile("movq %%r8, %0" : "=r" (r8));
    E9_WriteString("Value of rax: ");
    E9_WriteString(intToString(rax));
    E9_WriteString("\r\n");
    E9_WriteString("Value of rdi: ");
    E9_WriteString(intToString(rdi));
    E9_WriteString("\r\n");
    E9_WriteString("Value of rsi: ");
    E9_WriteString(intToString(rsi));
    E9_WriteString("\r\n");
    E9_WriteString("Value of rdx: ");
    E9_WriteString(intToString(rdx));
    E9_WriteString("\r\n");
    E9_WriteString("Value of r9: ");
    E9_WriteString(intToString(r9));
    E9_WriteString("\r\n");
    E9_WriteString("Value of r8: ");
    E9_WriteString(intToString(r8));
    E9_WriteString("\r\n");
}

CNAME void isr128_handler() {
    E9_WriteString("Interrupt 0x80 (syscall) called!\r\n");
    handleSyscall();
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}

EXPORT IDT64 _idt[256];
EXPORT u64 isr1;
EXPORT u64 isr128;
CNAME void LoadIDT();

void remapPic() {
    u8 a1, a2;
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

void initializeIDT()
{

    _idt[0x01].zero = 0;
    _idt[0x01].offset_low = (u16)(((u64)&isr1 & 0x000000000000ffff));
    _idt[0x01].offset_mid = (u16)(((u64)&isr1 & 0x00000000ffff0000) >> 16);
    _idt[0x01].offset_high = (u32)(((u64)&isr1 & 0xffffffff00000000) >> 32);
    _idt[0x01].ist = 0;
    _idt[0x01].selector = 0x08;
    _idt[0x01].types_attr = 0x8e;

    _idt[128].zero = 0;
    _idt[128].offset_low = (u16)(((u64)&isr128 & 0x000000000000ffff));
    _idt[128].offset_mid = (u16)(((u64)&isr128 & 0x00000000ffff0000) >> 16);
    _idt[128].offset_high = (u32)(((u64)&isr128 & 0xffffffff00000000) >> 32);
    _idt[128].ist = 0;
    _idt[128].selector = 0x08;
    _idt[128].types_attr = 0x8e;

    remapPic();

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    LoadIDT();
}
