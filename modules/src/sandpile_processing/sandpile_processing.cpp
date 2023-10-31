#include "sandpile_processing.h"

void PerformSandPile(SandPileParameters sp, OptionsList options) {
  CoordsList unstable_coords;
  bool add_up, add_right, add_down, add_left;
  int iters = 0;
  int iter_to_save = 1;
  int num_of_images = 1;
  while (iters < options.max_num_of_iters || options.max_num_of_iters == -1) {
    add_up = false;
    add_right = false;
    add_down = false;
    add_left = false;
    for (int i = 0; i < sp.size_y; ++i) {
      for (int j = 0; j < sp.size_x; ++j) {
        if (sp.matrix[i][j] >= 4) {
          unstable_coords.PushBack(j, i, sp.matrix[i][j] / 4);
          sp.matrix[i][j] %= 4;
          if (i == 0) {
            add_up = true;
          }
          if (i == sp.size_y - 1) {
            add_down = true;
          }
          if (j == 0) {
            add_left = true;
          }
          if (j == sp.size_x - 1) {
            add_right = true;
          }
        }
      }
    }
    if (unstable_coords.IsEmpty()) {
      break;
    }
    if (add_up || add_right || add_down || add_left) {
      sp.size_y += add_up + add_down;
      sp.size_x += add_left + add_right;
      uint64_t** new_sp = new uint64_t* [sp.size_y];
      for (int16_t i = 0; i < sp.size_y; ++i) {
        new_sp[i] = new uint64_t[sp.size_x];
        for (int16_t j = 0; j < sp.size_x; ++j) {
          if (i == 0 && add_up || i == sp.size_y - 1 && add_down || j == 0 && add_left
              || j == sp.size_x - 1 && add_right) {
            new_sp[i][j] = 0;
          } else {
            new_sp[i][j] = sp.matrix[i][j];
          }
        }
        if (add_up <= i && i < sp.size_y - add_down) {
          delete[] sp.matrix[i];
        }
      }
      delete[] sp.matrix;
      sp.matrix = new_sp;
      for (int16_t i = 0; i < sp.size_y; ++i) {
        delete[] new_sp[i];
      }
      delete[] new_sp;
    }

    while (!unstable_coords.IsEmpty()) {
      sp.matrix[unstable_coords.head->y + 1][unstable_coords.head->x] += unstable_coords.head->num;
      sp.matrix[unstable_coords.head->y - 1][unstable_coords.head->x] += unstable_coords.head->num;
      sp.matrix[unstable_coords.head->y][unstable_coords.head->x + 1] += unstable_coords.head->num;
      sp.matrix[unstable_coords.head->y][unstable_coords.head->x - 1] += unstable_coords.head->num;
      unstable_coords.Shift();
    }
    if (options.freq_of_saving > 0 && iter_to_save == options.freq_of_saving) {
      SaveImage(sp, options, num_of_images);
      ++num_of_images;
      iter_to_save = 0;
    }
    ++iter_to_save;
    ++iters;
//    for (int16_t i = 0; i < sp.size_y; ++i) {
//      for (int16_t j = 0; j < sp.size_x; ++j) {
//        std::cout << sp.matrix[i][j] << ' ';
//      }
//      std::cout << '\n';
//    }
//    std::cout << '\n';
  }
  if (options.freq_of_saving == 0) {
    SaveImage(sp, options, num_of_images);
  }
};
//        if (add_up) {
//          new_sp[0] = new uint64_t[sp.size_x];
//          for (int16_t i = 0; i < sp.size_x) {
//            new_sp[0][i] = 0;
//          }
//        }
//        if (add_left) {
//          new_sp[0] = new uint64_t[sp.size_x];
//          for (int16_t i = 0; i < sp.size_x) {
//            new_sp[0][i] = 0;
//          }
//        }
//        if (add_down) {
//          new_sp[0] = new uint64_t[sp.size_x];
//          for (int16_t i = 0; i < sp.size_x) {
//            new_sp[0][i] = 0;
//          }
//        }


//  int num;
//  bool is_stable;
//  for (int k = 0; k < iters_num; ++k) {
//    is_stable = true;
//    for (int i = 0; i < height; ++i) {
//      for (int j = 0; j < width; ++j) {
//        num = sandpiles[i][j];
//        if (num >= 4) {
//          is_stable = false;
//          nextpiles[i][j] -= 4;
//          if (i + 1 < height)
//            nextpiles[i + 1][j]++;
//          if (i - 1 >= 0)
//            nextpiles[i - 1][j]++;
//          if (j + 1 < width)
//            nextpiles[i][j + 1]++;
//          if (j - 1 >= 0)
//            nextpiles[i][j - 1]++;
//        }
//      }
//    }
//    if (is_stable) {
//      std::cout << "The pile is now stable!";
//      break;
//    }
//    std::cout << "State after " << k + 1 << "iteration: \n";
//    for (int i = 0; i < height; ++i) {
//      for (int j = 0; j < width; ++j) {
//        sandpiles[i][j] = nextpiles[i][j];
//        std::cout << sandpiles[i][j];
//        if (sandpiles[i][j] > 9) {
//          std::cout << " ";
//        } else {
//          std::cout << "  ";
//        }
//      }
//      std::cout << '\n';
//    }


//if (increase_x || increase_y) {
//uint64_t** sandpile_new = new uint64_t* [max_y - increase_y + 1];
//for (int16_t i = 0; i < max_y - increase_y + 1; ++i) {
//sandpile_new[i] = new uint64_t[max_x - increase_x + 1];
//for (int16_t j = 0; j < max_x - increase_x + 1; ++j) {
//sandpile_new[i][j] = sandpile[i][j];
//}
//delete[] sandpile[i];
//}
//delete[] sandpile;
//uint64_t** sandpile = new uint64_t* [max_y + 1];
//for (int16_t i = 0; i < max_y + 1; ++i) {
//sandpile[i] = new uint64_t[max_x + 1];
//for (int16_t j = 0; j < max_x + 1; ++j) {
//if (i == max_y && increase_y) {
//sandpile[i][j] = 0;
//} else {
//sandpile[i][j] = sandpile_new[i][j];
//}
//if (j == max_x && increase_x) {
//sandpile[i][j] = 0;
//} else {
//sandpile[i][j] = sandpile_new[i][j];
//}
//}
//delete[] sandpile_new[i];
//}
//delete[] sandpile_new;
//sandpile[y][x] += num;
//} else {
//sandpile[y][x] += num;
//}
