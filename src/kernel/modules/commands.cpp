#pragma once
#include "StringUtil.cpp"
#include "commands/cls.cpp"
#include "commands/help.cpp"
#include "commands/echo.cpp"
#include "commands/version.cpp"
#include "commands/color.cpp"
#include "commands/unknown.cpp"

extern char commandBuffer[];
extern uint8_t commandLength;
#define MAX_COMMAND_ARGS 12 // Not counting the name

void callCommand(char* commandParts[], uint32_t tokenCount, const char* command) {
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
    else
        unknownCommand(commandParts, tokenCount);
}

void executeCommand() {
    commandBuffer[commandLength] = '\0';
    const char* commandAll = (const char*)commandBuffer;
    char* commandParts[MAX_COMMAND_ARGS + 1] = {}; // Command arguments + 1 (leaving space for name)
    uint32_t tokenCount = splitString((char*)commandAll, ' ', commandParts, MAX_COMMAND_ARGS + 1);
    const char* command = toLower(commandParts[0]);
    if (isSpace(command)) {
        return;
    }
    callCommand(commandParts, tokenCount, command);
}