#pragma once
#include <std/stdint.hpp>
#include <std/stdterm.cpp>
#include <std/stdcolor.cpp>
#include <std/stdstring.cpp>
#include <modules/commands/command.hpp>

extern uint8_t termColor; // ../drivers/Screen.cpp

void clsCommand(char* commandParts[], const uint32_t tokenCount) {
    if (tokenCount < 2) {
        termClearScreen();
        return;
    }

    if (strcmp(commandParts[1], "?") == 0) {
        if (tokenCount < 3) {
            termPrintLn("Syntax: cls ? <color type>\r\nColor types\r\n'fg': foreground\r\n'bg': background");
            return;
        }
        const char* colorHelp = colorHelpLookup(commandParts[2]);
        if (colorHelp == (const char*)LOOKUP_UNKNOWN) { // Stop VSCode from yelling at me
            termPrintLn("Invalid color type!");
            return;
        }
        termPrintLn(colorHelp);
    } else {
        const char* colorString = commandParts[1];
        if (getLength(colorString) != 2) {
            termPrintString("Syntax: cls <color>\r\n");
            termPrintString("Type 'cls ?' for more information.\r\n");
            return;
        }

        const uint8_t bg = getColor(colorString[0], LOOKUP_BG);
        const uint8_t fg = getColor(colorString[1], LOOKUP_FG);

        if (bg == LOOKUP_UNKNOWN || fg == LOOKUP_UNKNOWN) {
            termPrintString("Syntax: cls <color>\r\n");
            termPrintString("Type 'cls ?' for more information.\r\n");
            return;
        }

        termColor = bg | fg;
        termClearScreen();
    }
}

Command getCls() {
    Command cls;
    cls.name = "cls";
    cls.action = clsCommand;
    return cls;
}