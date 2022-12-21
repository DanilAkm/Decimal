#include "../s21_decimal.h"

s21_decimal s21_get_pre_digit(s21_decimal value) {
  s21_decimal ten = {{10}};
  s21_decimal div_result = {{1}};
  s21_decimal pre_digit = {0};
  int_div(value, ten, &div_result);
  s21_mod(div_result, ten, &pre_digit);
  return pre_digit;
}

s21_decimal s21_base_bank_round(s21_decimal last_decimal, s21_decimal pre_digit,
                                s21_decimal result) {
  s21_decimal two = {{2}};
  s21_decimal five = {{5}};
  s21_decimal is_even = {0};
  s21_decimal zero = {0};
  s21_decimal one = {{1}};
  if (s21_is_equal(last_decimal, five)) {
    s21_mod(pre_digit, two, &is_even);
    if (s21_is_not_equal(zero, is_even)) {
      s21_sum(result, one, &result);
    }
  } else if (s21_is_less(five, last_decimal)) {
    s21_sum(result, one, &result);
  }
  return result;
}

s21_decimal s21_bank_rounding(s21_decimal value) {
  s21_decimal ten = {{10}};
  s21_decimal last_decimal = {0};
  s21_decimal result = {{1}};

  s21_mod(value, ten, &last_decimal);
  s21_decimal pre_digit = s21_get_pre_digit(value);
  int_div(value, ten, &result);

  return s21_base_bank_round(last_decimal, pre_digit, result);
}

int s21_normalize(s21_decimal *a, s21_decimal *b) {
  int check_over = arth_ok;
  int power_1 = s21_get_power(*a);
  int power_2 = s21_get_power(*b);
  s21_set_power(a, 0);
  s21_set_power(b, 0);

  int biggest_power = power_1 > power_2 ? power_1 : power_2;
  int min_power = power_1 < power_2 ? power_1 : power_2;
  s21_decimal num_normalize = power_1 < power_2 ? *a : *b;
  s21_decimal small = power_1 < power_2 ? *b : *a;
  s21_decimal result = {0};
  s21_decimal ten = {{10}};

  while (min_power != biggest_power) {
    check_over = s21_multiply(num_normalize, ten, &result);
    if (check_over) {
      break;
    }
    min_power++;
    num_normalize = result;
    memset(&result, 0, sizeof(s21_decimal));
  }
  if (check_over) {
    while (min_power < biggest_power) {
      small = s21_bank_rounding(small);
      min_power++;
    }
  }
  if (power_1 < power_2) {
    *a = num_normalize;
    *b = small;
  } else {
    *b = num_normalize;
    *a = small;
  }
  s21_set_power(a, biggest_power);
  s21_set_power(b, biggest_power);
  return check_over;
}
