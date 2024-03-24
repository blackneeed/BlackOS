#pragma once

#define ENTER 0x1C
#define BACKSPACE 0x0E
#define CAPS 0x3A
#define LEFTSHIFT 0x2A
#define LEFTSHIFTRELEASE 0xAA
#define RIGHTSHIFT 0x36
#define RIGHTSHIFTRELEASE 0xB6
#define TAB 0x0F
#define ALTPRESS 0x38
#define ALTRELEASE 0xB8
#define CONTROLPRESS 0x1D
#define CONTROLRELEASE 0x9D
#define DELETEPRESS 0x53

const char KBSet1ScanCodeLookupTable[] =
{
    0, 0, '1', '2',
    '3', '4', '5', '6',
    '7', '8', '9', '0',
    '-', '=', 0, 0,
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i',
    'o', 'p', '[', ']',
    0, 0, 'a', 's',
    'd', 'f', 'g', 'h',
    'j', 'k', 'l', ';',
    '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',',
    '.', '/', 0, '*',
    0, ' ', 0, 0,  // Left Alt, Left Shift, Left Control
    0, 0, 0, 0,    // Right Alt, Right Shift, Right Control, Function keys
    0, 0, 0, 0,    // Function keys continued
    0, 0, 0        // Function keys continued
};
const char KBSet1ScanCodeLookupTableShift[] =
{
    0, 0, '!', '@',
    '#', '$', '%', '^',
    '&', '*', '(', ')',
    '_', '+', 0, 0,
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i',
    'o', 'p', '{', '}',
    0, 0, 'a', 's',
    'd', 'f', 'g', 'h',
    'j', 'k', 'l', ':',
    '"', '`', 0, '|',
    'z', 'x', 'c', 'v',
    'b', 'n', 'm', '<',
    '>', '?', 0, '*',
    0, ' ', 0, 0,  // Left Alt, Left Shift, Left Control
    0, 0, 0, 0,    // Right Alt, Right Shift, Right Control, Function keys
    0, 0, 0, 0,    // Function keys continued
    0, 0, 0        // Function keys continued
};