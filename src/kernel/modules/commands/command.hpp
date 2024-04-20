#pragma once
#include <std/stdint.hpp>

typedef struct Command {
    const char* name;
    void (*action)(char* commandParts[], const u32 tokenCount);
} Command;