#pragma once
#include "../Screen.cpp"
#include "../debug/E9.cpp"
#include "Keymap.cpp"
#include "Keys.hpp"
#include "../../Typedefs.hpp"
#include "../IO.cpp"

void handleEnter();
void handleBackspace();
void handleTab();
void handleCharacter(char chr);

class KeyboardDriver {
public:
    KeyboardDriver() {}

    void main() {
        uint8_t scanCode = inb(0x60);
        switch (scanCode) {
            case ENTER:
                handleEnter();
                break;

            case BACKSPACE:
                handleBackspace();
                break;

            case TAB:
                handleTab();
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
    }
    bool capsLockPressed = false;
    bool leftShiftPressed = false;
    bool rightShiftPressed = false;
};