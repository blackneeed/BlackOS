#pragma once
#include <std/stdlib.cpp>
#include <std/stdport.cpp>
#include <std/stdcolor.cpp>
#include <std/stdcharInfo.hpp>
#include <modules/kb/key.hpp>

#define VGA_ADDRESS (uint8_t*)0xb8000
#define VGA_COLS 80
#define VGA_ROWS 25
#define CRT_CONTROLLER_PORT 0x3D4
uint16_t cursorPos;
uint8_t termColor = BG_BLACK | FG_WHITE;
extern uint32_t keyPressCount;
extern Key lastKeyInfo;
extern uint16_t lastPrint;
bool capsLockPressed = false, leftShiftPressed = false, rightShiftPressed = false, altPressed = false, controlPressed = false;

// Cursor position stuff

uint16_t posFromCoords(uint8_t x, uint8_t y) {
    return y * VGA_COLS + x;
}

void termSetCursorPos(uint16_t newPos = cursorPos) { // Defaults to cursor pos becuase it is often used to refresh the cursor
    outb(CRT_CONTROLLER_PORT, 0x0F);
    outb(CRT_CONTROLLER_PORT + 1, (uint8_t)(newPos & 0xFF));
    outb(CRT_CONTROLLER_PORT, 0x0E);
    outb(CRT_CONTROLLER_PORT + 1, (uint8_t)((newPos >> 8) & 0xFF));

    cursorPos = newPos;
}

// Screen scrolling

void termScrollScreenUp(uint8_t color = termColor) {
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

void termScrollScreenDown(uint8_t color = termColor) {
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

void termPrintChar(char character, uint8_t color = termColor)
{
    switch (character) {
        case '\n':
            cursorPos += VGA_COLS;
            if (cursorPos >= VGA_COLS * VGA_ROWS) {
                termScrollScreenUp();
                cursorPos -= VGA_COLS;
            }
        case '\r':
            cursorPos -= cursorPos % VGA_COLS;
            break;
        case '\t':
            for (int i = 0; i < TAB_WIDTH; i++) {
                if (cursorPos >= VGA_COLS * VGA_ROWS) {
                    termScrollScreenUp(color);
                    cursorPos -= VGA_COLS;
                }
                *(VGA_ADDRESS + cursorPos * 2) = ' ';
                *(VGA_ADDRESS + cursorPos * 2 + 1) = color;
                cursorPos++;
            }
            break;
        default:
            if (cursorPos >= VGA_COLS * VGA_ROWS) {
                termScrollScreenUp();
                cursorPos -= VGA_COLS;
            }
            *(VGA_ADDRESS + cursorPos * 2) = character;
            *(VGA_ADDRESS + cursorPos * 2 + 1) = color;
            cursorPos++;
            break;
    }
    termSetCursorPos();
}

void termPrintString(const char* string, uint8_t color = termColor)
{
    for (size_t i = 0; string[i] != '\0'; i++) {
        termPrintChar(string[i], color);
    }
}

void termPrintLn(const char* string, uint8_t color = termColor) {
    termPrintString(string, color);
    termPrintString("\r\n", color);
}

void termPrintLn(uint8_t color = termColor) {
    termPrintString("\r\n", color);
}

Key termGetKey() {
    int lastKeyPressCount = keyPressCount;
    while (keyPressCount == lastKeyPressCount) {
        // Hang
    }
    // Now a key has been pressed
    return lastKeyInfo;
}

void termDeleteChar(uint8_t color = termColor) {
    if (cursorPos > 0) {
        cursorPos--;
        termPrintChar(' ', color);
        cursorPos--;
        termSetCursorPos();
    }
}

int termReadLine(const char* message, char buffer[], size_t bufferSize, uint8_t color = termColor, bool replaceInput = false, char replaceInputWith = ' ') {
    termPrintString(message, color);
    lastPrint = cursorPos;
    int length = 0;
    while (true) {
        Key key = termGetKey();
        if (key.isCharacter && key.keyCode == character && length < bufferSize - 1) {
            CharInfo chrInfo = processCharacter(key.charScanCode);
            if (chrInfo.isEmpty) {
                continue;
            }
            if (!replaceInput) termPrintChar(chrInfo.chr, color);
            if (replaceInput) termPrintChar(replaceInputWith, color);
            buffer[length++] = chrInfo.chr;
        } else if (key.keyCode == tab) {
            if (!replaceInput) termPrintChar('\t', color);
            if (replaceInput) {
                for (int i = 0; i < TAB_WIDTH; i++) {
                    termPrintChar(replaceInputWith, color);
                }
            }
        } else if (key.keyCode == backspace && cursorPos > lastPrint) {
            termDeleteChar(color);
            buffer[length--] = '\0';
        } else if (key.keyCode == enter) {
            termPrintLn();
            break;
        } else if (key.keyCode == lshiftpress || key.keyCode == lshiftrelease) {
            leftShiftPressed = !leftShiftPressed;
        } else if (key.keyCode == rshiftpress || key.keyCode == rshiftrelease) {
            rightShiftPressed = !rightShiftPressed;
        } else if (key.keyCode == caps) {
            capsLockPressed = !capsLockPressed;
        } else if (key.keyCode == controlpress || key.keyCode == controlrelease) {
            controlPressed = !controlPressed;
        } else if (key.keyCode == altpress || key.keyCode == altrelease) {
            altPressed = !altPressed;
        }
    }
    lastPrint = cursorPos;
    return length;
}

int termReadMultiLine(const char* message, char buffer[], size_t bufferSize, const char* lineWrapSymbol = "~ ", uint8_t lineWrapSymbolColor = termColor & 0b11110000 | FG_BLUE, uint8_t color = termColor, bool replaceInput = false, char replaceInputWith = ' ') {
    termPrintString(message, color);
    lastPrint = cursorPos;
    int length = 0;
    while (true) {
        Key key = termGetKey();
        if (key.isCharacter && key.keyCode == character && length < bufferSize - 1) {
            CharInfo chrInfo = processCharacter(key.charScanCode);
            if (chrInfo.isEmpty) {
                continue;
            }
            if (!replaceInput) termPrintChar(chrInfo.chr, color);
            if (replaceInput) termPrintChar(replaceInputWith, color);
            buffer[length++] = chrInfo.chr;
        } else if (key.keyCode == tab) {
            if (!replaceInput) termPrintChar('\t', color);
            if (replaceInput) {
                for (int i = 0; i < TAB_WIDTH; i++) {
                    termPrintChar(replaceInputWith, color);
                }
            }
        } else if (key.keyCode == backspace && cursorPos > lastPrint) {
            termDeleteChar(color);
            buffer[length--] = '\0';
        } else if (key.keyCode == enter) {
            if (leftShiftPressed || rightShiftPressed) {
                buffer[length++] = '\r';
                buffer[length++] = '\n';
                termPrintLn();
                termPrintString(lineWrapSymbol, lineWrapSymbolColor);
            } else {
                termPrintLn();
                break;
            }
        } else if (key.keyCode == lshiftpress || key.keyCode == lshiftrelease) {
            leftShiftPressed = !leftShiftPressed;
        } else if (key.keyCode == rshiftpress || key.keyCode == rshiftrelease) {
            rightShiftPressed = !rightShiftPressed;
        } else if (key.keyCode == caps) {
            capsLockPressed = !capsLockPressed;
        } else if (key.keyCode == controlpress || key.keyCode == controlrelease) {
            controlPressed = !controlPressed;
        } else if (key.keyCode == altpress || key.keyCode == altrelease) {
            altPressed = !altPressed;
        }
    }
    lastPrint = cursorPos;
    return length;
}

// Screen clearing

void termClearScreen(uint64_t color = termColor)
{
    for (uint16_t pos = VGA_COLS * VGA_ROWS; pos > 0; pos--) {
        termSetCursorPos(pos);
        termDeleteChar(color);
    }

    termSetCursorPos(0);
}

void termSetColor(uint64_t color = termColor) {
    for (uint16_t pos = 0; pos < VGA_COLS * VGA_ROWS; pos++) {
        *(VGA_ADDRESS + pos * 2 + 1) = color;
    }
}