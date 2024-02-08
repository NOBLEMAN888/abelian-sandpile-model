#ifndef LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_SANDPILE_PROCESSING_SANDPILE_PROCESSING_H_

#define LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_SANDPILE_PROCESSING_SANDPILE_PROCESSING_H_

#include "../file_reading/file_reading.h"
#include "../arguments_parsing/arguments_parsing.h"
#include "../picture_processing/picture_processing.cpp"

#include <iostream>

uint64_t** DoubleMatrix(SandPileParameters& sp, int16_t offset_x, int16_t offset_y);

void ClearMatrix(SandPileParameters& sp);

void PerformSandPile(SandPileParameters& sp, OptionsList& options);

#endif //LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_SANDPILE_PROCESSING_SANDPILE_PROCESSING_H_
