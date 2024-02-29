namespace KBset1
{
    const char ScanCodeLookupTable[] =
    {
        0, 0, '1', '2',
        '3', '4', '5', '6',
        '7', '8', '9', '0',
        '-', '=', 0, 0,
        'q', 'w', 'e', 'r',
        't', 'y', 'u', 'i',
        'o', 'p', '[', ']',
        0/*Enter is handled by scancode*/, 0, 'a', 's',
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
}