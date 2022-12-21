#include "../s21_decimal.h"

/**
 * @brief mathematical rounding of a given number
 *
 * @param value source value
 * @param result resutl destination
 * @return 0 - OK | 1 - calculation error
 */
int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return convertation_error;
  }
  memset(result, 0, sizeof(s21_decimal));
  s21_decimal five = {{5}};
  s21_decimal one = {{1}};
  s21_decimal mod_result = {0};
  int sign = s21_get_sign(value);
  s21_set_sign(&value, 0);
  s21_set_power(&five, 1);
  s21_truncate(value, result);
  s21_mod(value, one, &mod_result);
  if (!s21_is_less(mod_result, five)) {
    s21_sum(*result, one, result);
  }
  if (sign) {
    s21_set_sign(result, 1);
  }
  return convertation_ok;
}