#pragma once
#include "../../std/stdstring.cpp"
#include "cls.cpp"
#include "help.cpp"
#include "echo.cpp"
#include "version.cpp"
#include "color.cpp"
#include "hello.cpp"
#include "unknown.cpp"

extern char commandBuffer[];
#define MAX_COMMAND_ARGS 12 // Not counting the name

void callCommand(char* commandParts[], const uint32_t tokenCount, const char* command) {
    if (strcmp("cls", command))
        clsCommand(commandParts, tokenCount);
    else if (strcmp("help", command))
        helpCommand(commandParts, tokenCount);
    else if (strcmp("echo", command))
        echoCommand(commandParts, tokenCount);
    else if (strcmp("version", command))
        versionCommand(commandParts, tokenCount);
    else if (strcmp("color", command))
        colorCommand(commandParts, tokenCount);
    else if (strcmp("hello", command))
        helloCommand(commandParts, tokenCount);
    else
        unknownCommand(commandParts, tokenCount);
}

void executeCommand(int length) {
    commandBuffer[length] = '\0';
    const char* commandAll = (const char*)commandBuffer;
    char* commandParts[MAX_COMMAND_ARGS + 1] = {}; // Command arguments + 1 (leaving space for name)
    const uint32_t tokenCount = splitString((char*)commandAll, ' ', commandParts, MAX_COMMAND_ARGS + 1);
    const char* command = toLower(commandParts[0]);
    if (isSpace(command)) {
        return;
    }
    callCommand(commandParts, tokenCount, command);
}