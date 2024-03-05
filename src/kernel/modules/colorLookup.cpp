#pragma once
#define LOOKUP_BG 0
#define LOOKUP_FG 1
#define LOOKUP_UNKNOWN 128

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