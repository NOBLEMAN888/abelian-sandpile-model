#include "sandpile_processing.h"

uint64_t** DoubleMatrix(SandPileParameters& sp, int16_t offset_x, int16_t offset_y) {
  uint64_t** new_sp = new uint64_t* [sp.size_y];
  for (int16_t i = 0; i < sp.size_y; ++i) {
    new_sp[i] = new uint64_t[sp.size_x];
    for (int16_t j = 0; j < sp.size_x; ++j) {
      if (sp.from_y <= i - offset_y && i - offset_y < sp.to_y && sp.from_x <= j - offset_x && j - offset_x < sp.to_x) {
        new_sp[i][j] = sp.matrix[i - offset_y][j - offset_x];
      } else {
        new_sp[i][j] = 0;
      }
    }
    if (sp.from_y <= i - offset_y && i - offset_y < sp.to_y) {
      delete[] sp.matrix[i - offset_y];
    }
  }
  delete[] sp.matrix;
  return new_sp;
}

void ClearMatrix(SandPileParameters& sp) {
  for (int16_t i = 0; i < sp.size_y; ++i) {
    delete[] sp.matrix[i];
  }
  delete[] sp.matrix;
}

void PerformSandPile(SandPileParameters& sp, OptionsList& options) {
  CoordsList unstable_coords;
  bool need_to_add;
  int iters = 0;
  int iter_to_save = 1;
  int num_of_images = 1;
  int16_t offset_x, offset_y;
  while (iters < options.max_num_of_iters || options.max_num_of_iters == -1) {
    offset_x = 0;
    offset_y = 0;
    need_to_add = false;
    for (int16_t i = sp.from_y; i < sp.to_y; ++i) {
      for (int16_t j = sp.from_x; j < sp.to_x; ++j) {
        if (sp.matrix[i][j] >= 4) {
          unstable_coords.PushBack(j, i, 1);
          sp.matrix[i][j] -= 4;
          if (i == 0 || i == sp.size_y - 1 || j == 0 || j == sp.size_x - 1) {
            need_to_add = true;
          }
        }
      }
    }
    if (unstable_coords.IsEmpty()) {
      break;
    }
    if (need_to_add) {
      offset_x = sp.size_x / 2;
      offset_y = sp.size_y / 2;
      sp.size_y *= 2;
      sp.size_x *= 2;
      sp.matrix = DoubleMatrix(sp, offset_x, offset_y);
      sp.from_y += offset_y;
      sp.to_y += offset_y;
      sp.from_x += offset_x;
      sp.to_x += offset_x;
    }

    while (!unstable_coords.IsEmpty()) {
      sp.matrix[unstable_coords.head->y + 1 + offset_y][unstable_coords.head->x + offset_x] += 1;
      sp.matrix[unstable_coords.head->y - 1 + offset_y][unstable_coords.head->x + offset_x] += 1;
      sp.matrix[unstable_coords.head->y + offset_y][unstable_coords.head->x + 1 + offset_x] += 1;
      sp.matrix[unstable_coords.head->y + offset_y][unstable_coords.head->x - 1 + offset_x] += 1;
      if (unstable_coords.head->y - 1 + offset_y < sp.from_y) {
        --sp.from_y;
      }
      if (unstable_coords.head->y + 1 + offset_y >= sp.to_y) {
        ++sp.to_y;
      }
      if (unstable_coords.head->x - 1 + offset_x < sp.from_x) {
        --sp.from_x;
      }
      if (unstable_coords.head->x + 1 + offset_x >= sp.to_x) {
        ++sp.to_x;
      }
      unstable_coords.Shift();
    }
    if (options.freq_of_saving > 0 && iter_to_save == options.freq_of_saving) {
      SaveImage(sp, options, num_of_images);
      ++num_of_images;
      iter_to_save = 0;
    }
    ++iter_to_save;
    ++iters;
  }
  if (options.freq_of_saving == 0) {
    SaveImage(sp, options, num_of_images
    );
  }
  ClearMatrix(sp);
};
