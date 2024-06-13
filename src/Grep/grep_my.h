#ifndef GREP_MY_H
#define GREP_MY_H

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

void read_options(char *pattern, int argc, char *argv[], opt *options);
void add_pattern(char *pattern, char *src);

#endif