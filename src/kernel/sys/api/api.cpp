#pragma once
#include <std/stdint.cpp>
#include <std/stdterm.cpp>
#include <std/stdcolor.cpp>

void _hcf() {
    asm("cli");
    for (;;) asm("hlt");
}

void _die(const char* message) {
    color = BG_RED | FG_LIGHTBLUE;
    termClearScreen();
    u8 Y = 1;
    termSetCursorPos(posFromCoords(8 * TAB_WIDTH, Y));
    termPrintString("Kernel panic:\r\n");
    termSetCursorPos(posFromCoords(TAB_WIDTH * 8, Y + 3));
    termPrintString(message);
    _hcf();
}

extern "C" inline void hcf() {
    _hcf();    
}

extern "C" inline void die(const char* message) {
    _die(message);
}