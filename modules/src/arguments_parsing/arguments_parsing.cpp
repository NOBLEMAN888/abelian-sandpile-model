#include "arguments_parsing.h"

#include <algorithm>
#include <iostream>

void LogErrorInvalidArg() {
  std::cerr << "Argument not recognized!";
  exit(EXIT_FAILURE);
};

void LogErrorInvalidArgNum() {
  std::cerr << "No second argument!";
  exit(EXIT_FAILURE);
};

void LogErrorFileNotFound() {
  std::cerr << "No file with that name!";
  exit(EXIT_FAILURE);
};

void LogErrorFileNotOpened() {
  std::cerr << "Can't open the file!";
  exit(EXIT_FAILURE);
};

size_t CompareStrings(const char* s1, const char* s2, size_t count) {
  while (count > 0 && *s1 != '\0' && (*s1 == *s2)) {
    ++s1;
    ++s2;
    --count;
  }
  if (count == 0) {
    return 0;
  }

  return (*s1 > *s2) - (*s2 > *s1);
};
static size_t GetStringLen(const char* str) {
  const char* ptr = str;
  for (; *ptr != '\0'; ++ptr);
  return ptr - str;
};
char* GetStringArgumentValue(char* s) {
  return std::find(s, s + GetStringLen(s), '=') + 1;
}
int64_t GetInt64ArgumentValue(char* s) {
  return std::stoll(GetStringArgumentValue(s), nullptr, 10);
}

OptionsList ParseArguments(int argc, char* argv[]) {
  OptionsList options;
  ArgumentParameters arguments[] = {
      "-i", 2, 0,
      "--input=", 8, 0,
      "-o", 2, 1,
      "--output=", 9, 1,
      "-m", 2, 2,
      "--max-iter=", 11, 2,
      "-f", 2, 3,
      "--freq=", 7, 3
  };
  int i = 1;
  bool is_argument_correct;
  while (i < argc) {
    is_argument_correct = false;
    for (int j = 0; j < options.kNumberOfArguments; ++j) {
      if (!CompareStrings(argv[i], arguments[j].kArgumentKey, arguments[j].kArgumentLen)) {
        is_argument_correct = true;
        if (arguments[j].kArgumentLen == 2) {
          if (i < argc - 1) {
            switch (arguments[j].kArgumentType) {
              case 0:
                options.file_name = argv[++i];
                break;
              case 1:
                options.path_to_save = argv[++i];
                break;
              case 2:
                options.max_num_of_iters = std::stoll(argv[++i], nullptr, 10);
                break;
              case 3:
                options.freq_of_saving = std::stoll(argv[++i], nullptr, 10);
                break;
              default:
                break;
            }
          } else {
            LogErrorInvalidArgNum();
          }
        } else {
          switch (arguments[j].kArgumentType) {
            case 0:
              options.file_name = GetStringArgumentValue(argv[i]);
              break;
            case 1:
              options.path_to_save = GetStringArgumentValue(argv[i]);
              break;
            case 2:
              options.max_num_of_iters = GetInt64ArgumentValue(argv[i]);
              break;
            case 3:
              options.freq_of_saving = GetInt64ArgumentValue(argv[i]);
              break;
            default:
              break;
          }
        }
      }
    }
    if (!is_argument_correct) {
      LogErrorInvalidArg();
    }
    ++i;
  }
  return options;
};

//if (!CompareStrings(argv[i], options.kFileShortArg, options.kShortArgLen)) {
//if (i < argc - 1) {
//options.file_name = argv[++i];
//} else {
//LogErrorInvalidArgNum();
//}
//} else if (!CompareStrings(argv[i], options.kFileLongArg, options.kFileLongLen)) {
//options.file_name = std::find(argv[i], argv[i] + GetStringLen(argv[i]), '=') + 1;
//} else if (!CompareStrings(argv[i], options.kPathShortArg, options.kShortArgLen)) {
//if (i < argc - 1) {
//options.path_to_save = argv[++i];
//} else {
//LogErrorInvalidArgNum();
//}
//} else if (!CompareStrings(argv[i], options.kPathLongArg, options.kPathLongLen)) {
//options.path_to_save = std::find(argv[i], argv[i] + GetStringLen(argv[i]), '=') + 1;
//} else if (!CompareStrings(argv[i], options.kItersShortArg, options.kShortArgLen)) {
//if (i < argc - 1) {
//options.max_num_of_iters = std::atoll(argv[++i]);
//} else {
//LogErrorInvalidArgNum();
//}
//} else if (!CompareStrings(argv[i], options.kItersLongArg, options.kItersLongLen)) {
//options.max_num_of_iters = std::atoll(std::find(argv[i], argv[i] + GetStringLen(argv[i]), '=') + 1);
//} else if (!CompareStrings(argv[i], options.kFreqShortArg, options.kShortArgLen)) {
//if (i < argc - 1) {
//options.freq_of_saving = std::atoll(argv[++i]);
//} else {
//LogErrorInvalidArgNum();
//}
//} else if (!CompareStrings(argv[i], options.kFreqLongArg, options.kFreqLongLen)) {
//options.freq_of_saving = std::atoll(std::find(argv[i], argv[i] + GetStringLen(argv[i]), '=') + 1);
//} else {
//LogErrorInvalidArg();
//}