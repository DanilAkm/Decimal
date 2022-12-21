#include "../s21_decimal.h"

/**
 * @brief converts an s21_decimal number to a floating point number
 *
 * @param src source value
 * @param dst destination address
 * @return 0 - OK | 1 - convertation error
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 0;
  if (dst == NULL) {
    result = 1;
  } else {
    double num = 0;
    int scale = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 32; j++) {
        int res = s21_get_bit(src, i * 32 + j);
        if (res == 1) {
          num += pow(2, i * 32 + j);
        }
      }
    }
    scale = s21_get_power(src);
    num /= (double)pow(10.0, (double)scale);
    if (s21_get_sign(src) == 1) {
      num *= -1;
    }
    *dst = (float)num;
  }
  return result;
}
