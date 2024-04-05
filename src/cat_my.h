#ifndef CAT_MY_H
#define CAT_MY_H

#define TRUE 1
#define FALSE 0

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
FILE *read_file(char *name_file);
void processing_file(FILE *file, const opt *options);

#endif