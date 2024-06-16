#include "grep_my.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  opt option = {0};
  FILE *file;
  regex_t reg;
  regmatch_t pm[10];
  if (argc < 3) {
    printf(
        "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for "
        "more information.'\n'");
    return 1;
  }
  struct str_pattern *pattern = init_pattern();
  struct str_pattern *buffer = init_pattern();
  read_options(pattern, argc, argv, &option);
  if (option.e == 0 && option.f == 0) add_to_pattern(pattern, argv[optind++]);
  int cflags = REG_NEWLINE | REG_EXTENDED;
  if (option.i == 1) {
    cflags = REG_NEWLINE | REG_EXTENDED | REG_ICASE;
  }
  char *str = malloc((len_pattern(pattern) + 1) * sizeof(char));
  get_pattern(pattern, str);
  int z = regcomp(&reg, str, cflags);
  if (z != 0) {
    char error_buf[1024] = {0};
    regerror(z, &reg, error_buf, sizeof(error_buf));
    fprintf(stderr, "%s: pattern '%s' \n", error_buf, str);
    return 1;
  }
  free(str);
  for (; optind < argc; optind++) {
    file = fopen(argv[optind], 'r');
    if (file == NULL) {
      printf("grep: dddd: No such file or directory\n");
    }
    char *str_tmp[1024] = {0};
    cstr(buffer, str_tmp);
    while (fgets(str_tmp, 1024, file) == NULL) {
      add_to_pattern(buffer, str_tmp);
      if (str_tmp[1023] != '\0' || str_tmp[1023] != '\n') {
        continue;
      }
      // int z = regexec(&reg, buffer, 10, pm, 0);
      // print_result()
      clear_pattern(buffer);
    }
  }

  printf("%s", str);
  erase_pattern(pattern);
  erase_pattern(buffer);
}

void read_options(struct str_pattern *str, int argc, char *argv[],
                  opt *options) {
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
        //     option_f(optarg, str, count);
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
  }
}

void add_to_pattern(struct str_pattern *pattern, char *str) {
  if (len_pattern(pattern)) {
    add_pattern(pattern, "|");
  }
  add_pattern(pattern, str);
}

void get_data_from_regcomp(const int optind, regex_t *reg, opt *option) {}