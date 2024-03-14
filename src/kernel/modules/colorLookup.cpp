#pragma once
#include "../std/stdstring.cpp"
#include "lookup.cpp"
#define LOOKUP_BG 0
#define LOOKUP_FG 1

uint8_t getColor(char c, int mode) {
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
        return LOOKUP_UNKNOWN;
    }
}