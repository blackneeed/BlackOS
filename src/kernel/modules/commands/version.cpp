#pragma once
#include "../../std/stdterm.cpp"
#include "../../std/stdlib.cpp"
#include "../../sys/config.hpp"
#include "../../sys/api/fetchInfo.cpp"

void versionCommand(char* commandParts[], const uint32_t tokenCount) {
    OSConfig config = fetchOSInfo().config;
    termPrintString(config.name);
    termPrintChar(' ');
    termPrintLn(intToString(config.revision));
}