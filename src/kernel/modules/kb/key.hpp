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
    caps = 8
};

typedef struct {
    bool isCharacter;
    KeyCode keyCode;
    char character;
    int scanCode;
} Key;