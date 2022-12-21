#include "../s21_decimal.h"

/**
 * @brief tells weather the first value is greater
 *
 * @param num1 first number
 * @param num2 second number
 * @return 0 - FALSE | 1 - TRUE
 */
int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int result = FALSE;

  int sign1 = s21_get_sign(num1);
  int sign2 = s21_get_sign(num2);

  if (is_zero(num1) && is_zero(num2)) {
    result = FALSE;
  } else if (sign1 && !sign2) {
    result = FALSE;
  } else if (!sign1 && sign2) {
    result = TRUE;
  } else if (sign1 && sign2) {
    s21_set_sign(&num1, 0);
    s21_set_sign(&num2, 0);
    s21_normalize(&num1, &num2);
    result = comparison_value_bits(num1, num2);
  } else {
    s21_normalize(&num1, &num2);
    result = !comparison_value_bits(num1, num2);
  }
  return result;
}

int comparison_value_bits(s21_decimal num1, s21_decimal num2) {
  int result = FALSE;

  for (int i = 95; i >= 0; i--) {
    int bit1 = s21_get_bit(num1, i);
    int bit2 = s21_get_bit(num2, i);
    if (!bit1 && bit2) {
      result = TRUE;
      break;
    }
    if (bit1 && !bit2) {
      result = FALSE;
      break;
    }
  }
  return result;
}

int is_zero(s21_decimal number) {
  int result =
      number.bits[0] == 0 && number.bits[1] == 0 && number.bits[2] == 0;
  return result;
}
