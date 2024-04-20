#include <std/stdterm.cpp>
#include <modules/IDT/IDT.cpp>
#include <std/stdlib.cpp>
#include <sys/config.hpp>
#include <modules/commands/commands.cpp>

uint16_t lastPrint;
#define MAX_COMMAND_LENGTH 128
char commandBuffer[MAX_COMMAND_LENGTH];

OSConfig osConfig = {"BlackOS", "base", 11};

CNAME void KLoop() {
    int length = termReadLine("> ", commandBuffer, MAX_COMMAND_LENGTH);
    executeCommand(length);
}

CNAME void KStart() {
    termClearScreen();
    termPrintString("Welcome to ");
    termPrintString(osConfig.name);
    termPrintString(" (");
    termPrintString(osConfig.distro);
    termPrintLn(")!");
    E9_WriteString("\r\n");
    initializeIDT();
    initCommands();
}
