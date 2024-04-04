#ifndef CAT_MY_H
#define CAT_MY_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct options {
  int b;
  int s;
  int n;
  int e;
  int t;
  int v;
} opt;

void read_option(int argc, char **argv, opt *option);
int read_name_file(FILE *file);

#endif