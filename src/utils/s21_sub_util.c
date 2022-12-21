// #include <stdio.h>

#include "../s21_decimal.h"
// Вычитание чисел без учета знаков и степени
void s21_sub_util(s21_decimal max, s21_decimal min, s21_decimal *result) {
  int bit1 = 0, bit2 = 0, j = 0;
  for (int i = 0; i < 95; ++i) {
    bit1 = s21_get_bit(max, i);
    bit2 = s21_get_bit(min, i);
    s21_set_bit(result, i, bit1 ^ bit2);
    if (!bit1 && bit2) {
      j = i + 1;
      while (!s21_get_bit(max, j)) {
        s21_set_bit(&max, j, 1);
        ++j;
      }
      s21_set_bit(&max, j, 0);
    }
  }
}
