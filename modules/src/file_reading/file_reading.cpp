#include "file_reading.h"

#include "arguments_parsing/arguments_parsing.h"

#include <fstream>
#include <cstring>
#include <iostream>


void LogErrorFileNotOpened() {
  std::cerr << "Can't open the file!";
  exit(EXIT_FAILURE);
}
bool IsDigit(const char chr) {
  return '0' <= chr && chr <= '9';
}
int GetDigitFromChar(const char chr) {
  return chr - '0';
}

SandPileParameters GetMatrixFromFile(OptionsList options) {
  char file_path[GetStringLen(options.file_name) + GetStringLen(options.path_to_open)];
  strcpy(file_path, options.path_to_open);
  strcat(file_path, options.file_name);
  std::ifstream file(file_path, std::ios::in);
  if (!file.is_open()) {
    LogErrorFileNotOpened();
  }
  char tmp;
  file.seekg(0, std::ios::beg);
  int cnt = 0;
  int16_t x = 0, y = 0;
  uint64_t num = 0;
  int16_t max_x = 0, max_y = 0;
  CoordsList list;
  SandPileParameters sp;
  while (file.get(tmp)) {
    if (tmp == '\t') {
      ++cnt;
    } else if (tmp == '\n') {
      cnt = 0;
      if (x > max_x) {
        max_x = x;
      }
      if (y > max_y) {
        max_y = y;
      }
      list.PushBack(x, y, num);
      x = 0;
      y = 0;
      num = 0;
    } else if (IsDigit(tmp)) {
      switch (cnt) {
        case 0:
          x = x * 10 + GetDigitFromChar(tmp);
          break;
        case 1:
          y = y * 10 + GetDigitFromChar(tmp);
          break;
        case 2:
          num = num * 10 + GetDigitFromChar(tmp);
          break;
        default:
          break;
      }
    }
  }
  file.close();
  sp.size_x = max_x + 1;
  sp.size_y = max_y + 1;
  sp.matrix = new uint64_t*[sp.size_y];
  for (int16_t i = 0; i < sp.size_y; ++i) {
    sp.matrix[i] = new uint64_t[sp.size_x];
    for (int16_t j = 0; j < sp.size_x; ++j) {
      sp.matrix[i][j] = 0;
    }
  }
  while (!list.IsEmpty()) {
    sp.matrix[list.head->y][list.head->x] += list.head->num;
    list.Shift();
  }
  return sp;
}
