#include "grep_my.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  opt option = {0};
  FILE *file;
  regex_t reg;
  regmatch_t pm[10];

  if (argc < 3) return 1;
  struct C_string *pattern = init_string();
  struct C_string *buffer = init_string();
  cstr(buffer, "");
  cstr(pattern, "");
  read_options(pattern, argc, argv, &option);
  if (option.e == 0 && option.f == 0) add_to_pattern(pattern, argv[optind++]);
  int cflags = REG_NEWLINE | REG_EXTENDED;
  if (option.i == 1) {
    cflags = REG_NEWLINE | REG_EXTENDED | REG_ICASE;
  }
  char *str = get_str(pattern);
  int z = regcomp(&reg, str, cflags);
  if (z != 0) {
    error_grep(z, &reg, -1, str);
    return 1;
  }
  for (; optind < argc; optind++) {
    int count_str_in_file = 0, num_str = 0;
    file = fopen(argv[optind], "r");
    if (file == NULL) {
      if (!option.s) {
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
        continue;
      }
    }
    char str_tmp[1024] = {0};
    while (fgets(str_tmp, 1024, file) != NULL) {
      add_to_pattern(buffer, str_tmp);
      if (!(str_tmp[1023] == '\0' || str_tmp[1023] == '\n')) {
        continue;
      }
      num_str++;
      char *str_in_file = get_str(buffer);
      z = regexec(&reg, str_in_file, 10, pm, 0);
      if (z == 0 || (z = REG_NOMATCH && option.v)) {
        if (option.o) {
          option_o(&reg, str_in_file, argv[optind], num_str, pm, &option);
        }
        count_str_in_file++;
        if (option.c == 0 && option.l == 0 && option.o == 0)
          print_result(str_in_file, argv[optind], num_str, &option);
      } else {
        // error_grep(z, &reg, -1, str_in_file);
      }
      clear_string(buffer);
    }
    if (option.c == 1 || option.l == 1)
      print_result("", argv[optind], count_str_in_file, &option);
    fclose(file);
  }
  regfree(&reg);
  erase_string(pattern);
  erase_string(buffer);
}

void read_options(struct C_string *str, int argc, char *argv[], opt *options) {
  int c;

  while ((c = getopt_long(argc, argv, "e:sivclnhf:o", NULL, NULL)) != -1) {
    switch (c) {
      case 'e':
        options->e = 1;
        add_to_pattern(str, optarg);
        break;

      case 'i':
        options->i = 1;
        break;

      case 'v':
        options->v = 1;
        break;

      case 'c':
        options->c = 1;
        break;

      case 'l':
        options->l = 1;
        break;

      case 'n':
        options->n = 1;
        break;

      case 'h':
        options->h = 1;
        break;

      case 's':
        options->s = 1;
        break;

      case 'f':
        options->f = 1;
        option_f(str, optarg);
        break;

      case 'o':
        options->o = 1;
        break;

      default:
        break;
    }
  }
  if (options->l == 1) {
    options->c = 0;
    options->n = 0;
    options->o = 0;
    options->h = 0;
  }
  if (options->c) {
    options->n = 0;
  }
}

void add_to_pattern(struct C_string *pattern, char *str) {
  if (len_string(pattern)) {
    add_string(pattern, "|");
  }
  add_string(pattern, str);
}

// void get_data_from_regcomp(const int optind, regex_t *reg, opt *option) {}

void print_result(char *str, char *name_file, int num_str, opt *option) {
  struct C_string *output = init_string();
  cstr(output, "");
  if (option->h == 0) {
    add_string(output, name_file);
    add_string(output, ":");
  }
  if (option->l) {
    if (num_str) {
      add_string(output, "\n");
      printf("%s", get_str(output));
      erase_string(output);
    }
    return;
  }
  if (option->n) {
    add_string_int(output, num_str);
    add_string(output, ":");
  }
  if (option->c == 1) {
    add_string_int(output, num_str);
    add_string(output, "\n");
  } else {
    add_string(output, str);
  }
  printf("%s", get_str(output));
  erase_string(output);
}

void error_grep(int reg_er, const regex_t *reg, int grep_er, char *src) {
  if (grep_er == -1) {
    char error_buf[1024] = {0};
    regerror(reg_er, reg, error_buf, sizeof(error_buf));
    fprintf(stderr, "%s: pattern '%s' \n", error_buf, src);
  } else {
  }
}

void option_f(struct C_string *str, char *argv) {
  char tmp_str[Nmax] = {0};
  FILE *f_patern = fopen(argv, "r");
  if (f_patern == NULL) {
    printf("grep: %s: Not such file or directory\n", argv);
  }
  while (fgets(tmp_str, Nmax, f_patern) != NULL) {
    add_to_pattern(str, tmp_str);
  }
  fclose(f_patern);
}

void option_o(regex_t *reg, char *str, char *name_file, int num_str,
              regmatch_t *pm, opt *option) {
  char str_match[Nmax] = {0};
  do {
    int len = pm->rm_eo - pm->rm_so;
    strncpy(str_match, str + pm->rm_so, len);
    str_match[len] = '\n';

    print_result(str_match, name_file, num_str, option);
    str += pm->rm_eo;
  } while (regexec(reg, str, 1, pm, 0) == 0);
}