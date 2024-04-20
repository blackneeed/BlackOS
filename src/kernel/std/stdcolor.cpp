#pragma once
#include <std/stdstring.cpp>
#include <std/stdlookup.hpp>

#define FG_BLACK 0x00 // "0"
#define FG_BLUE 0x01 // "1"
#define FG_GREEN 0x02 // "2"
#define FG_CYAN 0x03 // "3"
#define FG_RED 0x04 // "4"
#define FG_MAGENTA 0x05 // "5"
#define FG_BROWN 0x06 // "6"
#define FG_LIGHTGRAY 0x07 // "7"
#define FG_DARKGRAY 0x08 // "8"
#define FG_LIGHTBLUE 0x09 // "9"
#define FG_LIGHTGREEN 0x0A // "A"
#define FG_LIGHTCYAN 0x0B // "B"
#define FG_LIGHTRED 0x0C // "C"
#define FG_LIGHTMAGENTA 0x0D // "D"
#define FG_YELLOW 0x0E // "E"
#define FG_WHITE 0x0F // "F"

#define BG_BLACK 0x00 // "0"
#define BG_BLUE 0x10 // "1"
#define BG_GREEN 0x20 // "2"
#define BG_CYAN 0x30 // "3"
#define BG_RED 0x40 // "4"
#define BG_MAGENTA 0x50 // "5"
#define BG_BROWN 0x60 // "6"
#define BG_LIGHTGRAY 0x70 // "7"
#define BG_BLINKINGBLACK 0x80 // "8"
#define BG_BLINKINGBLUE 0x90 // "9"
#define BG_BLINKINGGREEN 0xA0 // "A"
#define BG_BLINKINGCYAN 0xB0 // "B"
#define BG_BLINKINGRED 0xC0 // "C"
#define BG_BLINKINGMAGENTA 0xD0 // "D"
#define BG_BLINKINGYELLOW 0xE0 // "E"
#define BG_BLINKINGWHITE 0xF0 // "F"

#define ANSI_BLACK_FG "\033[30m"
#define ANSI_RED_FG "\033[31m"
#define ANSI_GREEN_FG "\033[32m"
#define ANSI_YELLOW_FG "\033[33m"
#define ANSI_BLUE_FG "\033[34m"
#define ANSI_MAGENTA_FG "\033[35m"
#define ANSI_CYAN_FG "\033[36m"
#define ANSI_WHITE_FG "\033[37m"

#define ANSI_BLACK_BG "\033[40m"
#define ANSI_RED_BG "\033[41m"
#define ANSI_GREEN_BG "\033[42m"
#define ANSI_YELLOW_BG "\033[43m"
#define ANSI_BLUE_BG "\033[44m"
#define ANSI_MAGENTA_BG "\033[45m"
#define ANSI_CYAN_BG "\033[46m"
#define ANSI_WHITE_BG "\033[47m"

#define ANSI_RESET "\033[0m"

#define LOOKUP_BG 0
#define LOOKUP_FG 1

u8 getColor(char c, int mode) {
  if (mode == LOOKUP_BG) {
    switch (charToUpper(c)) {
      case '0': return BG_BLACK; break;
      case '1': return BG_BLUE; break;
      case '2': return BG_GREEN; break;
      case '3': return BG_CYAN; break;
      case '4': return BG_RED; break;
      case '5': return BG_MAGENTA; break;
      case '6': return BG_BROWN; break;
      case '7': return BG_LIGHTGRAY; break;
      case '8': return BG_BLINKINGBLACK; break;
      case '9': return BG_BLINKINGBLUE; break;
      case 'A': return BG_BLINKINGGREEN; break;
      case 'B': return BG_BLINKINGCYAN; break;
      case 'C': return BG_BLINKINGRED; break;
      case 'D': return BG_BLINKINGMAGENTA; break;
      case 'E': return BG_BLINKINGYELLOW; break;
      case 'F': return BG_BLINKINGWHITE; break;
      default: return LOOKUP_UNKNOWN; break;
    }
  } else if (mode == LOOKUP_FG) {
    switch (charToUpper(c)) { 
      case '0': return FG_BLACK; break;
      case '1': return FG_BLUE; break;
      case '2': return FG_GREEN; break;
      case '3': return FG_CYAN; break;
      case '4': return FG_RED; break;
      case '5': return FG_MAGENTA; break;
      case '6': return FG_BROWN; break;
      case '7': return FG_LIGHTGRAY; break;
      case '8': return FG_DARKGRAY; break;
      case '9': return FG_LIGHTBLUE; break;
      case 'A': return FG_LIGHTGREEN; break;
      case 'B': return FG_LIGHTCYAN; break;
      case 'C': return FG_LIGHTRED; break;
      case 'D': return FG_LIGHTMAGENTA; break;
      case 'E': return FG_YELLOW; break;
      case 'F': return FG_WHITE; break;
      default: return LOOKUP_UNKNOWN; break;
    }
  } else {
    return LOOKUP_UNKNOWN;
  }
}

const char* colorHelpLookup(char* colorMode) {
    if (strcmp(colorMode, "fg")) {
        return "0: Black\r\n1: Blue\r\n2: Green\r\n3: Cyan\r\n4: Red\r\n5: Magenta\r\n6: Brown\r\n7: Light Gray\r\n8: Dark Gray\r\n9: Light Blue\r\nA: Light Green\r\nB: Light Cyan\r\nC: Light Red\r\nD: Light Magenta\r\nE: Yellow\r\nF: White";
    } else if (strcmp(colorMode, "bg")) {
        return "0: Black\r\n1: Blue\r\n2: Green\r\n3: Cyan\r\n4: Red\r\n5: Magenta\r\n6: Brown\r\n7: Light Gray\r\n8: Blinking Black\r\n9: Blinking Blue\r\nA: Blinking Green\r\nB: Blinking Cyan\r\nC: Blinking Red\r\nD: Blinking Magenta\r\nE: Blinking Yellow\r\nF: Blinking White";
    } else {
        return (const char*)LOOKUP_UNKNOWN; // Again, stop VSCode from yelling at me
    }
}