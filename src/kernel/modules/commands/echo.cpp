#pragma once
#include "../Typedefs.hpp"
#include "../drivers/Screen.cpp"

void echoCommand(char* commandParts[], uint32_t tokenCount) {
  for (size_t i = 0; i < tokenCount; i++) {
    if (i == 0) {
      continue;
    }
    if (i > 1) {
      printString(" ");
    }
    printString(commandParts[i]);
  }
  printString("\r\n");
}