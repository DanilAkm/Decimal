#include "../s21_decimal.h"

/**
 * @brief tells weather the first value is greater or equal
 *
 * @param num1 first number
 * @param num2 second number
 * @return 0 - FALSE | 1 - TRUE
 */
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  return (s21_is_equal(num1, num2) || s21_is_greater(num1, num2));
}
