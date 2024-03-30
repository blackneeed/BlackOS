#pragma once
#include <std/stdterm.cpp>
#include <std/stdlib.cpp>

void helpCommand(char* commandParts[], const uint32_t tokenCount) {
    termPrintLn("Commands:");
    termPrintLn("\t- 'version'");
    termPrintLn("\t- 'help'");
    termPrintLn("\t- 'cls'");
    termPrintLn("\t- 'color'");
    termPrintLn("\t- 'echo'");
    termPrintLn("\t- 'hello'");
}