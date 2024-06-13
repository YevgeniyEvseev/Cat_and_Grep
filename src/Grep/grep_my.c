#include "grep_my.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 3) {
    printf(
        "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for "
        "more information.'\n'");
    return 1;
  }
}

void read_options(char *str, int argc, char *argv[], opt *options) {
  int c;

  while ((c = getopt_long(argc, argv, "e:sivclnhf:o", NULL, NULL)) != -1) {
    switch (c) {
      case 'e':
        options->e = 1;
        add_pattern(str, optarg);
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

void add_pattern(char *pattern, char *src) {
  if (strlen(pattern)) {
    strcat(pattern, "|");
  }
  strcat(pattern, src);
}
