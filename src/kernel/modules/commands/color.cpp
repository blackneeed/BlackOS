#pragma once
#include "../../std/stdlib.hpp"
#include "../../std/stdio.cpp"
#include "../colorLookup.cpp"
#include "../../std/stdstring.cpp"

extern uint8_t DEFAULT_COLOR; // ../drivers/Screen.cpp

void colorCommand(char* commandParts[], uint32_t tokenCount) {
    if (tokenCount < 2) {
        clearScreen();
        return;
    }

    if (strcmp(commandParts[1], "?")) {
        if (tokenCount < 3) {
            printString("Syntax: color ? <color type>\r\nColor types\r\n'fg': foreground\r\n'bg': background\r\n");
            return;
        }
        const char* colorHelp = colorHelpLookup(commandParts[2]);
        if (colorHelp == LOOKUP_UNKNOWN) {
            printString("Invalid color type!\r\n");
            return;
        }
        printString(colorHelp);
        printString("\r\n");
    } else {
        const char* color = commandParts[1];
        if (getLength(color) != 2) {
            printString("Syntax: color <color>\r\n");
            printString("Type 'color ?' for more information.\r\n");
            return;
        }

        const uint8_t bg = getColor(color[0], LOOKUP_BG);
        const uint8_t fg = getColor(color[1], LOOKUP_FG);

        if (bg == LOOKUP_UNKNOWN || fg == LOOKUP_UNKNOWN) {
            printString("Syntax: color <color>\r\n");
            printString("Type 'color ?' for more information.\r\n");
            return;
        }

        setColor(bg | fg);
        DEFAULT_COLOR = bg | fg;
    }
}