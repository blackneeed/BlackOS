#pragma once
#include "../../std/stdio.cpp"
#include "../../std/stdlib.cpp"
#include "../../sys/config.hpp"

extern OSConfig osConfig; // main.cpp

void versionCommand(char* commandParts[], const uint32_t tokenCount) {
    printString(osConfig.name);
    printChar(' ');
    printString(osConfig.version);
    if (osConfig.isAlpha) {
        printLn(" alpha");
    } else if (osConfig.isBeta) {
        printLn(" beta");
    } else {
        printLn();
    }
}