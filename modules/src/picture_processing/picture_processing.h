#ifndef LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_PICTURE_PROCESSING_PICTURE_PROCESSING_H_

#define LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_PICTURE_PROCESSING_PICTURE_PROCESSING_H_

#include "../sandpile_processing/sandpile_processing.h"
#include "../arguments_parsing/arguments_parsing.h"
#include "../file_reading/file_reading.h"

#include <cstring>
#include <string>
#include <fstream>

struct Color {
  uint8_t r = 0, g = 0, b = 0;
  Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {};
};

struct ColorsPreset {
  const Color kColorWhite = Color(255, 255, 255);
  const Color kColorGreen = Color(34, 245, 20);
  const Color kColorYellow = Color(245, 227, 20);
  const Color kColorPurple = Color(227, 20, 245);
  const Color kColorBlack = Color(0, 0, 0);
};

const uint64_t kFileHeaderSize = 14;
const uint64_t kInformationHeaderSize = 40;
const uint64_t kTotalColors = 5;
const uint64_t kBitsPerPixel = 4;
const uint64_t kColorBytes = 4;
const uint64_t kColorPalleteSize = kColorBytes * kTotalColors;

void SaveImage(SandPileParameters& sp, OptionsList& options, int img_index);

#endif //LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_PICTURE_PROCESSING_PICTURE_PROCESSING_H_
