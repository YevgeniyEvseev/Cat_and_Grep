FLAGS = -Wall -Wextra -Werror

all: cat

grep: grep_my.c
	gcc -g grep_my.c pattern.c -o ./test/s21_grep

tests: test_func_cat.sh
	cd test && bash ./test_func_cat.sh

light_test:
	sh ./test_l/test.sh

clean: 
	rm -f ./test/s21_grep