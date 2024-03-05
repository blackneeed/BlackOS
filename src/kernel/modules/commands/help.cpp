#pragma once
#include "../drivers/Screen.cpp"

void helpCommand(char* commandParts[], uint32_t tokenCount) {
    printString("Commands:\r\n");
    printString("- 'version'\r\n");
    printString("- 'help'\r\n");
    printString("- 'cls'\r\n");
    printString("- 'echo'\r\n");
}