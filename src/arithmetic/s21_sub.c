#include "../s21_decimal.h"

// Вычитание

/**
 * @brief substraction of two numbers
 *
 * @param value_1 first summand
 * @param value_2 second summand
 * @param result result address
 * @return 0 - OK | 1 - the number is too large or equal to infinity | 2 - the
 * number is too small or equal to negative infinity | 3 - division by 0
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign1 = s21_get_sign(value_1), sign2 = s21_get_sign(value_2);
  int res = 0, res_sign;
  s21_decimal max_num = {0}, min_num = {0};
  if (!result)
    return calculation_error;
  dec_to_zero(result);
  if (sign1 + sign2 == 1) {
    s21_set_sign(&value_2, 0);
    s21_set_sign(&value_1, 0);
    res = s21_add(value_1, value_2, result);
    s21_set_sign(result, sign1);
  } else {
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    if (s21_is_equal(value_1, value_2))
      return arth_ok;
    if (s21_is_equal(value_1, value_2))
      return arth_ok;
    s21_normalize(&value_1, &value_2);
    if (s21_is_greater(value_1, value_2)) {
      max_num = value_1;
      min_num = value_2;
      res_sign = sign1;
    } else {
      max_num = value_2;
      min_num = value_1;
      res_sign = 1;
    }
    s21_sub_util(max_num, min_num, result);
    result->bits[3] = max_num.bits[3];
    s21_set_sign(result, res_sign);
  }
  if (res)
    ++res;
  return res;
}
