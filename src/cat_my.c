#include "cat_my.h"

int main(int argc, char *argv[]) {}

void read_options(int argc, char *argv[], opt *options) {
  int c;

  static struct option long_option[] = {{"number-nonblank", 0, 0, 'b'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {"number", 0, 0, 'n'},
                                        {0, 0, 0, 0}};

  while ((c = getopt_long(argc, argv, "+bsneEtTv", long_option, NULL)) != -1) {
    switch (c) {
      case 'v':
        options->v = 1;
        break;

      case 'b':
        options->b = 1;
        break;

      case 's':
        options->s = 1;
        break;

      case 'n':
        options->n = 1;
        break;

      case 'e':
        // options->t = 1;
        options->e = 1;
        options->v = 1;
        break;

      case 'E':
        options->e = 1;
        break;

      case 't':
        options->t = 1;
        options->v = 1;
        break;

      case 'T':
        options->t = 1;
        break;

      default:
        break;
    }
  }
  if (options->b == 1 && options->n == 1) {
    options->n = 0;
  }
}