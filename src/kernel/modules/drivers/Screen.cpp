#pragma once

#include "IO.cpp"
#include "../Typedefs.hpp"
#include "../TextColors.hpp"

uint16_t cursorPos;
uint8_t DEFUALT_COLOR = BG_BLACK | FG_RED;

#define VGA_MEMORY (unsigned char*)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define CRT_CONTROLLER_PORT 0x3D4

unsigned short posFromCoords(uint8_t x, uint8_t y){
    return y * VGA_WIDTH + x;
}

void scrollScreenUp() {
    for (int y = 1; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x) {
            unsigned short srcPos = posFromCoords(x, y);
            unsigned short destPos = posFromCoords(x, y - 1);
            *(VGA_MEMORY + destPos * 2) = *(VGA_MEMORY + srcPos * 2);
            *(VGA_MEMORY + destPos * 2 + 1) = *(VGA_MEMORY + srcPos * 2 + 1);
        }
    }

    unsigned short lastRowPos = posFromCoords(0, VGA_HEIGHT - 1);
    for (int x = 0; x < VGA_WIDTH; ++x) {
        *(VGA_MEMORY + lastRowPos * 2) = ' ';
        *(VGA_MEMORY + lastRowPos * 2 + 1) = DEFUALT_COLOR;
        ++lastRowPos;
    }
}

void scrollScreenDown() {
    for (int y = VGA_HEIGHT - 2; y >= 0; --y) {
        for (int x = 0; x < VGA_WIDTH; ++x) {
            unsigned short srcPos = posFromCoords(x, y);
            unsigned short destPos = posFromCoords(x, y + 1);
            *(VGA_MEMORY + destPos * 2) = *(VGA_MEMORY + srcPos * 2);
            *(VGA_MEMORY + destPos * 2 + 1) = *(VGA_MEMORY + srcPos * 2 + 1);
        }
    }

    unsigned short firstRowPos = posFromCoords(0, 0);
    for (int x = 0; x < VGA_WIDTH; ++x) {
        *(VGA_MEMORY + firstRowPos * 2) = ' ';
        *(VGA_MEMORY + firstRowPos * 2 + 1) = DEFUALT_COLOR;
        ++firstRowPos;
    }
}

void clearScreen(uint64_t ClearColor = DEFUALT_COLOR)
{
    uint64_t value = 0;
    value += ClearColor << 8;
    value += ClearColor << 24;
    value += ClearColor << 40;
    value += ClearColor << 56;

    for (uint64_t* i = (uint64_t*)VGA_MEMORY; i < (uint64_t*)(VGA_MEMORY + 4000); i++){
        *i = value;
    }
}


void setCursorPos(uint16_t newPos){
    outb(CRT_CONTROLLER_PORT, 0x0F);
    outb(CRT_CONTROLLER_PORT + 1, (uint8_t)(newPos & 0xFF));
    outb(CRT_CONTROLLER_PORT, 0x0E);
    outb(CRT_CONTROLLER_PORT + 1, (uint8_t)((newPos >> 8) & 0xFF));

    cursorPos = newPos;
}

void printString(const char* string, uint8_t color = DEFUALT_COLOR)
{
    uint16_t index = cursorPos;
    for (size_t i = 0; string[i] != '\0'; i++) {
        switch(string[i]) {
            case '\n':
                index += VGA_WIDTH;
                if (index >= VGA_WIDTH * VGA_HEIGHT) {
                    scrollScreenUp();
                    index -= VGA_WIDTH;
                }
                break;
            case '\r':
                index -= index % VGA_WIDTH;
                break;
            default:
                if (index >= VGA_WIDTH * VGA_HEIGHT) {
                    scrollScreenUp();
                    index -= VGA_WIDTH;
                }
                *(VGA_MEMORY + index * 2) = string[i];
                *(VGA_MEMORY + index * 2 + 1) = color;
                index++;
        }
    }
    setCursorPos(index);
}

void printChar(char character, uint8_t color = DEFUALT_COLOR)
{
    *(VGA_MEMORY + cursorPos * 2) = character;
    *(VGA_MEMORY + cursorPos * 2 + 1) = color;
    setCursorPos(cursorPos + 1);
}

void deleteChar(uint8_t color = DEFUALT_COLOR) {
    if (cursorPos > 0) {
        setCursorPos(cursorPos - 1);
        printChar(' ');
        setCursorPos(cursorPos - 1);
    }
}