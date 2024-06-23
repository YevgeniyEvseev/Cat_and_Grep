FLAGS = -Wall -Wextra -Werror

all: grep

grep: grep_my.c
	gcc $(FLAGS) grep_my.c pattern.c -o ./test/s21_grep

grep_gdb: grep_my.c
	gcc -g grep_my.c pattern.c -o ./grep_my

tests:
	cd test && bash ./test_func_grep.sh

clean: 
	rm -f ./test/s21_grep
	rm -f ./grep_my