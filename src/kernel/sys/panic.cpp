#include <std/stdint.cpp>
#include <std/stdterm.cpp>
#include <std/stdcolor.cpp>
#include <sys/api/api.hpp>

void panic(const char* message) {
    color = BG_RED | FG_LIGHTBLUE;
    termClearScreen();
    u8 Y = 1;
    termSetCursorPos(posFromCoords(8 * TAB_WIDTH, Y));
    termPrintString("Kernel panic:\r\n");
    termSetCursorPos(posFromCoords(TAB_WIDTH * 8, Y + 3));
    termPrintString(message);
    _hcf();
}