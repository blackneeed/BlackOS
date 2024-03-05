#pragma once

#include "IO.cpp"
#include "../Typedefs.hpp"
#include "../TextColors.hpp"

// Settings
uint16_t cursorPos;
uint8_t DEFAULT_COLOR = BG_BLACK | FG_RED;
#define VGA_MEMORY (uint8_t*)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define CRT_CONTROLLER_PORT 0x3D4

// Cursor position stuff

uint16_t posFromCoords(uint8_t x, uint8_t y) {
    return y * VGA_WIDTH + x;
}

void setCursorPos(uint16_t newPos) {
    outb(CRT_CONTROLLER_PORT, 0x0F);
    outb(CRT_CONTROLLER_PORT + 1, (uint8_t)(newPos & 0xFF));
    outb(CRT_CONTROLLER_PORT, 0x0E);
    outb(CRT_CONTROLLER_PORT + 1, (uint8_t)((newPos >> 8) & 0xFF));

    cursorPos = newPos;
}

// Screen scrolling

void scrollScreenUp() {
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            uint16_t srcPos = posFromCoords(x, y);
            uint16_t destPos = posFromCoords(x, y - 1);
            *(VGA_MEMORY + destPos * 2) = *(VGA_MEMORY + srcPos * 2);
            *(VGA_MEMORY + destPos * 2 + 1) = *(VGA_MEMORY + srcPos * 2 + 1);
        }
    }

    uint16_t lastRowPos = posFromCoords(0, VGA_HEIGHT - 1);
    for (int x = 0; x < VGA_WIDTH; x++) {
        *(VGA_MEMORY + lastRowPos * 2) = ' ';
        *(VGA_MEMORY + lastRowPos * 2 + 1) = DEFAULT_COLOR;
        ++lastRowPos;
    }
}

void scrollScreenDown() {
    for (int y = VGA_HEIGHT - 2; y >= 0; y--) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            uint16_t srcPos = posFromCoords(x, y);
            uint16_t destPos = posFromCoords(x, y + 1);
            *(VGA_MEMORY + destPos * 2) = *(VGA_MEMORY + srcPos * 2);
            *(VGA_MEMORY + destPos * 2 + 1) = *(VGA_MEMORY + srcPos * 2 + 1);
        }
    }

    uint16_t firstRowPos = posFromCoords(0, 0);
    for (int x = 0; x < VGA_WIDTH; x++) {
        *(VGA_MEMORY + firstRowPos * 2) = ' ';
        *(VGA_MEMORY + firstRowPos * 2 + 1) = DEFAULT_COLOR;
        ++firstRowPos;
    }
}

// Printing

void printChar(char character, uint8_t color = DEFAULT_COLOR)
{
    switch (character) {
        case '\n':
            cursorPos += VGA_WIDTH;
            if (cursorPos >= VGA_WIDTH * VGA_HEIGHT) {
                scrollScreenUp();
                cursorPos -= VGA_WIDTH;
            }
        case '\r':
            cursorPos -= cursorPos % VGA_WIDTH;
            break;
        default:
            if (cursorPos >= VGA_WIDTH * VGA_HEIGHT) {
                scrollScreenUp();
                cursorPos -= VGA_WIDTH;
            }
            *(VGA_MEMORY + cursorPos * 2) = character;
            *(VGA_MEMORY + cursorPos * 2 + 1) = color;
            cursorPos++;
    }
    setCursorPos(cursorPos);
}

void printString(const char* string, uint8_t color = DEFAULT_COLOR)
{
    uint16_t index = cursorPos;
    for (size_t i = 0; string[i] != '\0'; i++) {
        printChar(string[i]);
    }
}

// Screen clearing

void clearScreen(uint64_t color = DEFAULT_COLOR)
{
    uint64_t value = 0;
    value += color << 8;
    value += color << 24;
    value += color << 40;
    value += color << 56;

    for (uint64_t* i = (uint64_t*)VGA_MEMORY; i < (uint64_t*)(VGA_MEMORY + 4000); i++){
        *i = value;
    }

    setCursorPos(0);
}

void deleteChar(uint8_t color = DEFAULT_COLOR) {
    if (cursorPos > 0) {
        setCursorPos(cursorPos - 1);
        printChar(' ');
        setCursorPos(cursorPos - 1);
    }
}