#include <std/stdlib.cpp>
#include <std/stdterm.cpp>
#include <std/stdcolor.cpp>

extern uint8_t color; 

void panic(const char* message) {
    color = BG_RED | FG_LIGHTBLUE;
    termClearScreen();
    uint8_t Y = 1;
    termSetCursorPos(posFromCoords(8 * TAB_WIDTH, Y));
    termPrintString("Kernel panic:\r\n");
    termSetCursorPos(posFromCoords(TAB_WIDTH * 8, Y + 3));
    termPrintString(message);
    for (;;) {
        asm("hlt");
    }
}