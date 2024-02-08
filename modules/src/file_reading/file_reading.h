#ifndef LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_FILE_READING_FILE_READING_H_

#define LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_FILE_READING_FILE_READING_H_

#include "../arguments_parsing/arguments_parsing.h"

#include <fstream>
#include <iostream>

struct Node {
  int16_t x = 1;
  int16_t y = 1;
  uint64_t num = 0;
  Node* next;
  Node(int16_t a, int16_t b, uint64_t c){
    x = a;
    y = b;
    num = c;
    next = nullptr;
  }
  ~Node() {
    next = nullptr;
  }
};

struct CoordsList {
  Node* head;
  Node* tail;
  CoordsList() {
    head = nullptr;
    tail = nullptr;
  }
  ~CoordsList() {
    while (!IsEmpty()) {
      Shift();
    }
  }

  void PushBack(int16_t a, int16_t b, uint64_t c) {
    Node* new_node = new Node(a, b, c);
    if (IsEmpty()) {
      head = new_node;
      tail = head;
      return;
    }
    tail->next = new_node;
    tail = new_node;
  }

  void Shift() {
    if (IsEmpty()) {
      return;
    }
    Node* tmp = head;
    if (head == tail) {
      tail = nullptr;
      head = nullptr;
    } else {
      head = head->next;
    }
    delete tmp;
  }
  bool IsEmpty() {
    return head == nullptr;
  }
};

struct SandPileParameters {
  int16_t size_x = 1;
  int16_t size_y = 1;
  int16_t from_x = 0;
  int16_t to_x = 2;
  int16_t from_y = 0;
  int16_t to_y = 2;
  uint64_t** matrix;
};

void LogErrorFileNotOpened(); // If argument is invalid, logs the error and exits program

bool IsDigit(char chr);

int16_t GetDigitFromChar(char chr);

SandPileParameters GetMatrixFromFile(OptionsList options);

#endif //LAB3_LABWORK3_NOBLEMAN888_LABWORK3_NOBLEMAN888_MODULES_FILE_READING_FILE_READING_H_
