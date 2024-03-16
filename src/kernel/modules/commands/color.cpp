#pragma once
#include "../../std/stdlib.cpp"
#include "../../std/stdio.cpp"
#include "../../std/stdcolor.cpp"
#include "../../std/stdstring.cpp"

extern uint8_t color; // ../drivers/Screen.cpp

void colorCommand(char* commandParts[], const uint32_t tokenCount) {
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
        if (colorHelp == (const char*)LOOKUP_UNKNOWN) { // Stop VSCode from yelling at me
            printString("Invalid color type!\r\n");
            return;
        }
        printString(colorHelp);
        printString("\r\n");
    } else {
        const char* colorString = commandParts[1];
        if (getLength(colorString) != 2) {
            printString("Syntax: color <color>\r\n");
            printString("Type 'color ?' for more information.\r\n");
            return;
        }

        const uint8_t bg = getColor(colorString[0], LOOKUP_BG);
        const uint8_t fg = getColor(colorString[1], LOOKUP_FG);

        if (bg == LOOKUP_UNKNOWN || fg == LOOKUP_UNKNOWN) {
            printString("Syntax: color <color>\r\n");
            printString("Type 'color ?' for more information.\r\n");
            return;
        }

        setColor(bg | fg);
        color = bg | fg;
    }
}