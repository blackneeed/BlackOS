#pragma once
#include "../commands.cpp"
#include "../../std/stdlib.cpp"
#include "kbset1.hpp"
#include "key.hpp"
#include "../../std/stdio.cpp"

Key lastKeyInfo;
uint32_t keyPressCount;

void handleCharacter(char chr, int scanCode) {
    E9_WriteString("Character '");
    E9_WriteChar(chr);
    E9_WriteString("' pressed!\r\n");
    Key info;
    info.isCharacter = true;
    info.character = chr;
    info.keyCode = character;
    info.scanCode = scanCode;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleTab() {
    E9_WriteString("Tab pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.character = '\0';
    info.keyCode = tab;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleBackspace() {
    E9_WriteString("Backspace pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.character = '\0';
    info.keyCode = backspace;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleEnter() {
    E9_WriteString("Enter pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.character = '\0';
    info.keyCode = enter;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleLShiftPress() {
    E9_WriteString("LShift pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.character = '\0';
    info.keyCode = lshiftpress;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleLShiftRelease() {
    E9_WriteString("LShift released!\r\n");
    Key info;
    info.isCharacter = false;
    info.character = '\0';
    info.keyCode = lshiftrelease;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleRShiftPress() {
    E9_WriteString("RShift pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.character = '\0';
    info.keyCode = rshiftpress;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleRShiftRelease() {
    E9_WriteString("RShift released!\r\n");
    Key info;
    info.isCharacter = false;
    info.character = '\0';
    info.keyCode = rshiftrelease;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleCaps() {
    E9_WriteString("Caps lock pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.character = '\0';
    info.keyCode = caps;
    lastKeyInfo = info;
    keyPressCount++;
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
            handleCaps();
            break;

        case LEFTSHIFT:
            handleLShiftPress();
            break;

		case LEFTSHIFTRELEASE:
            handleLShiftRelease();
            break;
        
		case RIGHTSHIFT:
            handleRShiftPress();
			break;

		case RIGHTSHIFTRELEASE:
			handleLShiftPress();
			break;


        default:
            if (scanCode < 0x3A)
            {
                handleCharacter(KBSet1ScanCodeLookupTable[scanCode], scanCode);
            }
            break;
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}