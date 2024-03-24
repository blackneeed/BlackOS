#pragma once
#include "../../std/stdlib.cpp"
#include "../../std/stdio.cpp"

void unknownCommand(char* commandParts[], const uint32_t tokenCount) {
    printString("Unknown command '");
    printString(commandParts[0]);
    printLn("'!");
    printLn("Type 'help' for help.");
}