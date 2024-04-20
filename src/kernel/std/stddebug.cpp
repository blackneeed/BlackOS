#pragma once
#include <std/stdint.hpp>
#include <std/stdport.cpp>
#include <std/stdcolor.cpp>

void E9_WriteChar(u8 character, const char* fg = ANSI_WHITE_FG, const char* bg = ANSI_BLACK_BG) {
    for (int i = 0; fg[i] != '\0'; i++) {
        outb(0xE9, fg[i]);
    }
    for (int i = 0; bg[i] != '\0'; i++) {
        outb(0xE9, bg[i]);
    }
    outb(0xE9, character);
    for (int i = 0; ANSI_RESET[i] != '\0'; i++) {
        outb(0xE9, ANSI_RESET[i]);
    }
}

void E9_WriteString(const char* string, const char* fg = ANSI_WHITE_FG, const char* bg = ANSI_BLACK_BG) {
    for (usize i = 0; string[i] != '\0'; i++) {
        E9_WriteChar(string[i], fg, bg);
    }
}