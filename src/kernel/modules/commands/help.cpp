#pragma once
#include "../drivers/Screen.cpp"
#include "../Typedefs.hpp"

void helpCommand(char* commandParts[], uint32_t tokenCount) {
    printString("Commands:\r\n");
    printString("- 'version'\r\n");
    printString("- 'help'\r\n");
    printString("- 'cls'\r\n");
    printString("- 'echo'\r\n");
}