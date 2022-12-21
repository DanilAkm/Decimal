#include "../s21_decimal.h"

s21_decimal int_div(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  s21_decimal result_sub = {0};
  s21_decimal one = {{1}};
  s21_decimal temp_value_2 = value_2;
  if (s21_is_less(value_1, value_2)) {
    *result = result_sub;
    return result_sub;
  } else if (s21_is_equal(value_1, value_2)) {
    return one;
  }
  while (find_first_one_bit(value_1) > find_first_one_bit(temp_value_2)) {
    lshift(&temp_value_2);
    lshift(result);
  }
  if (s21_is_less(value_1, temp_value_2)) {
    rshift(&temp_value_2);
    rshift(result);
  }
  s21_sub(value_1, temp_value_2, &result_sub);
  one = int_div(result_sub, value_2, &one);
  s21_sum(*result, one, result); //  1000000 + 10000 + 1000 + 100 + 1 <---
  return *result;
}
