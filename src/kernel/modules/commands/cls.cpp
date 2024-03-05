#pragma once
#include "../Typedefs.hpp"
#include "../TextColors.hpp"
#include "../drivers/Screen.cpp"
#include "../StringUtil.cpp"
#include "../colorLookup.cpp"

extern uint8_t DEFAULT_COLOR;
void clsCommand(char* commandParts[], uint32_t tokenCount) {
    if (tokenCount < 2) {
        clearScreen();
        return;
    }
    const char* color = commandParts[1];
    if (getLength(color) < 2) {
        printString("Syntax: cls <color>\r\n");
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
    return;
}