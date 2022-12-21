#include "../s21_decimal.h"

/**
 * @brief
 *
 * @param src source value
 * @param dst destination address
 * @return 0 - OK | 1 - convertation error
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL)
    return convertation_error;

  dec_to_zero(dst);
  if (src < 0) {
    src *= -1;
    s21_set_sign(dst, 1);
  }

  dst->bits[0] = src;
  return convertation_ok;
}