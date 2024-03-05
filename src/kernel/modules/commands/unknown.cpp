#pragma once
#include "../Typedefs.hpp"
#include "../drivers/Screen.cpp"

void unknownCommand(char* commandParts[], uint32_t tokenCount) {
    printString("Unknown command '");
    printString(commandParts[0]);
    printString("'!,\r\n");
    printString("Type 'help' for help.\r\n");
}