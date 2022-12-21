#include "../s21_decimal.h"

void dec_to_zero(s21_decimal *number) {
  memset(number, 0, sizeof(s21_decimal));
}
