#pragma once
#include <std/stdint.hpp>
#include <std/stdterm.cpp>

void echoCommand(char* commandParts[], const uint32_t tokenCount) {
  for (size_t i = 0; i < tokenCount; i++) {
    if (i == 0) {
      continue;
    }
    if (i > 1) {
      termPrintString(" ");
    }
    termPrintString(commandParts[i]);
  }
  termPrintLn();
}