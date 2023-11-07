#include "../modules/src/arguments_parsing/arguments_parsing.cpp"
#include "../modules/src/file_reading/file_reading.cpp"
#include "../modules/src/sandpile_processing/sandpile_processing.cpp"

#include <iostream>

int main(int argc, char* argv[]) {
  OptionsList options = ParseArguments(argc, argv);
  SandPileParameters sp = GetMatrixFromFile(options);
  PerformSandPile(sp, options);
//  SaveImage(sp, options, 10);
//  std::cout << options.file_name << ' ' << options.path_to_save << ' ' << options.max_num_of_iters << ' '
//            << options.freq_of_saving;
//  SandPile(4, 3, 9, 5);
  return 0;
}
