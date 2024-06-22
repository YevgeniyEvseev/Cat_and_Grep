FLAGS = -Wall -Wextra -Werror

all: cat

cat: grep_my.c
	gcc -g grep_my.c pattern.c -o ./test/s21_grep

test:
	sh ./test/test_func_cat.sh

light_test:
	sh ./test_l/test.sh

clean: 
	rm -f ./test/s21_cat