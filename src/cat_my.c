#include "cat_my.h"

int main(int argc, char *argv[]) {
  FILE *file;
  opt options = {0};
  read_option(argc, argv, &options);
  for (; optind < argc; optind++) {
    file = read_file(argv[optind]);
    if (file != NULL) {
      processing_file(file, &options);
      fclose(file);
    }
  }
}

int squeeze_str(const opt *options, int *flag_squeez) {
  if (options->s && *flag_squeez == 1) return TRUE;
  *flag_squeez = 1;
  return FALSE;
}

void print_num_str(int num_str) {
  int count = 5;
  int tmp = num_str;
  while ((tmp /= 10) > 0) {
    count--;
  }
  for (int i = 0; i < count; i++) {
    printf(" ");
  }

  printf("%d\t", num_str);
}

void print_dollar() { printf("$"); }

int print_non_visible(int c) {
  if ((c >= 0 && c < 9) || (c >= 11 && c <= 31)) {
    putc('^', stdout);
    int n = (int)c + 64;
    putc(n, stdout);
    return TRUE;
  }

  if ((int)c == 127) {
    putc('^', stdout);
    putc('?', stdout);
    return TRUE;
  }
  return FALSE;
}

int print_tab() {
  putc('^', stdout);
  putc('I', stdout);
  return TRUE;
}

void print_cat(int c, const opt *options, int count_in_str, int *num_countr_str,
               int *flag_squeez) {
  int flag_v = 0;
  if (c == '\n' && count_in_str == 0) {
    if (squeeze_str(options, flag_squeez)) return;
  } else {
    *flag_squeez = 0;
  }
  if (options->n && count_in_str == 0) print_num_str((*num_countr_str)++);
  if (options->b && count_in_str == 0 && c != '\n')
    print_num_str((*num_countr_str)++);
  if (options->e && c == '\n') print_dollar();
  if (options->v) flag_v = print_non_visible(c);
  if (options->t && c == '\t') flag_v = print_tab();
  if (flag_v == 0) putc(c, stdout);
}

void processing_file(FILE *file, const opt *options) {
  char c;
  int count_in_str = 0, num_countr_str = 1, flag_squeez = 0;
  while ((c = fgetc(file)) != EOF) {
    print_cat(c, options, count_in_str, &num_countr_str, &flag_squeez);
    count_in_str++;
    if (c == '\n') count_in_str = 0;
  }
}

FILE *read_file(char *name_file) {
  FILE *files;
  if ((files = fopen(name_file, "r")) == NULL) {
    printf("cat: %s: No such file or directory\n", name_file);
  }
  return files;
}

void read_option(int argc, char *argv[], opt *options) {
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