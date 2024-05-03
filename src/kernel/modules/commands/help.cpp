#pragma once
#include <std/stdterm.cpp>
#include <std/stdint.hpp>
#include <modules/commands/command.hpp>

void helpCommand(char* commandParts[], const u32 tokenCount) {
    termPrintLn("Commands:");
    termPrintLn("\t- 'version'");
    termPrintLn("\t- 'help'");
    termPrintLn("\t- 'cls'");
    termPrintLn("\t- 'color'");
    termPrintLn("\t- 'echo'");
    termPrintLn("\t- 'hello'");
}

Command getHelp() {
    Command help;
    help.name = "help";
    help.action = helpCommand;
    return help;
}