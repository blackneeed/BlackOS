#pragma once
#include "../../std/stdio.cpp"
#include "../../std/stdlib.cpp"
#include "../../sys/config.hpp"
#include "../../sys/fetchInfo.cpp"

void versionCommand(char* commandParts[], const uint32_t tokenCount) {
    OSConfig config = fetchOSInfo().config;
    printString(config.name);
    printChar(' ');
    printString(config.version);
    if (config.isAlpha) {
        printLn(" alpha");
    } else if (config.isBeta) {
        printLn(" beta");
    } else {
        printLn();
    }
}