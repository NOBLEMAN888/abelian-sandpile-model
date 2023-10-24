#include "sandpile_processing.h"

#include <iostream>
void SandPile() {
  int height = 10, width = 10;
  int start_num = 20;
  int iters_num = 10;
  int sandpiles[height][width];
  int nextpiles[height][width];

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      sandpiles[i][j] = 0;
      nextpiles[i][j] = 0;
    }
  }
  sandpiles[height / 2][width / 2] = start_num;
  nextpiles[height / 2][width / 2] = start_num;

  std::cout << "Start state: \n";
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      std::cout << sandpiles[i][j];
      if (sandpiles[i][j] > 9) {
        std::cout << " ";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << '\n';
  }
  int num;
  bool is_stable;
  for (int k = 0; k < iters_num; ++k) {
    is_stable = true;
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        num = sandpiles[i][j];
        if (num >= 4) {
          is_stable = false;
          nextpiles[i][j] -= 4;
          if (i + 1 < height)
            nextpiles[i + 1][j]++;
          if (i - 1 >= 0)
            nextpiles[i - 1][j]++;
          if (j + 1 < width)
            nextpiles[i][j + 1]++;
          if (j - 1 >= 0)
            nextpiles[i][j - 1]++;
        }
      }
    }
    if (is_stable) {
      std::cout << "The pile is now stable!";
      break;
    }
    std::cout << "State after " << k + 1 << "iteration: \n";
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        sandpiles[i][j] = nextpiles[i][j];
        std::cout << sandpiles[i][j];
        if (sandpiles[i][j] > 9) {
          std::cout << " ";
        } else {
          std::cout << "  ";
        }
      }
      std::cout << '\n';
    }
  }
}