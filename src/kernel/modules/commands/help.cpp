#pragma once
#include "../../std/stdio.cpp"
#include "../../std/stdlib.cpp"

void helpCommand(char* commandParts[], const uint32_t tokenCount) {
    printString("Commands:\r\n");
    printString("- 'version'\r\n");
    printString("- 'help'\r\n");
    printString("- 'cls'\r\n");
    printString("- 'color'\r\n");
    printString("- 'echo'\r\n");
}