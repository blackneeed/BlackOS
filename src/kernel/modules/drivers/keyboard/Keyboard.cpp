#pragma once
#include "../../commands.cpp"
#include "../Screen.cpp"
#include "../../Typedefs.hpp"
#include "../debug/E9.cpp"
#include "Keymap.cpp"
#include "Keys.hpp"
#include "CLIKeyboard.cpp"
#include "GUIKeyboard.cpp"

extern uint8_t MODE;
bool capsLockPressed = false;
bool leftShiftPressed = false;
bool rightShiftPressed = false;

void handleCharacter(char chr) {
    if (MODE == CLI) CLIHandleCharacter(chr);
    else if (MODE == GUI) GUIHandleCharacter(chr);
    else {}
}

extern "C" void isr1_handler()
{
    uint8_t scanCode = inb(0x60);
    switch (scanCode) {
        case ENTER:
            if (MODE == CLI) CLIHandleEnter();
            else if (MODE == GUI) GUIHandleEnter();
            else {}
            break;

        case BACKSPACE:
            if (MODE == CLI) CLIHandleBackspace();
            else if (MODE == GUI) GUIHandleBackspace();
            else {}
            break;

        case TAB:
            if (MODE == CLI) CLIHandleTab();
            else if (MODE == GUI) GUIHandleTab();
            else {}
            break;

        case CAPS:
            E9_WriteString("Caps lock pressed\r\n");
            capsLockPressed = !capsLockPressed;
            break;

        case LEFTSHIFT:
            E9_WriteString("LSHIFT pressed\r\n");
			leftShiftPressed = true;
			break;

		case LEFTSHIFTRELEASE:
			E9_WriteString("LSHIFT released\r\n");
            leftShiftPressed = false;
            break;
        
		case RIGHTSHIFT:
			E9_WriteString("RSHIFT pressed\r\n");
			rightShiftPressed = true;
			break;
		case RIGHTSHIFTRELEASE:
			E9_WriteString("RSHIFT released\r\n");
			rightShiftPressed = false;
			break;


        default:
            if (scanCode < 0x3A)
            {
                if (leftShiftPressed | rightShiftPressed) {
                    if (!capsLockPressed) {
                        handleCharacter(charToUpper(KBset1::ScanCodeLookupTableShift[scanCode]));
                    } else {
                        handleCharacter(charToLower(KBset1::ScanCodeLookupTableShift[scanCode]));
                    }
                } else if (capsLockPressed) {
                    handleCharacter(charToUpper(KBset1::ScanCodeLookupTable[scanCode]));
                } else {
                    handleCharacter(charToLower(KBset1::ScanCodeLookupTable[scanCode]));
                }
            }
            break;
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}