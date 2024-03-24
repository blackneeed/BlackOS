#pragma once
#include "../std/stdlib.cpp"
#include "../modules/kb/key.hpp"
#include "config.hpp"
#include "../std/stdio.cpp"

EXPORT OSConfig osConfig; // main.cpp
EXPORT bool leftShiftPressed, rightShiftPressed, capsLockPressed; // stdio.cpp
EXPORT int keyPressCount; // stdio.cpp

typedef struct OSInfo {
    bool specialKeysPressed[3];
    int keyPressCount;
    OSConfig config;
} OSInfo;

OSInfo fetchOSInfo() {
	bool specialKeys[3] = {leftShiftPressed, rightShiftPressed, capsLockPressed};
	OSInfo osInfo {specialKeys, keyPressCount, osConfig};
	return osInfo;
}