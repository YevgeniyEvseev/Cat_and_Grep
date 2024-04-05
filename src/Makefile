FLAGS = -Wall -Wextra -Werror

all: cat

cat: cat_my.c
	gcc $(FLAGS) cat_my.c -o ./test/s21_cat

test:
	sh ./test/test_func_cat.sh

clean: 
	rm -f ./test/s21_cat