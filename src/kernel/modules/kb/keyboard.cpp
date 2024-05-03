#pragma once
#include <std/stdlib.cpp>
#include <std/stdint.hpp>
#include <std/stddebug.cpp>
#include <modules/kb/key.hpp>

Key lastKeyInfo;
u32 keyPressCount;

void handleCharacter(int scanCode) {
    if (!processCharacter(scanCode).isEmpty) {
        E9_WriteString("Character '");
        E9_WriteChar(processCharacter(scanCode).chr);
        E9_WriteString("' pressed!\r\n");
    }
    Key info;
    info.isCharacter = true;
    info.keyCode = character;
    info.charScanCode = scanCode;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleTab() {
    E9_WriteString("Tab pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = tab;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleBackspace() {
    E9_WriteString("Backspace pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = backspace;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleEnter() {
    E9_WriteString("Enter pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = enter;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleLShiftPress() {
    E9_WriteString("LShift pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = lshiftpress;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleLShiftRelease() {
    E9_WriteString("LShift released!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = lshiftrelease;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleRShiftPress() {
    E9_WriteString("RShift pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = rshiftpress;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleRShiftRelease() {
    E9_WriteString("RShift released!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = rshiftrelease;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleControlPress() {
    E9_WriteString("Control pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = controlpress;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleControlRelease() {
    E9_WriteString("Control released!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = controlrelease;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleAltPress() {
    E9_WriteString("Alt pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = altpress;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleAltRelease() {
    E9_WriteString("Alt released!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = altrelease;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleDeletePress() {
    E9_WriteString("Delete pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = deletepress;
    lastKeyInfo = info;
    keyPressCount++;
}

void handleCaps() {
    E9_WriteString("Caps lock pressed!\r\n");
    Key info;
    info.isCharacter = false;
    info.keyCode = caps;
    lastKeyInfo = info;
    keyPressCount++;
}

CNAME void isr1_handler()
{
    u8 scanCode = inb(0x60);

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

        case ALTPRESS:
            handleAltPress();
            break;
        
        case ALTRELEASE:
            handleAltRelease();
            break;

        case CONTROLPRESS:
            handleControlPress();
            break;
        
        case CONTROLRELEASE:
            handleControlRelease();
            break;

        case DELETEPRESS:
            handleDeletePress();
            break;

        default:
            if (scanCode < 0x3A)
                handleCharacter(scanCode);
            break;
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}
