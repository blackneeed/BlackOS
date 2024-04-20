#pragma once
#include <std/stdint.hpp>
#include <std/stdterm.cpp>
#include <modules/commands/command.hpp>

char nameBuffer[256];

void helloCommand(char* commandParts[], const u32 tokenCount) {
    termReadLine("Enter your name: ", nameBuffer, 256);
    const char* name = (const char*)nameBuffer;
    termPrintString("Hello, ");
    termPrintString(name);
    termPrintLn("!");
}

Command getHello() {
    Command hello;
    hello.name = "hello";
    hello.action = helloCommand;
    return hello;
}