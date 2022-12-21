#include "../s21_decimal.h"

int test_bit(unsigned int bits, int index) { return bits & (1U << index); }

int exp_float_bin2dec(unsigned int bits) {
  int exp_int = 0;
  int index = 30;
  int exp_2 = 7;
  while (index >= 23) {
    if (test_bit(bits, index)) {
      exp_int += pow(2, exp_2);
    }
    index--;
    exp_2--;
  }
  return exp_int - 127;
}

/**
 * @brief IEEE 754 float to decimal
 *
 * @param src source value
 * @param dst destination address
 * @return 0 - OK | 1 - convertation error
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL || src == INFINITY || src == -INFINITY || src < MIN_DEC ||
      src > MAX_DEC)
    return convertation_error;

  memset(&(dst->bits), 0, sizeof(dst->bits));

  // Проверяем знак

  if (src < 0)
    s21_set_sign(dst, 1);
  src = fabsf(src);

  // Получаем степень экспоненты из float с 30 до 23 бита
  unsigned int float_bits = *((unsigned int *)&src);
  int exp_value = exp_float_bin2dec(float_bits);

  // не входит в диапазон
  if (exp_value > 95)
    return convertation_error;

  // нормализуем флот
  int scale = 0;
  for (; !((unsigned int)src); src *= 10, scale++) {
  }

  // определяем количество знаков после точки, которые мы хотим сохранить

  src *= 10 * FLOAT_PRECISION;
  scale += FLOAT_PRECISION;

  float_bits = *((unsigned int *)&src);
  exp_value = exp_float_bin2dec(float_bits);

  // слишком большая степень в процессе вычислений
  if (exp_value < -94 || scale > 28)
    return calculation_error;

  s21_set_bit(dst, scale--, 1);

  dst->bits[0] = float_bits;

  for (int i = 31; i != 22; i--) {
    s21_set_bit(dst, i, 0);
  }
  s21_set_power(dst, scale);

  return convertation_ok;
}