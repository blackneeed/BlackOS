#include "std/stdio.cpp"
#include "modules/IDT/IDT.cpp"
#include "std/stdlib.cpp"
#include "sys/config.hpp"
#include "modules/kb/key.hpp"
#include "std/stdstring.cpp"

uint16_t lastPrint;
#define MAX_COMMAND_LENGTH 128
char commandBuffer[MAX_COMMAND_LENGTH];
uint8_t commandLength;
bool capsLockPressed, leftShiftPressed, rightShiftPressed = false;

char processCharacter(int scanCode) {
    if (leftShiftPressed | rightShiftPressed) {
        if (!capsLockPressed) {
            return charToUpper(KBSet1ScanCodeLookupTableShift[scanCode]);
        } else {
            return charToLower(KBSet1ScanCodeLookupTableShift[scanCode]);
        }
    } else if (capsLockPressed) {
        return charToUpper(KBSet1ScanCodeLookupTable[scanCode]);
    } else {
        return charToLower(KBSet1ScanCodeLookupTable[scanCode]);
    }
}

void init() {
    printString("Welcome from ");
    printString(OSNAME);
    printString("!\r\n");
    printString("> ");
    lastPrint = cursorPos;
}

void readCommand() {
    while (true) {
        Key key = getKey();
        if (key.isCharacter && key.keyCode == character && commandLength < MAX_COMMAND_LENGTH - 1) {
            char chr = processCharacter(key.scanCode);
            printChar(chr);
            commandBuffer[commandLength++] = chr;
        } else if (key.keyCode == tab) {
            printChar('\t');
        } else if (key.keyCode == backspace && cursorPos > lastPrint) {
            deleteChar();
            commandBuffer[commandLength--] = '\0';
        } else if (key.keyCode == enter) {
            return;
        } else if (key.keyCode == lshiftpress || key.keyCode == lshiftrelease) {
            leftShiftPressed = !leftShiftPressed;
        } else if (key.keyCode == rshiftpress || key.keyCode == rshiftrelease) {
            rightShiftPressed = !rightShiftPressed;
        } else if (key.keyCode == caps) {
            capsLockPressed = !capsLockPressed;
        }
    }
}

void loop() {
    readCommand();
    printString("\r\n");
    executeCommand();
    commandLength = 0;
    printString("> ");
    lastPrint = cursorPos;
}

CNAME void _start() {
    clearScreen();
    initializeIDT();
    init();
    while (true) { loop(); }
    return;
}