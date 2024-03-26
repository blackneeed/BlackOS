



#include "std/stdio.cpp"
#include "modules/IDT/IDT.cpp"
#include "std/stdlib.cpp"
#include "sys/config.hpp"
#include "modules/commands/commands.cpp"

uint16_t lastPrint;
#define MAX_COMMAND_LENGTH 128
char commandBuffer[MAX_COMMAND_LENGTH];

OSConfig osConfig = OSConfig {"BlackOS", 2};

void KLoop() {
    int length = readLine("> ", commandBuffer, MAX_COMMAND_LENGTH);
    executeCommand(length);
}

CNAME void KStart() {
    clearScreen();
    printString("Welcome to ");
    printString(osConfig.name);
    printLn("!");
    E9_WriteString("\r\n");
    initializeIDT();
    while (true) { KLoop(); }
    return;
}