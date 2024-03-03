#include "modules/drivers/Screen.cpp"
#include "modules/drivers/IDT/IDT.cpp"

uint16_t lastPrint;

void Run() { }

extern "C" void _start() {
    clearScreen();
    printString("Welcome from BlackOS!\r\n");
    printString("> ");
    lastPrint = cursorPos;
    InitializeIDT();
    while (true) { Run(); }
    return;
}