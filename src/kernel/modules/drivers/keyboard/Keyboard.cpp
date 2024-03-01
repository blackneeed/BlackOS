#pragma once
#include "../Screen.cpp"
#include "../../Typedefs.hpp"
#include "../../commands.cpp"

#define MAX_COMMAND_LENGTH 128
extern uint16_t lastPrint;
uint8_t commandLength;
char commandBuffer[MAX_COMMAND_LENGTH];
bool capsLockPressed = false;
bool leftShiftPressed = false;
bool rightShiftPressed = false;

void handleCharacter(char chr) {
    printChar(chr);
    if (commandLength < MAX_COMMAND_LENGTH - 1) {
        commandBuffer[commandLength++] = chr;
    }
}

void handleBackspace() {
    if (cursorPos > lastPrint) {
        deleteChar();
        commandLength--;
        commandBuffer[commandLength] = '\0';
    }
}

void handleEnter() {
    printString("\r\n");
    executeCommand();
    printString("\r\n");
    commandLength = 0;
    printString("> ");
    lastPrint = cursorPos;
}