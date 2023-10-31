#ifndef LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_PICTURE_PROCESSING_PICTURE_PROCESSING_H_

#define LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_PICTURE_PROCESSING_PICTURE_PROCESSING_H_

#include "sandpile_processing/sandpile_processing.h"
#include "arguments_parsing/arguments_parsing.h"
#include "file_reading/file_reading.h"

#include <cstring>
#include <string>
#include <fstream>

struct BmpHeader {
  char bitmapSignatureBytes[2] = {'B', 'M'};
  uint32_t sizeOfBitmapFile = 46;
  uint32_t reservedBytes = 0;
  uint32_t pixelDataOffset = 46;
};
struct BmpInfoHeader {
  uint32_t sizeOfThisHeader = 32;
  int16_t width; // in pixels
  int16_t height; // in pixels
  uint16_t numberOfColorPlanes = 1; // must be 1
  uint16_t colorDepth = 3;
  uint32_t compressionMethod = 0;
  uint32_t rawBitmapDataSize = 0; // generally ignored
  int32_t horizontalResolution = 3780; // in pixel per meter
  int32_t verticalResolution = 3780; // in pixel per meter
  uint32_t colorTableEntries = 0;
  uint32_t importantColors = 0;
};
struct Pixel {
  uint8_t blue = 1;
  uint8_t green = 1;
  uint8_t red = 0;
};

void SaveImage(SandPileParameters sp, OptionsList options, int img_index);

#endif //LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_PICTURE_PROCESSING_PICTURE_PROCESSING_H_
