#include "modules/drivers/Screen.cpp"
#include "modules/drivers/IDT/IDT.cpp"
#include "modules/StringUtil.cpp"
#include "modules/commands.cpp"

#define MAX_COMMAND_LENGTH 128
char commandBuffer[MAX_COMMAND_LENGTH];
uint16_t lastPrint;
uint8_t commandLength;
bool capsLockPressed = false;
bool leftShiftPressed = false;
bool rightShiftPressed = false;

void Run() {
    
}

extern "C" void _start() {
    clearScreen();
    setCursorPos(0);
    printString("Welcome from BlackOS!\r\n");
    printString("> ");
    lastPrint = cursorPos;
    InitializeIDT();
    while (true) { Run(); }
    return;
}

void handleEnter() {
    printString("\r\n");
    executeCommand();
    printString("\r\n");
    commandLength = 0;
    printString("> ");
    lastPrint = cursorPos;
}

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