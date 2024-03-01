#include "StringUtil.cpp"
#include "drivers/Screen.cpp"

void versionCommand(char* command_parts[]) {
    printString("*********************************************\r\n");
    printString("*********************************************\r\n");
    printString("****************    BlackOS    **************\r\n");
    printString("******************** 1.0.0 ******************\r\n");
    printString("*********************alpha*******************\r\n");
    printString("*********************************************");
}

void helpCommand(char* command_parts[]) {
    printString("Commands:\r\n");
    printString("- 'version'");
}

void clearScreenCommand(char* command_parts[]) {
    clearScreen();
}

void unknownCommand(char* command_parts[]) {
    printString("Unknown command '");
    printString(command_parts[0]); // Print the one with orginal caps
    printString("'!,\r\n");
    printString("Type 'help' for help.");
}

void executeCommand() {
    commandBuffer[commandLength] = '\0';
    const char* command_all = (const char*)commandBuffer;
    char* command_parts[4]; // Up to 4 arguments
    splitString((char*)command_all, ' ', command_parts, 4);
    const char* command = toLower(command_parts[0]);
    if (strcmp(command, "version") == 0) {
        versionCommand(command_parts);
    } else if (strcmp(command, "help") == 0) {
        helpCommand(command_parts);
    } else if (strcmp(command, "cls") == 0) {
        clearScreenCommand(command_parts);
    } else {
        unknownCommand(command_parts);
    }
}