#include "picture_processing.h"



void SaveImage(SandPileParameters sp, OptionsList options, int img_index) {
  char file_path[GetStringLen(options.file_name) + GetStringLen(options.path_to_open)];
  strcpy(file_path, options.path_to_open);
  strcat(file_path, std::to_string(img_index).c_str());
  strcat(file_path, ".bmp");
  std::ofstream file(file_path, std::ofstream::out);
  if (!file.is_open()) {
    LogErrorFileNotOpened();
  }
  BmpHeader header;
  BmpInfoHeader info_header;
  info_header.width = sp.size_x;
  info_header.height = sp.size_y;
  header.sizeOfBitmapFile += sp.size_x * sp.size_y * 3 / 8;
  Pixel pixel;
  file.write((char *) &header, 14);
  file.write((char *) &header, 40);

  // writing pixel data
  size_t numberOfPixels = info_header.width * info_header.height;
  for (int i = 0; i < numberOfPixels; i++) {
    file.write((char *) &pixel, 3);
  }
  file.close();
}

