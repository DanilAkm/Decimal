#include "../s21_decimal.h"

/**
 * @brief cuts the fractional part of a given number
 *
 * @param value source value
 * @param result resutl destination
 * @return 0 - OK | 1 - calculation error
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL)
    return calculation_error;
  s21_decimal ten = {{10}};
  int power = s21_get_power(value);
  int sign = s21_get_sign(value);
  s21_set_sign(&value, 0);
  s21_set_power(&value, 0);
  if (power) {
    while (power) {
      memset(result, 0, sizeof(s21_decimal));
      result->bits[0] = 1;
      int_div(value, ten, result);
      value = *result;
      power--;
    }
  } else {
    *result = value;
  }
  if (sign) {
    s21_set_sign(result, 1);
  }
  return calculation_ok;
}
