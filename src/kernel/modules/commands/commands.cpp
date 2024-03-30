#pragma once
#include <std/stdstring.cpp>
#include <modules/commands/command.hpp>
#include <modules/commands/cls.cpp>
#include <modules/commands/help.cpp>
#include <modules/commands/echo.cpp>
#include <modules/commands/version.cpp>
#include <modules/commands/color.cpp>
#include <modules/commands/hello.cpp>

extern char commandBuffer[];
#define MAX_COMMAND_ARGS 12 // Not counting the name
const int commandCount = 6;
Command commands[commandCount];

void unknownCommand(const char* command) {
    termPrintString("Unknown command '");
    termPrintString(command);
    termPrintString("'");
    termPrintLn(".");
    termPrintLn("Type 'help' for help.");
}

void initCommands() {
    commands[0] = getCls();
    commands[1] = getColor();
    commands[2] = getVersion();
    commands[3] = getEcho();
    commands[4] = getHelp();
    commands[5] = getHello();
}

void callCommand(char* commandParts[], const uint32_t tokenCount, const char* command) {
    bool foundCommand = false;
    int commandIndex = 0;
    for (int i = 0; i < commandCount && !foundCommand; i++) {
        if (strcmp(commands[i].name, command) == 0) {
            commandIndex = i;
            foundCommand = true;
        }
    }
    if (foundCommand) {
        commands[commandIndex].action(commandParts, tokenCount);
        return;
    } else {
        unknownCommand(command);
    }
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