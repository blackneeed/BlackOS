#pragma once
#include <std/stdint.hpp>
#include <std/stdterm.cpp>
#include <std/stdcolor.cpp>
#include <std/stdstring.cpp>
#include <modules/commands/command.hpp>

extern u8 termColor; // ../drivers/Screen.cpp

void colorCommand(char* commandParts[], const u32 tokenCount) {
    if (strcmp(commandParts[1], "?") == 0) {
        if (tokenCount < 3) {
            termPrintLn("Syntax: color ? <color type>\r\nColor types\r\n'fg': foreground\r\n'bg': background");
            return;
        }
        const char* colorHelp = colorHelpLookup(commandParts[2]);
        if (colorHelp == (const char*)LOOKUP_UNKNOWN) { // Stop VSCode from yelling at me
            termPrintLn("Invalid color type!");
            return;
        }
        termPrintString(colorHelp);
        termPrintString("\r\n");
    } else {
        const char* colorString = commandParts[1];
        if (getLength(colorString) != 2) {
            termPrintLn("Syntax: color <color>");
            termPrintLn("Type 'color ?' for more information.");
            return;
        }

        const u8 bg = getColor(colorString[0], LOOKUP_BG);
        const u8 fg = getColor(colorString[1], LOOKUP_FG);

        if (bg == LOOKUP_UNKNOWN || fg == LOOKUP_UNKNOWN) {
            termPrintLn("Syntax: color <color>");
            termPrintLn("Type 'color ?' for more information.");
            return;
        }

        termSetColor(bg | fg);
        termColor = bg | fg;
    }
}

Command getColor() {
    Command color;
    color.name = "color";
    color.action = colorCommand;
    return color;
}