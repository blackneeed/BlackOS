#pragma once
#include <std/stdlib.cpp>
#include <std/stdterm.cpp>

void unknownCommand(char* commandParts[], const uint32_t tokenCount) {
    termPrintString("Unknown command '");
    termPrintString(commandParts[0]);
    termPrintLn("'!");
    termPrintLn("Type 'help' for help.");
}