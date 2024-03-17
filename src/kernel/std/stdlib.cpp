#pragma once
#include "../modules/kb/kbset1.hpp"

typedef unsigned long long size_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#define EXPORT extern
#define CNAME extern "C"
#define NULL nullptr
#define TAB_WIDTH 4

extern bool leftShiftPressed, rightShiftPressed, capsLockPressed;
char charToUpper(char chr); // It would be a circular import
char charToLower(char chr); // It would be a circular import
char intToStringOutput[128];
template<typename T>
const char* intToString(T value) {

	uint8_t isNegative = 0;

	if (value < 0) {
		isNegative = 1;
		value *= -1;
		intToStringOutput[0] = '-';
	}

	uint8_t size = 0;
	uint64_t sizeTester = (uint64_t)value;
	while (sizeTester / 10 > 0) {
		sizeTester /= 10;
		size++;
	}

	uint8_t index = 0;
	uint64_t newValue = (uint64_t)value;
	while (newValue / 10 > 0) {
		uint8_t remainder = newValue % 10;
		newValue /= 10;
		intToStringOutput[isNegative + size - index] = remainder + 48; 
		index++;
	}
	uint8_t remainder = newValue % 10;
	intToStringOutput[isNegative + size - index] = remainder + 48;
	intToStringOutput[isNegative + size + 1] = 0;
	return intToStringOutput;
}

const char* intToString(uint8_t value) { return intToString<uint8_t>(value); }
const char* intToString(uint16_t value) { return intToString<uint16_t>(value); }
const char* intToString(uint32_t value) { return intToString<uint32_t>(value); }
const char* intToString(uint64_t value) { return intToString<uint64_t>(value); }
const char* intToString(char value) { return intToString<char>(value); }
const char* intToString(short value) { return intToString<short>(value); }
const char* intToString(int value) { return intToString<int>(value); }
const char* intToString(long long value) { return intToString<long long>(value); }

char processCharacter(int scanCode) {
    if (leftShiftPressed | rightShiftPressed) {
        if (!capsLockPressed) {
            return charToUpper(KBSet1ScanCodeLookupTableShift[scanCode]);
        } else {
            return charToLower(KBSet1ScanCodeLookupTableShift[scanCode]);
        }
    } else if (capsLockPressed) {
        return charToUpper(KBSet1ScanCodeLookupTable[scanCode]);
    } else {
        return charToLower(KBSet1ScanCodeLookupTable[scanCode]);
    }
}