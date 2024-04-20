#pragma once
#include <modules/kb/PLKBSet.hpp> // Change this to import another kbset if you want another keyboard layout
#include <std/stdcharInfo.hpp>
#include <std/stdint.hpp>

#define EXPORT extern
#define CNAME extern "C"
#define NULL nullptr
#define TAB_WIDTH 4

extern bool leftShiftPressed, rightShiftPressed, capsLockPressed, altPressed;
char charToUpper(char chr); // It would be a circular import
char charToLower(char chr); // It would be a circular import
char intToStringOutput[128];
template<typename T>
const char* intToString(T value) {

	u8 isNegative = 0;

	if (value < 0) {
		isNegative = 1;
		value *= -1;
		intToStringOutput[0] = '-';
	}

	u8 size = 0;
	u64 sizeTester = (u64)value;
	while (sizeTester / 10 > 0) {
		sizeTester /= 10;
		size++;
	}

	u8 index = 0;
	u64 newValue = (u64)value;
	while (newValue / 10 > 0) {
		u8 remainder = newValue % 10;
		newValue /= 10;
		intToStringOutput[isNegative + size - index] = remainder + 48; 
		index++;
	}
	u8 remainder = newValue % 10;
	intToStringOutput[isNegative + size - index] = remainder + 48;
	intToStringOutput[isNegative + size + 1] = 0;
	return intToStringOutput;
}

const char* intToString(u8 value) { return intToString<u8>(value); }
const char* intToString(u16 value) { return intToString<u16>(value); }
const char* intToString(u32 value) { return intToString<u32>(value); }
const char* intToString(u64 value) { return intToString<u64>(value); }
const char* intToString(i8 value) { return intToString<i8>(value); }
const char* intToString(i16 value) { return intToString<i16>(value); }
const char* intToString(i32 value) { return intToString<i32>(value); }
const char* intToString(i64 value) { return intToString<i64>(value); }

CharInfo processCharacter(int scanCode) {
	if ((leftShiftPressed || rightShiftPressed) && altPressed) {
		return {true, '\0'};
	}
    if (leftShiftPressed || rightShiftPressed) {
        if (!capsLockPressed) {
			return {false, charToUpper(ScanCodeLookupTableShift[scanCode])};
        } else {
            return {false, charToLower(ScanCodeLookupTableShift[scanCode])};
        }
    } else if (altPressed && capsLockPressed) {
		return {false, charToUpper(ScanCodeLookupTableAlt[scanCode])};
	} else if (altPressed && !capsLockPressed) {
		return {false, charToLower(ScanCodeLookupTableAlt[scanCode])};
	} else if (capsLockPressed) {
        return {false, charToUpper(ScanCodeLookupTable[scanCode])};
    } else {
        return {false, charToLower(ScanCodeLookupTable[scanCode])};
    }
}