#pragma once
#include "../Screen.cpp"
#include "../../Typedefs.hpp"
#include "../debug/E9.cpp"

#define MAX_COMMAND_LENGTH 128
#define TAB_WIDTH 4
uint8_t commandLength;
extern uint16_t lastPrint;
char commandBuffer[MAX_COMMAND_LENGTH];

void CLIHandleCharacter(char chr) {
    E9_WriteString("Character '");
    E9_WriteChar(chr);
    E9_WriteString("' pressed!\r\n");
    printChar(chr);
    if (commandLength < MAX_COMMAND_LENGTH - 1) {
        commandBuffer[commandLength++] = chr;
    }
}

void CLIHandleTab() {
    E9_WriteString("Tab pressed!\r\n");
    for (uint8_t i = 0; i < TAB_WIDTH; i++) {
        printChar(' ');
    }
}

void CLIHandleBackspace() {
    E9_WriteString("Backspace pressed!\r\n");
    if (cursorPos > lastPrint) {
        deleteChar();
        commandLength--;
        commandBuffer[commandLength] = '\0';
    }
}

void CLIHandleEnter() {
    E9_WriteString("Enter pressed!\r\n");
    printString("\r\n");
    executeCommand();
    commandLength = 0;
    printString("> ");
    lastPrint = cursorPos;
}