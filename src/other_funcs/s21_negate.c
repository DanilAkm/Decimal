#include "../s21_decimal.h"

/**
 * @brief same as multiplying by -1
 *
 * @param value source value
 * @param result resutl destination
 * @return 0 - OK | 1 - calculation error
 */
int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL)
    return calculation_error;
  int sign;
  if (!result)
    return 1;
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  result->bits[3] = value.bits[3];
  sign = s21_get_sign(value);
  s21_set_sign(result, !sign);
  return calculation_ok;
}
