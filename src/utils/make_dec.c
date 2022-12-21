#include "../s21_decimal.h"

s21_decimal make_dec(int a, int b, int c) {
  s21_decimal out_value;
  out_value.bits[0] = a;
  out_value.bits[1] = b;
  out_value.bits[2] = c;
  out_value.bits[3] = 0;
  return out_value;
}