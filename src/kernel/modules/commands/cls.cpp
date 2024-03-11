#pragma once
#include "../Typedefs.hpp"
#include "../drivers/Screen.cpp"
#include "../colorLookup.cpp"
#include "../StringUtil.cpp"

extern uint8_t DEFAULT_COLOR; // ../drivers/Screen.cpp

const char* colorHelpLookup(char* colorMode) {
    if (strcmp(colorMode, "fg")) {
        return "0: Black\r\n1: Blue\r\n2: Green\r\n3: Cyan\r\n4: Red\r\n5: Magenta\r\n6: Brown\r\n7: Light Gray\r\n8: Dark Gray\r\n9: Light Blue\r\nA: Light Green\r\nB: Light Cyan\r\nC: Light Red\r\nD: Light Magenta\r\nE: Yellow\r\nF: White";
    } else if (strcmp(colorMode, "bg")) {
        return "0: Black\r\n1: Blue\r\n2: Green\r\n3: Cyan\r\n4: Red\r\n5: Magenta\r\n6: Brown\r\n7: Light Gray\r\n8: Blinking Black\r\n9: Blinking Blue\r\nA: Blinking Green\r\nB: Blinking Cyan\r\nC: Blinking Red\r\nD: Blinking Magenta\r\nE: Blinking Yellow\r\nF: Blinking White";
    } else {
        return LOOKUP_UNKNOWN;
    }
}

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
            printString("Invalid color string!\r\n");
            return;
        }

        DEFAULT_COLOR = bg | fg;
        clearScreen();
    }
}