#pragma once
#include "../../std/stdlib.cpp"
#include "../../std/stdio.cpp"

char nameBuffer[256];

void helloCommand(char* commandParts[], const uint32_t tokenCount) {
    readLine("Enter your name: ", nameBuffer, 256);
    const char* name = (const char*)nameBuffer;
    printString("Hello, ");
    printString(name);
    printLn("!");
}