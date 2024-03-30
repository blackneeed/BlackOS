#pragma once
#include <std/stdlib.cpp>

int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        ++str1;
        ++str2;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2 == 0;
}

uint32_t splitString(char* str, char delimiter, char** tokens, uint32_t maxTokens) {
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

    return tokenCount;
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

bool isCharSpace(char chr) {
    return (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\r' || chr == '\v' || chr == '\f' || chr == '\0');
}

bool isSpace(const char* str) {
    if (str == nullptr)
        return true;

    while (*str != '\0') {
        if (!isCharSpace(*str))
            return false;
        str++;
    }
    return true;
} 

bool startsWith(const char* str, const char* prefix) {
    if (str == nullptr || prefix == nullptr)
        return false;

    while (*prefix != '\0') {
        if (*str != *prefix)
            return false;
        str++;
        prefix++;
    }

    return true;
}

bool endsWith(const char* str, const char* suffix) {
    if (str == nullptr || suffix == nullptr)
        return false;

    size_t str_len = getLength(str);
    size_t suffix_len = getLength(suffix);

    if (suffix_len > str_len)
        return false;

    str -= suffix_len;

    while (*suffix != '\0') {
        if (*str != *suffix)
            return false;
        str++;
        suffix++;
    }

    return true;
} 

bool isCharAlpha(char chr) {
    return chr >= 'A' && chr <= 'Z' || chr <= 'z' && chr >= 'a';
}

bool isAlpha(const char* str) { 
    while (*str != '\0') {
        if (!isCharAlpha(*str)) {
            return false;
        }
        str++;
    }
    return true;
}