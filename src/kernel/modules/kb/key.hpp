#pragma once

enum KeyCode {
    character = 0,
    tab = 1,
    backspace = 2,
    enter = 3,
    lshiftpress = 4,
    lshiftrelease = 5,
    rshiftpress = 6,
    rshiftrelease = 7,
    controlpress = 8,
    controlrelease = 9,
    altpress = 10,
    altrelease = 11,
    deletepress = 12,
    deleterelease = 13,
    caps = 14
};

typedef struct {
    bool isCharacter;
    KeyCode keyCode;
    int charScanCode;
} Key;