#pragma once
#include "../../std/stdlib.cpp"
#include "../../std/stdio.cpp"

char nameBuffer[256];
int nameLength;
extern char processCharacter(int scanCode);
uint16_t lastPrint_Hello = 0;
extern bool leftShiftPressed, rightShiftPressed, capsLockPressed;

void helloCommand(char* commandParts[], const uint32_t tokenCount) {
    printString("Enter your name: ");
    lastPrint_Hello = cursorPos;
    while (true) {
        Key key = getKey();
        if (key.isCharacter && key.keyCode == character && nameLength < 255) {
            char chr = processCharacter(key.scanCode);
            printChar(chr);
            nameBuffer[nameLength++] = chr;
        } else if (key.keyCode == tab) { } else if (key.keyCode == backspace && cursorPos > lastPrint_Hello) {
            deleteChar();
            nameBuffer[nameLength--] = '\0';
        } else if (key.keyCode == enter) {
            nameBuffer[nameLength++] = '\0';
            break;
        } else if (key.keyCode == lshiftpress || key.keyCode == lshiftrelease) {
            leftShiftPressed = !leftShiftPressed;
        } else if (key.keyCode == rshiftpress || key.keyCode == rshiftrelease) {
            rightShiftPressed = !rightShiftPressed;
        } else if (key.keyCode == caps) {
            capsLockPressed = !capsLockPressed;
        }
    }

    printString("\r\n");
    const char* name = (const char*)nameBuffer;
    printString("Hello, ");
    printString(name);
    printString("!\r\n");
}