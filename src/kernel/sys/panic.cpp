#include "../std/stdlib.cpp"
#include "../std/stdio.cpp"
#include "../std/stdcolor.cpp"

extern uint8_t color; 

void panic(const char* message) {
    color = BG_RED | FG_LIGHTBLUE;
    clearScreen();
    uint8_t Y = 1;
    setCursorPos(posFromCoords(8 * TAB_WIDTH, Y));
    printString("Kernel panic:\r\n");
    setCursorPos(posFromCoords(TAB_WIDTH * 8, Y + 3));
    printString(message);
    for (;;) {
        asm("hlt");
    }
}