#define REVISION_NUMBER 22

#include <std/stdterm.cpp>
#include <modules/IDT/IDT.cpp>
#include <std/stdint.hpp>
#include <sys/config.hpp>
#include <modules/commands/commands.cpp>

u16 lastPrint;
#define MAX_COMMAND_LENGTH 128
char commandBuffer[MAX_COMMAND_LENGTH];

OSConfig osConfig = {"BlackOS", "base", REVISION_NUMBER};

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
