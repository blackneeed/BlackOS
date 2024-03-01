#include "modules/drivers/Screen.cpp"
#include "modules/drivers/IDT/IDT.cpp"
#include "modules/StringUtil.cpp"

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


void executeCommand() {
    commandBuffer[commandLength] = '\0';
    const char* command_all = (const char*)commandBuffer;
    char* command_parts[4]; // Up to 4 arguments
    splitString((char*)command_all, ' ', command_parts, 4);
    const char* command = toLower(command_parts[0]);
    if (strcmp(command, "version") == 0) {
        printString("*********************************************\r\n");
        printString("*********************************************\r\n");
        printString("****************    BlackOS    **************\r\n");
        printString("******************** 1.0.0 ******************\r\n");
        printString("*********************alpha*******************\r\n");
        printString("*********************************************");
    } else if (strcmp(command, "help") == 0) {
        printString("Commands:\r\n");
        printString("- 'version'");
    } else {
        printString("Unknown command '");
        printString(command_parts[0]); // Print the one with orginal caps
        printString("'!,\r\n");
        printString("Type 'help' for help.");
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