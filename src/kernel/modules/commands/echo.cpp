#pragma once
#include "../../std/stdlib.hpp"
#include "../../std/stdio.cpp"

void echoCommand(char* commandParts[], const uint32_t tokenCount) {
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