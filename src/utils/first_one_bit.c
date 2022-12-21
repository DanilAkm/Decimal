#include "../s21_decimal.h"

int find_first_one_bit(s21_decimal src) {
  int position = -1;
  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit(src, i)) {
      position = i;
      break;
    }
  }
  return position;
}

// прибавлять единицу
