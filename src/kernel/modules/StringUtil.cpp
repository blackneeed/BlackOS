#pragma once
#include "Typedefs.hpp"

int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        ++str1;
        ++str2;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

void splitString(char* str, char delimiter, char** tokens, uint32_t maxTokens) {
    uint32_t tokenCount = 0;
    char* token = (char*)str;

    while (*str != '\0' && tokenCount < maxTokens) {
        if (*str == delimiter) {
            *str = '\0';
            tokens[tokenCount++] = token;
            token = str + 1;
        }
        str++;
    }

    if (tokenCount < maxTokens) {
        tokens[tokenCount++] = token;
    }

    if (tokenCount < maxTokens) {
        tokens[tokenCount] = NULL;
    }
}

char* toLower(char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = (char)(int)str[i] + 32;
    }
    return str;
}

char* toUpper(char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] <= 'z' && str[i] >= 'a')
            str[i] = (char)(int)str[i] - 32;
    }
    return str;
}

char charToLower(char chr) {
    if (chr >= 'A' && chr <= 'Z')
        chr = (char)(int)chr + 32;
    return chr;
}

char charToUpper(char chr) {
    if (chr <= 'z' && chr >= 'a')
        chr = (char)(int)chr - 32;
    return chr;
}

uint8_t getLength(const char* str) {
    uint8_t length = 0;
    while (*str != '\0') {
        length += 1;
        str++;
    }
    return length;
}