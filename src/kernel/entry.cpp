#include "std/stdio.cpp"
#include "modules/IDT/IDT.cpp"
#include "std/stdlib.hpp"

uint16_t lastPrint;

void init() {
    printString("Welcome from BlackOS!\r\n");
    printString("> ");
    lastPrint = cursorPos;
}
void loop() { }

CNAME void _start() {
    clearScreen();
    initializeIDT();
    init();
    while (true) { loop(); }
    return;
}