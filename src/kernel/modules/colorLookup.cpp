#pragma once
#include "StringUtil.cpp"
#include "LookupUtil.cpp"
#define LOOKUP_BG 0
#define LOOKUP_FG 1

uint8_t getColor(char c, int mode) {
  if (mode == LOOKUP_BG) {
    switch (charToUpper(c)) {
      case '0': return BG_BLACK;
      case '1': return BG_BLUE;
      case '2': return BG_GREEN;
      case '3': return BG_CYAN;
      case '4': return BG_RED;
      case '5': return BG_MAGENTA;
      case '6': return BG_BROWN;
      case '7': return BG_LIGHTGRAY;
      case '8': return BG_BLINKINGBLACK;
      case '9': return BG_BLINKINGBLUE;
      case 'A': return BG_BLINKINGGREEN;
      case 'B': return BG_BLINKINGCYAN;
      case 'C': return BG_BLINKINGRED;
      case 'D': return BG_BLINKINGMAGENTA;
      case 'E': return BG_BLINKINGYELLOW;
      case 'F': return BG_BLINKINGWHITE;
      default: return LOOKUP_UNKNOWN;
    }
  } else if (mode == LOOKUP_FG) {
    switch (charToUpper(c)) { 
      case '0': return FG_BLACK;
      case '1': return FG_BLUE;
      case '2': return FG_GREEN;
      case '3': return FG_CYAN;
      case '4': return FG_RED;
      case '5': return FG_MAGENTA;
      case '6': return FG_BROWN;
      case '7': return FG_LIGHTGRAY;
      case '8': return FG_DARKGRAY;
      case '9': return FG_LIGHTBLUE;
      case 'A': return FG_LIGHTGREEN;
      case 'B': return FG_LIGHTCYAN;
      case 'C': return FG_LIGHTRED;
      case 'D': return FG_LIGHTMAGENTA;
      case 'E': return FG_YELLOW;
      case 'F': return FG_WHITE;
      default: return LOOKUP_UNKNOWN;
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
        return LOOKUP_UNKNOWN;
    }
}