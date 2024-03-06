#include "modules/drivers/Screen.cpp"
#include "modules/drivers/IDT/IDT.cpp"
#include "modules/Typedefs.hpp"

uint8_t MODE = CLI;

uint16_t lastPrint;

void CLIInit() {
    printString("Welcome from BlackOS!\r\n");
    printString("> ");
    lastPrint = cursorPos;
}
void CLILoop() { }

void GUIInit() { }
void GUILoop() { }

extern "C" void _start() {
    clearScreen();
    if (MODE == CLI) CLIInit();
    else if (MODE == GUI) GUIInit();
    else {}
    InitializeIDT();
    while (true) {
        if (MODE == CLI) CLILoop();
        else if (MODE == GUI) GUILoop();
        else {}
    }
    return;
}