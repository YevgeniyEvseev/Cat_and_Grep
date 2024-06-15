FLAGS = -Wall -Wextra -Werror

all: cat

cat: grep_my.c
	gcc -g grep_my.c pattern.c -o grep_my

test:
	sh ./test/test_func_cat.sh

clean: 
	rm -f ./test/s21_cat