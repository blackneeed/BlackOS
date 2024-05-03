#pragma once
#include <std/stdint.hpp>
#include <std/stdterm.cpp>
#include <std/stdcolor.cpp>
#include <sys/config.hpp>
#include <modules/kb/key.hpp>

EXPORT OSConfig osConfig; // main.cpp
EXPORT bool leftShiftPressed, rightShiftPressed, capsLockPressed; // stdterm.cpp
EXPORT u32 keyPressCount; // stdterm.cpp
EXPORT u8 termColor;

typedef struct OSInfo {
    bool specialKeysPressed[3];
    int keyPressCount;
    OSConfig config;
} OSInfo;

void _hcf() {
    asm("cli");
    for (;;) asm("hlt");
}

void _die(const char* message) {
    termColor = BG_RED | FG_LIGHTBLUE;
    termClearScreen();
    u8 Y = 1;
    termSetCursorPos(posFromCoords(8 * TAB_WIDTH, Y));
    termPrintString("Kernel panic:\r\n");
    termSetCursorPos(posFromCoords(TAB_WIDTH * 8, Y + 3));
    termPrintString(message);
    _hcf();
}

extern "C" inline void hcf() {
    _hcf();    
}

extern "C" inline void die(const char* message) {
    _die(message);
}

OSInfo _fetchOSInfo() {
	OSInfo osInfo;
    osInfo.specialKeysPressed[0] = leftShiftPressed;
    osInfo.specialKeysPressed[1] = rightShiftPressed;
    osInfo.specialKeysPressed[2] = capsLockPressed;
    osInfo.keyPressCount = keyPressCount;
    osInfo.config = osConfig;
	return osInfo;
}

extern "C" inline OSInfo fetchOSInfo() {
    return _fetchOSInfo();
}