#pragma once
#include "../commands.cpp"
#include "../../std/stdlib.hpp"
#include "kbset1.hpp"
#include "../../std/stdio.cpp"

#define MAX_COMMAND_LENGTH 128
char commandBuffer[MAX_COMMAND_LENGTH];
uint8_t commandLength;
EXPORT uint16_t lastPrint;
bool capsLockPressed, leftShiftPressed, rightShiftPressed = false;

void handleCharacter(char chr) {
    E9_WriteString("Character '");
    E9_WriteChar(chr);
    E9_WriteString("' pressed!\r\n");
    printChar(chr);
    if (commandLength < MAX_COMMAND_LENGTH - 1) {
        commandBuffer[commandLength++] = chr;
    }
}

void handleTab() {
    E9_WriteString("Tab pressed!\r\n");
    printChar('\t');
}

void handleBackspace() {
    E9_WriteString("Backspace pressed!\r\n");
    if (cursorPos > lastPrint) {
        deleteChar();
        commandLength--;
        commandBuffer[commandLength] = '\0';
    }
}

void handleEnter() {
    E9_WriteString("Enter pressed!\r\n");
    printString("\r\n");
    executeCommand();
    commandLength = 0;
    printString("> ");
    lastPrint = cursorPos;
}

extern "C" void isr1_handler()
{
    uint8_t scanCode = inb(0x60);
    switch (scanCode) {
        case ENTER:
            handleEnter();
            break;

        case BACKSPACE:
            handleBackspace();
            break;

        case TAB:
            handleTab();
            break;

        case CAPS:
            E9_WriteString("Caps lock pressed\r\n");
            capsLockPressed = !capsLockPressed;
            break;

        case LEFTSHIFT:
            E9_WriteString("LSHIFT pressed\r\n");
			leftShiftPressed = true;
			break;

		case LEFTSHIFTRELEASE:
			E9_WriteString("LSHIFT released\r\n");
            leftShiftPressed = false;
            break;
        
		case RIGHTSHIFT:
			E9_WriteString("RSHIFT pressed\r\n");
			rightShiftPressed = true;
			break;

		case RIGHTSHIFTRELEASE:
			E9_WriteString("RSHIFT released\r\n");
			rightShiftPressed = false;
			break;


        default:
            if (scanCode < 0x3A)
            {
                if (leftShiftPressed | rightShiftPressed) {
                    if (!capsLockPressed) {
                        handleCharacter(charToUpper(KBSet1ScanCodeLookupTableShift[scanCode]));
                    } else {
                        handleCharacter(charToLower(KBSet1ScanCodeLookupTableShift[scanCode]));
                    }
                } else if (capsLockPressed) {
                    handleCharacter(charToUpper(KBSet1ScanCodeLookupTable[scanCode]));
                } else {
                    handleCharacter(charToLower(KBSet1ScanCodeLookupTable[scanCode]));
                }
            }
            break;
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}