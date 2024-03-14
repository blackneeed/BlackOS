#pragma once

#include "stdlib.hpp"
#include "stdport.cpp"
#include "stdcolor.cpp"

// Debugging

void E9_WriteChar(uint8_t character) {
    outb(0xE9, character);
}

void E9_WriteString(const char* string) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        E9_WriteChar(string[i]);
    }
}

// Settings

uint16_t cursorPos;
uint8_t color = BG_BLACK | FG_WHITE;
#define VGA_ADDRESS (uint8_t*)0xb8000
#define VGA_COLS 80
#define VGA_ROWS 25
#define CRT_CONTROLLER_PORT 0x3D4

// Cursor position stuff

uint16_t posFromCoords(uint8_t x, uint8_t y) {
    return y * VGA_COLS + x;
}

void setCursorPos(uint16_t newPos = cursorPos) { // Defaults to cursor pos becuase it is often used to refresh the cursor
    outb(CRT_CONTROLLER_PORT, 0x0F);
    outb(CRT_CONTROLLER_PORT + 1, (uint8_t)(newPos & 0xFF));
    outb(CRT_CONTROLLER_PORT, 0x0E);
    outb(CRT_CONTROLLER_PORT + 1, (uint8_t)((newPos >> 8) & 0xFF));

    cursorPos = newPos;
}

// Screen scrolling

void scrollScreenUp() {
    for (int y = 1; y < VGA_ROWS; y++) {
        for (int x = 0; x < VGA_COLS; x++) {
            uint16_t srcPos = posFromCoords(x, y);
            uint16_t destPos = posFromCoords(x, y - 1);
            *(VGA_ADDRESS + destPos * 2) = *(VGA_ADDRESS + srcPos * 2);
            *(VGA_ADDRESS + destPos * 2 + 1) = *(VGA_ADDRESS + srcPos * 2 + 1);
        }
    }

    uint16_t lastRowPos = posFromCoords(0, VGA_ROWS - 1);
    for (int x = 0; x < VGA_COLS; x++) {
        *(VGA_ADDRESS + lastRowPos * 2) = ' ';
        *(VGA_ADDRESS + lastRowPos * 2 + 1) = color;
        ++lastRowPos;
    }
}

void scrollScreenDown() {
    for (int y = VGA_ROWS - 2; y >= 0; y--) {
        for (int x = 0; x < VGA_COLS; x++) {
            uint16_t srcPos = posFromCoords(x, y);
            uint16_t destPos = posFromCoords(x, y + 1);
            *(VGA_ADDRESS + destPos * 2) = *(VGA_ADDRESS + srcPos * 2);
            *(VGA_ADDRESS + destPos * 2 + 1) = *(VGA_ADDRESS + srcPos * 2 + 1);
        }
    }

    uint16_t firstRowPos = posFromCoords(0, 0);
    for (int x = 0; x < VGA_COLS; x++) {
        *(VGA_ADDRESS + firstRowPos * 2) = ' ';
        *(VGA_ADDRESS + firstRowPos * 2 + 1) = color;
        ++firstRowPos;
    }
}

// Printing

void printChar(char character, uint8_t color = color)
{
    switch (character) {
        case '\n':
            cursorPos += VGA_COLS;
            if (cursorPos >= VGA_COLS * VGA_ROWS) {
                scrollScreenUp();
                cursorPos -= VGA_COLS;
            }
        case '\r':
            cursorPos -= cursorPos % VGA_COLS;
            break;
        case '\t':
            for (int i = 0; i < TAB_WIDTH; i++) {
                if (cursorPos >= VGA_COLS * VGA_ROWS) {
                    scrollScreenUp();
                    cursorPos -= VGA_COLS;
                }
                *(VGA_ADDRESS + cursorPos * 2) = ' ';
                *(VGA_ADDRESS + cursorPos * 2 + 1) = color;
                cursorPos++;
            }
            break;
        default:
            if (cursorPos >= VGA_COLS * VGA_ROWS) {
                scrollScreenUp();
                cursorPos -= VGA_COLS;
            }
            *(VGA_ADDRESS + cursorPos * 2) = character;
            *(VGA_ADDRESS + cursorPos * 2 + 1) = color;
            cursorPos++;
            break;
    }
    setCursorPos();
}

void printString(const char* string, uint8_t color = color)
{
    uint16_t index = cursorPos;
    for (size_t i = 0; string[i] != '\0'; i++) {
        printChar(string[i]);
    }
}

// Screen clearing

void clearScreen(uint64_t color = color)
{
    uint64_t value = 0;
    value += color << 8;
    value += color << 24;
    value += color << 40;
    value += color << 56;

    for (uint64_t* i = (uint64_t*)VGA_ADDRESS; i < (uint64_t*)(VGA_ADDRESS + 4000); i++){
        *i = value;
    }

    setCursorPos(0);
}

void setColor(uint64_t color = color) {
    for (uint16_t pos = 0; pos < VGA_COLS * VGA_ROWS; pos++) {
        *(VGA_ADDRESS + pos * 2 + 1) = color;
    }
}

void deleteChar(uint8_t color = color) {
    if (cursorPos > 0) {
        cursorPos--;
        printChar(' ');
        cursorPos--;
        setCursorPos();
    }
}