#include "std/stdio.cpp"
#include "modules/IDT/IDT.cpp"
#include "std/stdlib.cpp"
#include "sys/config.hpp"
uint16_t lastPrint;

void init() {
    printString("Welcome from ");
    printString(OSNAME);
    printString("!\r\n");
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