#include "picture_processing.h"

void SaveImage(SandPileParameters& sp, OptionsList& options, int img_index) {
  char file_path[GetStringLen(std::to_string(img_index).c_str()) + 4 + GetStringLen(options.path_to_save)];
  strcpy(file_path, options.path_to_save);
  strcat(file_path, std::to_string(img_index).c_str());
  strcat(file_path, ".bmp");
  std::ofstream file(file_path, std::ios::out | std::ios::binary);
  uint16_t width = sp.to_x - sp.from_x;
  uint16_t height = sp.to_y - sp.from_y;
  const uint64_t padding = (8 - (width % 8)) % 8;
  const uint64_t full_width = width + padding;

  const uint64_t fileSize = kFileHeaderSize + kInformationHeaderSize + kColorPalleteSize + (full_width * height) / 2;
  uint8_t fileHeader[kFileHeaderSize] = {};
  uint8_t informationHeader[kInformationHeaderSize] = {};

  //file type
  fileHeader[0] = 'B';
  fileHeader[1] = 'M';
  //file size
  fileHeader[2] = fileSize;
  fileHeader[3] = fileSize >> 8;
  fileHeader[4] = fileSize >> 16;
  fileHeader[5] = fileSize >> 24;
  //reserved
  fileHeader[6] = 0;
  fileHeader[7] = 0;
  fileHeader[8] = 0;
  fileHeader[9] = 0;
  //number of bytes between start of file and the first byte of pixel data
  fileHeader[10] = kFileHeaderSize + kInformationHeaderSize + kColorPalleteSize;
  fileHeader[11] = 0;
  fileHeader[12] = 0;
  fileHeader[13] = 0;
  //information_header size
  informationHeader[0] = kInformationHeaderSize;
  informationHeader[1] = 0;
  informationHeader[2] = 0;
  informationHeader[3] = 0;
  //width of image
  informationHeader[4] = width;
  informationHeader[5] = width >> 8;
  informationHeader[6] = width >> 16;
  informationHeader[7] = width >> 24;
  //height of image
  informationHeader[8] = height;
  informationHeader[9] = height >> 8;
  informationHeader[10] = height >> 16;
  informationHeader[11] = height >> 24;
  //planes
  informationHeader[12] = 1;
  informationHeader[13] = 0;
  //bits per pixel
  informationHeader[14] = kBitsPerPixel;
  informationHeader[15] = 0;
  //total colors: black, white, green, purple, yellow
  informationHeader[32] = kTotalColors;
  informationHeader[33] = 0;
  informationHeader[34] = 0;
  informationHeader[35] = 0;

  ColorsPreset colors;
  uint8_t colorPallete[kColorPalleteSize] = {};
  //0 - white
  colorPallete[0] = colors.kColorWhite.b;
  colorPallete[1] = colors.kColorWhite.g;
  colorPallete[2] = colors.kColorWhite.r;
  colorPallete[3] = 0;
  //1 - green
  colorPallete[4] = colors.kColorGreen.b;
  colorPallete[5] = colors.kColorGreen.g;
  colorPallete[6] = colors.kColorGreen.r;
  colorPallete[7] = 0;
  //2 - purple
  colorPallete[8] = colors.kColorYellow.b;
  colorPallete[9] = colors.kColorYellow.g;
  colorPallete[10] = colors.kColorYellow.r;
  colorPallete[11] = 0;
  //3 - yellow
  colorPallete[12] = colors.kColorPurple.b;
  colorPallete[13] = colors.kColorPurple.g;
  colorPallete[14] = colors.kColorPurple.r;
  colorPallete[15] = 0;
  //4 - black
  colorPallete[16] = colors.kColorBlack.b;
  colorPallete[17] = colors.kColorBlack.g;
  colorPallete[18] = colors.kColorBlack.r;
  colorPallete[19] = 0;

  file.write(reinterpret_cast<char*>(fileHeader), kFileHeaderSize);
  file.write(reinterpret_cast<char*>(informationHeader), kInformationHeaderSize);
  file.write(reinterpret_cast<char*>(colorPallete), kColorPalleteSize);

  uint64_t first_color, second_color;
  uint8_t total_color;
  for (int64_t y = height - 1; y >= 0; y--) {
    for (int64_t x = 0; x < full_width; x += 2) {
      if (x >= width) {
        first_color = 0;
        second_color = 0;
      } else if (x + 1 >= width) {
        first_color = sp.matrix[y + sp.from_y][x + sp.from_x];
        second_color = 0;
      } else {
        first_color = sp.matrix[y + sp.from_y][x + sp.from_x];
        second_color = sp.matrix[y + sp.from_y][x + sp.from_x + 1];
      }
      if (first_color >= 4) {
        first_color = 4;
      }
      if (second_color >= 4) {
        second_color = 4;
      }
      total_color = (first_color << kBitsPerPixel);
      total_color += second_color;
      file << total_color;
    }
  }
  file.close();
}
