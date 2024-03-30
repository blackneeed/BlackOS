#pragma once
#include <std/stdlib.cpp>
#include <std/stdterm.cpp>
#include <std/stdcolor.cpp>
#include <std/stdstring.cpp>

extern uint8_t termColor; // ../drivers/Screen.cpp

void colorCommand(char* commandParts[], const uint32_t tokenCount) {
    if (strcmp(commandParts[1], "?")) {
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

        const uint8_t bg = getColor(colorString[0], LOOKUP_BG);
        const uint8_t fg = getColor(colorString[1], LOOKUP_FG);

        if (bg == LOOKUP_UNKNOWN || fg == LOOKUP_UNKNOWN) {
            termPrintLn("Syntax: color <color>");
            termPrintLn("Type 'color ?' for more information.");
            return;
        }

        termSetColor(bg | fg);
        termColor = bg | fg;
    }
}