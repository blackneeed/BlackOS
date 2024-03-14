#pragma once
#include "../../std/stdio.cpp"
#include "../../std/stdlib.hpp"
#include "../../sys/config.hpp"

void versionCommand(char* commandParts[], uint32_t tokenCount) {
    printString(OSNAME);
    printChar(' ');
    printString(OSVERSION);
    if (isAlpha) {
        printChar(' ');
        printString("alpha");
    } else if (isBeta) {
        printChar(' ');
        printString("beta");
    }
    printString("\r\n");
}