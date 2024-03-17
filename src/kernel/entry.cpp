#include "std/stdio.cpp"
#include "modules/IDT/IDT.cpp"
#include "std/stdlib.cpp"
#include "sys/config.hpp"
#include "modules/commands/commands.cpp"

uint16_t lastPrint;
#define MAX_COMMAND_LENGTH 128
char commandBuffer[MAX_COMMAND_LENGTH];
bool capsLockPressed, leftShiftPressed, rightShiftPressed = false;

void init() {
    printString("Welcome from ");
    printString(OSNAME);
    printString("!\r\n");
    lastPrint = cursorPos;
}

void loop() {
    int length = readLine("> ", commandBuffer, MAX_COMMAND_LENGTH);
    printString("\r\n");
    executeCommand(length);
}

CNAME void _start() {
    clearScreen();
    initializeIDT();
    init();
    while (true) { loop(); }
    return;
}