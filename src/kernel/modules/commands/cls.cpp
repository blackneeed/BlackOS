#pragma once
#include "../Typedefs.hpp"
#include "../drivers/Screen.cpp"
#include "../colorLookup.cpp"
#include "../StringUtil.cpp"

extern uint8_t DEFAULT_COLOR; // ../drivers/Screen.cpp

void clsCommand(char* commandParts[], uint32_t tokenCount) {
    if (tokenCount < 2) {
        clearScreen();
        return;
    }

    if (strcmp(commandParts[1], "?")) {
        if (tokenCount < 3) {
            printString("Syntax: cls ? <color type>\r\nColor types\r\n'fg': foreground\r\n'bg': background\r\n");
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
            printString("Syntax: cls <color>\r\n");
            printString("Type 'cls ?' for more information.\r\n");
            return;
        }

        const uint8_t bg = getColor(color[0], LOOKUP_BG);
        const uint8_t fg = getColor(color[1], LOOKUP_FG);

        if (bg == LOOKUP_UNKNOWN || fg == LOOKUP_UNKNOWN) {
            printString("Syntax: cls <color>\r\n");
            printString("Type 'cls ?' for more information.\r\n");
            return;
        }

        DEFAULT_COLOR = bg | fg;
        clearScreen();
    }
}