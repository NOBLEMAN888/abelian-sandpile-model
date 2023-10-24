#include <arguments_parsing/arguments_parsing.h>
//#include <file_reading/file_reading.h>
//#include <picture_processing/picture_processing.h>
//#include <sandpile_processing/sandpile_processing.h>

#include <iostream>


int main(int argc, char* argv[]) {
  OptionsList options = ParseArguments(argc, argv);
  std::cout << options.file_name << ' ' << options.path_to_save << ' ' << options.max_num_of_iters << ' ' << options.freq_of_saving;
  return 0;
}

