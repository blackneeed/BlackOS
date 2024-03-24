#pragma once
#include "../../std/stdio.cpp"
#include "../../std/stdlib.cpp"

void helpCommand(char* commandParts[], const uint32_t tokenCount) {
    printLn("Commands:");
    printLn("\t- 'version'");
    printLn("\t- 'help'");
    printLn("\t- 'cls'");
    printLn("\t- 'color'");
    printLn("\t- 'echo'");
    printLn("\t- 'hello'");
}