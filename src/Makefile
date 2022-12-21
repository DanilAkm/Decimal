CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
HEADER = s21_decimal.h
TESTS = s21_decimal
SOURCES_ALL:=$(wildcard *.c -I */*.c)
SOURCES_FUN:=$(shell find . -not -name "s21_decimal_test.c" -name "*.c" 2> /dev/null)
OBJECTS:=$(patsubst %.c,%.o,$(SOURCES_ALL))
OBJ_LIBRARY:=$(patsubst %.c,%.o,$(SOURCES_FUN))
UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lm -lrt -lpthread -lsubunit
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck
	OPEN_CM=open
endif

all: s21_decimal.a

check:
	@checkmk clean_mode=1 s21_decimal_test.check > s21_decimal_test.c

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

test: check $(OBJ_LIBRARY)
	@$(CC) $(CFLAGS) $(OBJ_LIBRARY) s21_decimal_test.c -o $(TESTS) $(LDFLAGS)
	@./$(TESTS)

s21_decimal.a: $(OBJ_LIBRARY) $(HEADER)
	@ar rcs s21_decimal.a $(OBJ_LIBRARY)
	@ranlib s21_decimal.a

gcov_report: check
	@$(CC) $(GCOVFLAGS) $(SOURCES_FUN) s21_decimal_test.c $(LDFLAGS) -o report.out
	@./report.out
	@-gcov -f $(SOURCES_FUN)
	@lcov -t "gcov_report" -o Coverage_Report.info -c -d ./
	@-lcov -r Coverage_Report.info '*/s21_decimal_test.c' -o Coverage_Report.info
	@genhtml -o ./report Coverage_Report.info
	@rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	@rm -rf */*.o
	@$(OPEN_CM) ./report/index-sort-f.html

rebuild: clean all

style:
	clang-format -n arithmetic/*.c comparison/*.c cast/*.c other_funcs/*.c utils/*.c *.h

correctoin_style:
	clang-format -i arithmetic/*.c comparison/*.c cast/*.c other_funcs/*.c utils/*.c *.h

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report
	rm -rf */*.o
	rm s21_decimal_test.c s21_decimal
