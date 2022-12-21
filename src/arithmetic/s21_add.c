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
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_value = arth_ok;
  memset(result, 0, sizeof(s21_decimal));
  int is_over;

  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  sign_1 ? s21_set_sign(&value_1, 0) : 0;
  sign_2 ? s21_set_sign(&value_2, 0) : 0;
  int pow_1 = s21_get_power(value_1);
  int pow_2 = s21_get_power(value_2);
  s21_normalize(&value_1, &value_2);
  if (sign_1 && sign_2) {
    is_over = s21_sum(value_1, value_2, result);
    if (is_over) {
      return arth_small_number;
    }
    s21_set_sign(result, 1);
  } else if (!sign_1 && !sign_2) {
    is_over = s21_sum(value_1, value_2, result);
    if (is_over) {
      return arth_large_number;
    }
  } else if (!sign_1 && sign_2) {
    s21_sub(value_1, value_2, result);
    if (s21_comparison(value_1, value_2) == VALUE2_GREATER) {
      s21_set_sign(result, 1);
    }
  } else if (sign_1 && !sign_2) {
    s21_sub(value_1, value_2, result);
    if (s21_comparison(value_1, value_2) == VALUE1_GREATER) {
      s21_set_sign(result, 1);
    }
  }
  int max_pow = 0;
  if (pow_1 > pow_2) {
    max_pow = pow_1;
  } else {
    max_pow = pow_2;
  }
  s21_set_power(result, max_pow);

  return return_value;
}

int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_value = arth_ok;
  int temp = 0;
  s21_decimal temp_res = {0};
  for (int i = 0; i < 96; i++) {
    int value1_bit = s21_get_bit(value_1, i);
    int value2_bit = s21_get_bit(value_2, i);
    int compare = value1_bit || value2_bit;
    if (value1_bit && value2_bit) {
      if (temp) {
        s21_set_bit(&temp_res, i, 1);
      }
      temp = 1;
    }
    if (!temp && compare) {
      s21_set_bit(&temp_res, i, 1);
    } else if (temp && !compare) {
      s21_set_bit(&temp_res, i, 1);
      temp = 0;
    }
    if (i == 95 && temp == 1) {
      result_value = 1;
    }
  }
  s21_set_power(&temp_res, s21_get_power(*result));
  *result = temp_res;
  return result_value;
}
