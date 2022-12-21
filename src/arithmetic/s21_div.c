#include "../s21_decimal.h"

/**
 * @brief sum of two numbers
 *
 * @param value_1 first summand
 * @param value_2 second summand
 * @param result result address
 * @return 0 - OK | 1 - the number is too large or equal to infinity | 2 - the
 * number is too small or equal to negative infinity | 3 - division by 0
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  dec_to_zero(result);
  s21_decimal one = {{1, 0, 0, 0}}, zero = {{0, 0, 0, 0}}, tmp = {{1, 0, 0, 0}};
  s21_decimal remainder = {{0, 0, 0, 0}};
  int sign = (s21_get_sign(value_1) ^ s21_get_sign(value_2));
  int pow_1 = s21_get_power(value_1), pow_2 = s21_get_power(value_2);
  // s21_set_power(&value_1, 0);
  // s21_set_power(&value_2, 0);
  if (s21_is_equal(value_2, zero))
    return arth_div_zero;
  if (s21_is_equal(value_1, value_2)) {
    *result = one;
  } else if (s21_is_equal(value_2, one)) {
    *result = value_1;
  } else {
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    s21_mod(value_1, value_2, &remainder);
    while (s21_is_greater_or_equal(value_1, value_2)) {
      lshift(&value_2);
      lshift(&tmp);
    }
    while (s21_is_greater(tmp, one)) {
      rshift(&value_2);
      rshift(&tmp);

      if (s21_is_greater_or_equal(value_1, value_2)) {
        s21_sub(value_1, value_2, &value_1);
        s21_add(tmp, *result, result);
      }
    }
    s21_set_sign(result, sign);
    s21_set_power(result, pow_1 + pow_2);
  }
  return arth_ok;
}
