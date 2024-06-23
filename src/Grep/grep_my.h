#ifndef GREP_MY_H
#define GREP_MY_H

#define Nmax 1024

#include <regex.h>

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} opt;

struct C_string;

struct C_string *init_string();
void cstr(struct C_string *pattern, char *str);
void get_string(const struct C_string *pattern, char *str);
char *get_str(const struct C_string *pattern);
void add_string(struct C_string *pattern, char *str);
void add_string_int(struct C_string *pattern, int n);
int is_empty(const struct C_string *pattern);
int len_string(const struct C_string *pattern);
void erase_string(struct C_string *pattern);
void clear_string(struct C_string *pattern);

void read_options(struct C_string *pattern, int argc, char *argv[],
                  opt *options);
void read_file(char *argv, regex_t *reg, opt *option);

void add_to_pattern(struct C_string *pattern, char *str);
void print_result(char *str, char *name_file, int num_str, opt *option);

void error_grep(int reg_er, const regex_t *reg, int grep_er, char *src);
void option_f(struct C_string *str, char *argv);
void option_o(regex_t *reg, char *str, char *name_file, int num_str,
              regmatch_t *pm, opt *option);
// void preproc_regcomp(int argc, char **argv);

#endif