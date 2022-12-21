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
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_value = arth_ok;
  memset(result, 0, sizeof(s21_decimal));

  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  int need_sign = (!sign_1 && sign_2) || (sign_1 && !sign_2);
  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);
  int pow1 = s21_get_power(value_1);
  int pow2 = s21_get_power(value_2);
  s21_set_power(&value_1, 0);
  s21_set_power(&value_2, 0);
  s21_decimal temp_result = {0};

  int is_over = s21_multiply(value_1, value_2, &temp_result);
  int count = 0;

  if (is_over && (pow1 + pow2) > 0) {
    s21_decimal ten = {{10}};
    while (is_over && count < (pow1 + pow2)) {
      s21_decimal div_res = {{1}};
      s21_decimal delim = count % 2 ? value_2 : value_1;
      int_div(delim, ten, &div_res);
      if (count % 2) {
        value_2 = div_res;
      } else {
        value_1 = div_res;
      }
      is_over = s21_multiply(value_1, value_2, &temp_result);
      count++;
    }
  }
  if (is_over && need_sign) {
    return arth_small_number;
  } else if (is_over && !need_sign) {
    return arth_large_number;
  }
  *result = temp_result;
  s21_set_power(result, pow1 + pow2 - count);
  if (need_sign) {
    s21_set_sign(result, 1);
  }
  return result_value;
}

int count_shift(s21_decimal *value, int count) {
  int is_over = 0;
  for (int i = 0; i < count; i++) {
    is_over = lshift(value);
    if (is_over) {
      break;
    }
  }
  return is_over;
}

int s21_multiply(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int is_over = arth_ok;
  int sum_over = arth_ok;
  s21_decimal temp = {0};
  s21_decimal result_tmp = {0};
  s21_decimal zero = {0};
  int count = 0;
  while (s21_is_not_equal(value_2, zero)) {
    memset(&temp, 0, sizeof(s21_decimal));
    int bit_2 = s21_get_bit(value_2, 0);
    for (int i = 0; i < 96; i++) {
      int bit_1 = s21_get_bit(value_1, i);
      if (bit_1 && bit_2) {
        s21_set_bit(&temp, i, 1);
      }
    }
    is_over = count_shift(&temp, count);
    sum_over = s21_sum(result_tmp, temp, &result_tmp);
    rshift(&value_2);
    if (is_over || sum_over) {
      break;
    }
    count++;
  }
  if (!is_over && !sum_over) {
    *result = result_tmp;
  }
  return is_over || sum_over;
}