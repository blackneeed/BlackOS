#pragma once
#include "../IO.cpp"
#include "../../Typedefs.hpp"

void E9_WriteChar(uint8_t character) {
    outb(0xE9, character);
}

void E9_WriteString(const char* string) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        E9_WriteChar(string[i]);
    }
}