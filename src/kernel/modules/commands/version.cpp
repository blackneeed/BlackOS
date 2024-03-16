#pragma once
#include "../../std/stdio.cpp"
#include "../../std/stdlib.cpp"
#include "../../sys/config.hpp"

void versionCommand(char* commandParts[], const uint32_t tokenCount) {
    printString(OSNAME);
    printChar(' ');
    printString(OSVERSION);
    if (isAlphaVersion) {
        printChar(' ');
        printString("alpha");
    } else if (isBetaVersion) {
        printChar(' ');
        printString("beta");
    }
    printString("\r\n");
}