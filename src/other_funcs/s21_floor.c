#include "../s21_decimal.h"

/**
 * @brief rounds the given number downwards
 *
 * @param value source value
 * @param result resutl destination
 * @return 0 - OK | 1 - calculation error
 */
int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL)
    return calculation_error;

  int sign = s21_get_sign(value);
  s21_decimal dec_after_trunc = make_dec(0, 0, 0);
  s21_decimal one = make_dec(1, 0, 0);
  s21_decimal fractional = {0};
  s21_mod(value, one, &fractional);
  s21_truncate(value, &dec_after_trunc);
  if (sign == 1 && !is_zero(fractional)) {
    s21_sub(dec_after_trunc, one, result);
  } else {
    *result = dec_after_trunc;
  }
  return calculation_ok;
}
