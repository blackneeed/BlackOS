#pragma once
#include <std/stdterm.cpp>
#include <std/stdlib.cpp>
#include <std/stdint.hpp>
#include <sys/config.hpp>
#include <sys/api/fetchInfo.cpp>
#include <modules/commands/command.hpp>

void versionCommand(char* commandParts[], const u32 tokenCount) {
    OSConfig config = fetchOSInfo().config;
    termPrintString(config.name);
    termPrintString(" Revision: ");
    termPrintLn(intToString(config.revision));
}

Command getVersion() {
    Command version;
    version.name = "version";
    version.action = versionCommand;
    return version;
}