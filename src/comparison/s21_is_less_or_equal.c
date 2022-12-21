#include "../s21_decimal.h"

/**
 * @brief tells weather the first value is less or equal
 *
 * @param num1 first number
 * @param num2 second number
 * @return 0 - FALSE | 1 - TRUE
 */
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  return (s21_is_equal(num1, num2) || s21_is_less(num1, num2));
}
