#pragma once
#include <std/stdlib.cpp>
#include <std/stdterm.cpp>

char nameBuffer[256];

void helloCommand(char* commandParts[], const uint32_t tokenCount) {
    termReadLine("Enter your name: ", nameBuffer, 256);
    const char* name = (const char*)nameBuffer;
    termPrintString("Hello, ");
    termPrintString(name);
    termPrintLn("!");
}