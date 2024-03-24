#pragma once
#include "../../std/stdio.cpp"
#include "../../std/stdlib.cpp"
#include "../../sys/config.hpp"
#include "../../sys/api/fetchInfo.cpp"

void versionCommand(char* commandParts[], const uint32_t tokenCount) {
    OSConfig config = fetchOSInfo().config;
    printString(config.name);
    printChar(' ');
    printLn(intToString(config.revision));
}