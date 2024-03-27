#pragma once
#include "../../std/stdlib.cpp"
#include "../../modules/kb/key.hpp"
#include "../config.hpp"
#include "../../std/stdterm.cpp"

EXPORT OSConfig osConfig; // main.cpp
EXPORT bool leftShiftPressed, rightShiftPressed, capsLockPressed; // stdterm.cpp
EXPORT uint32_t keyPressCount; // stdterm.cpp

typedef struct OSInfo {
    bool specialKeysPressed[3];
    int keyPressCount;
    OSConfig config;
} OSInfo;

OSInfo fetchOSInfo() {
	OSInfo osInfo;
    osInfo.specialKeysPressed[0] = leftShiftPressed;
    osInfo.specialKeysPressed[1] = rightShiftPressed;
    osInfo.specialKeysPressed[2] = capsLockPressed;
    osInfo.keyPressCount = keyPressCount;
    osInfo.config = osConfig;
	return osInfo;
}