#pragma once
#include <std/stdint.hpp>
#include <std/stdterm.cpp>

void unknownCommand(char* commandParts[], const uint32_t tokenCount) {
    termPrintString("Unknown command '");
    termPrintString(commandParts[0]);
    termPrintLn("'!");
    termPrintLn("Type 'help' for help.");
}