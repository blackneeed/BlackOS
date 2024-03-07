#include "modules/drivers/Screen.cpp"
#include "modules/drivers/IDT/IDT.cpp"
#include "modules/Typedefs.hpp"

uint16_t lastPrint;

void init() {
    printString("Welcome from BlackOS!\r\n");
    printString("> ");
    lastPrint = cursorPos;
}
void loop() { }

extern "C" void _start() {
    clearScreen();
    initializeIDT();
    init();
    while (true) { loop(); }
    return;
}