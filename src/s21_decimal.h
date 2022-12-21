#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//  bits[0], bits[1], и bits[2] содержат младшие, средние и старшие 32 бита
//  96-разрядного целого числа соответственно. bits[3] содержит коэффициент
//  масштабирования и знак, и состоит из следующих частей:

//  Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю.
//  Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
//  указывает степень 10 для разделения целого числа. Биты с 24 по 30 не
//  используются и должны быть равны нулю. Бит 31 содержит знак; 0 означает
//  положительный, а 1 означает отрицательный.

//  Обратите внимание, что битовое представление различает отрицательные и
//  положительные нули. Эти значения могут считаться эквивалентными во всех
//  операциях.

//  0[00000000 00000000 00000000 00000000]
//  1[00000000 00000000 00000000 00000000]
//  2[00000000 00000000 00000000 00000000]
//  3[00000000 00000000 00000000 00000000]

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

enum convert_error_code { convertation_ok, convertation_error };

enum calculation_error_code { calculation_ok, calculation_error };

enum arithmetic_error_code {
  arth_ok,
  arth_large_number,
  arth_small_number,
  arth_div_zero
};

enum { EQUAL, VALUE1_GREATER, VALUE2_GREATER };

#define TRUE 1
#define FALSE 0

enum other_defs { BEGIN_POWER = 16, END_POWER = 23, SIGN = 31 };

#define S21_EPS 1e-6
#define S21_INF 1 / 0.0
#define MAX_POWER 28
#define MAX_INT 2147483647
#define MIN_INT 2147483648U

#define S21_EPS 1e-6
#define S21_INF 1 / 0.0
#define MAX_POWER 28
#define MAX_INT 2147483647
#define MIN_INT 2147483648U
#define MAX_DEC 79228162514264337593543950335.0F
#define MIN_DEC -79228162514264337593543950335.0F
#define FLOAT_PRECISION 7

int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // boy
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // hank
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // vmeste
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // boomer
int s21_mod(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // boomer

//  Функции возвращают код ошибки:

//  0 - OK
//  1 - число слишком велико или равно бесконечности
//  2 - число слишком мало или равно отрицательной бесконечности
//  3 - деление на 0

//  Уточнение про числа, не вмещающиеся в мантиссу:

//  При получении чисел, не вмещающихся в мантиссу при арифметических операциях,
//  использовать банковское округление (например,
//  79,228,162,514,264,337,593,543,950,335 - 0.6 =
//  79,228,162,514,264,337,593,543,950,334)

//  Уточнение про операцию mod:

//  Если в результате операции произошло переполнение, то необходимо отбросить
//  дробную часть (например, 70,000,000,000,000,000,000,000,000,000 % 0.001 =
//  0.000)

int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2); // boomer
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2); // DONE TIPA

//  Return value:
//  0 - FALSE
//  1 - TRUE

int s21_from_int_to_decimal(int src, s21_decimal *dst);     // hank
int s21_from_float_to_decimal(float src, s21_decimal *dst); // dushnila boomer
int s21_from_decimal_to_int(s21_decimal src, int *dst);     // shettron
int s21_from_decimal_to_float(s21_decimal src, float *dst); // boy

//  Возвращаемое значение - код ошибки:

//  0 - OK
//  1 - ошибка конвертации

//  Уточнение про преобразование числа типа float:

//  Если числа слишком малы (0 < |x| < 1e-28), вернуть ошибку и значение, равное
//  0 Если числа слишком велики (|x| > 79,228,162,514,264,337,593,543,950,335)
//  или равны бесконечности, вернуть ошибку При обработке числа с типом float
//  преобразовывать все содержащиеся в нём значимые десятичные цифры. Если таких
//  цифр больше 7, то значение числа округляется к ближайшему, у которого не
//  больше 7 значимых цифр.

//  Уточнение про преобразование из числа типа decimal в тип int:

//  Если в числе типа decimal есть дробная часть, то её следует отбросить
//  (например, 0.9 преобразуется 0)

int s21_floor(s21_decimal value, s21_decimal *result); // boomer
// 10.23 = 10
// -12.23 = -13

int s21_round(s21_decimal value, s21_decimal *result);    // boy
int s21_truncate(s21_decimal value, s21_decimal *result); // shettron
// 10.23 = 10
// -12.23 = -12
int s21_negate(s21_decimal value, s21_decimal *result); // hank

//  Return value - code error:

//  0 - OK
//  1 - calculation error

//  UTILS
int s21_get_bit(s21_decimal number, int position);
void s21_set_bit(s21_decimal *number, int position, int val);
int s21_get_sign(s21_decimal number);
void s21_set_sign(s21_decimal *number, int sign);
void s21_delete_sign(s21_decimal *number);
int s21_get_power(s21_decimal number);
void s21_set_power(s21_decimal *number, int pow);
void s21_delete_power(s21_decimal *number);
int lshift(s21_decimal *number);
void rshift(s21_decimal *number);
int s21_div_ten(s21_decimal value);
void dec_to_zero(s21_decimal *number);
int loop_multiple(s21_decimal *src, s21_decimal multiplicand, size_t times);
int s21_normalize(s21_decimal *a, s21_decimal *b);
s21_decimal make_dec(int a, int b, int c);
unsigned int s21_get_bin_exp(unsigned int src);
void dec_to_dec(s21_decimal source, s21_decimal *dest);
s21_decimal int_div(s21_decimal divident, s21_decimal divider,
                    s21_decimal *result);
int find_first_one_bit(s21_decimal src);
s21_decimal s21_bank_rounding(s21_decimal value);
s21_decimal s21_base_bank_round(s21_decimal last_decimal, s21_decimal pre_digit,
                                s21_decimal result);
s21_decimal s21_get_pre_digit(s21_decimal value);
int s21_comparison(s21_decimal value_1, s21_decimal value_2);
int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_multiply(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int count_shift(s21_decimal *value, int count);
void s21_sub_util(s21_decimal max, s21_decimal min, s21_decimal *result);
int comparison_value_bits(s21_decimal value1, s21_decimal value2);
int is_zero(s21_decimal number);
s21_decimal s21_binary_mod(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_add_code(s21_decimal value);
s21_decimal s21_inversion(s21_decimal number);

/*
  Новые утилсы пуште отдельным файлом
*/

//  Необходимо реализовать описанные выше функции библиотеки:

//  Библиотека должна быть разработана на языке Си стандарта C11 с
//  использованием компиятора gcc Код библиотеки должен находиться в папке src в
//  ветке develop Не использовать устаревшие и выведенные из употребления
//  конструкции языка и библиотечные функции. Обращать внимания на пометки
//  legacy и obsolete в официальной документации по языку и используемым
//  библиотекам. Ориентироваться на стандарт POSIX.1-2017 При написании кода
//  необходимо придерживаться Google Style Оформить решение как статическую
//  библиотеку (с заголовочным файлом s21_decimal.h) Библиотека должна быть
//  разработана в соответствии с принципами структурного программирования Перед
//  каждой функцией использовать префикс s21_ Подготовить полное покрытие
//  unit-тестами функций библиотеки c помощью библиотеки Check Unit-тесты должны
//  покрывать не менее 80% каждой функции Предусмотреть Makefile для сборки
//  библиотеки и тестов (с целями all, clean, test, s21_decimal.a, gcov_report)
//  В цели gcov_report должен формироваться отчёт gcov в виде html страницы. Для
//  этого unit-тесты должны запускаться с флагами gcov При реализации decimal
//  ориентироваться на двоичное представление с целочисленным массивом bits, как
//  указано в примере выше. Соблюсти положение разрядов числа в массиве bits

//  Запрещено использование типа __int128
//  Конечные нули можно как оставлять, так и удалять (за исключением функции
//  s21_truncate) Определяемый тип должен поддерживать числа от
//  -79,228,162,514,264,337,593,543,950,335 до
//  +79,228,162,514,264,337,593,543,950,335.

#endif //  SRC_S21_DECIMAL_H_
