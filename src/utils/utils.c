#include "../s21_decimal.h"

int s21_get_bit(s21_decimal number, int position) {
  return (number.bits[position / 32] >> (position % 32)) & 1U;
}

// Устанавливает бит номер position в значение val
void s21_set_bit(s21_decimal *number, int position, int val) {
  int mask = 1U << (position % 32);
  if (val)
    number->bits[position / 32] |= mask;
  else
    number->bits[position / 32] &= ~mask;
}

int s21_get_sign(s21_decimal number) { return (number.bits[3] >> SIGN) & 1U; }

// Устанавливает желаемый знак у числа
// 0 означает положительный, 1 означает отрицательный знак
void s21_set_sign(s21_decimal *number, int sign) {
  int mask = 1U << SIGN;
  if (sign) {
    number->bits[3] |= mask;
  } else {
    number->bits[3] &= ~mask;
  }
}

// void s21_delete_sign(s21_decimal* number) {
//   int mask = ~(1U << SIGN);
//   number->bits[3] &= mask;
// }

int s21_get_power(s21_decimal number) {
  int power = 0;
  int result = 0;
  for (int i = 0; i < END_POWER - BEGIN_POWER; i++) {
    int temp = s21_get_bit(number, 96 + i + BEGIN_POWER);
    power = (1U << i) * temp;
    result += power;
  }
  return result;
}

void s21_delete_power(s21_decimal *number) {
  int sign = s21_get_sign(*number);
  number->bits[3] = 0;
  s21_set_sign(number, sign);
}

void s21_set_power(s21_decimal *number, int pow) {
  s21_delete_power(number);
  for (int i = BEGIN_POWER; i <= END_POWER && pow; i++) {
    if (pow % 2 == 1) {
      s21_set_bit(number, 96 + i, 1);
    }
    pow /= 2;
  }
}

int lshift(s21_decimal *number) {
  int is_over = s21_get_bit(*number, 95);
  number->bits[2] <<= 1U;
  if (s21_get_bit(*number, 63)) {
    s21_set_bit(number, 64, 1);
  }
  number->bits[1] <<= 1U;
  if (s21_get_bit(*number, 31)) {
    s21_set_bit(number, 32, 1);
  }
  number->bits[0] <<= 1U;
  return is_over;
}

void rshift(s21_decimal *number) {
  number->bits[0] >>= 1U;
  if (s21_get_bit(*number, 32)) {
    s21_set_bit(number, 31, 1);
  }
  number->bits[1] >>= 1U;
  if (s21_get_bit(*number, 64)) {
    s21_set_bit(number, 63, 1);
  }
  number->bits[2] >>= 1U;
}

int s21_comparison(s21_decimal value_1, s21_decimal value_2) {
  int result = EQUAL;
  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit(value_1, i) > s21_get_bit(value_2, i)) {
      result = VALUE1_GREATER;
      break;
    } else if (s21_get_bit(value_1, i) < s21_get_bit(value_2, i)) {
      result = VALUE2_GREATER;
      break;
    }
  }
  return result;
}

// void dec_to_zero(s21_decimal* number) {
//   memset(number, 0, sizeof(s21_decimal));
// }
