#include "../s21_decimal.h"

/**
 * @brief tells weather the values are equal
 *
 * @param num1 first number
 * @param num2 second number
 * @return 0 - FALSE | 1 - TRUE
 */
int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int res = FALSE;
  if (num1.bits[0] == num2.bits[0] && num1.bits[1] == num2.bits[1] &&
      num1.bits[2] == num2.bits[2] && num1.bits[3] == num2.bits[3]) {
    res = TRUE;
  }
  if (is_zero(num1) && is_zero(num2))
    res = TRUE;
  return res;
}
