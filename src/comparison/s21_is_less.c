#include "../s21_decimal.h"

/**
 * @brief tells weather the first value is less
 *
 * @param num1 first number
 * @param num2 second number
 * @return 0 - FALSE | 1 - TRUE
 */
int s21_is_less(s21_decimal value1, s21_decimal value2) {
  int result = FALSE;

  int sign1 = s21_get_sign(value1);
  int sign2 = s21_get_sign(value2);

  if (is_zero(value1) && is_zero(value2)) {
    result = FALSE;
  } else if (sign1 && !sign2) {
    result = TRUE;
  } else if (!sign1 && sign2) {
    result = FALSE;
  } else if (sign1 && sign2) {
    s21_set_sign(&value1, 0);
    s21_set_sign(&value2, 0);
    result = s21_is_greater(value1, value2);
  } else {
    s21_normalize(&value1, &value2);
    result = comparison_value_bits(value1, value2);
  }
  return result;
}
