FLAGS = -Wall -Wextra -Werror

all: cat

cat: grep_my.c
	gcc  grep_my.c -o ./test/grep_my

test:
	sh ./test/test_func_cat.sh

clean: 
	rm -f ./test/s21_cat