#ifndef LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_ARGUMENTS_PARSING_ARGUMENTS_PARSING_H_

#define LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_ARGUMENTS_PARSING_ARGUMENTS_PARSING_H_

#include <cstdint>

struct OptionsList {  // The list of options to get from arguments
  char* file_name;
  char* path_to_open = "E:\\My space\\ITMO\\OP\\lab3\\labwork3-NOBLEMAN888\\files\\";
  char* path_to_save;
  int64_t max_num_of_iters = -1;
  int64_t freq_of_saving = 0;
  const int kNumberOfArguments = 8;
};

struct ArgumentParameters { // The list of arguments to look for
  const char* kArgumentKey;
  const int kArgumentLen;
  const int kArgumentType;
};

void LogErrorInvalidArg();  // If argument is invalid, logs the error and exits program

void LogErrorInvalidArgNum(); // If 2-part argument doesn't have second part ,logs the error and exits program

size_t CompareStrings(const char* s1, const char* s2, size_t count);  // Compares 2 strings. Return 0, if they are equal

size_t GetStringLen(const char* str);  // Returns the numbers of chars in string

char* GetStringArgumentValue(char* s);  // Extracts and returns the string value from 2-part argument

int64_t GetInt64ArgumentValue(char* s); // Extracts and returns the int64 value from 2-part argument

OptionsList ParseArguments(int argc, char* argv[]); // The main parsing function, returns an OptionsList type instance

#endif //LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_ARGUMENTS_PARSING_ARGUMENTS_PARSING_H_
