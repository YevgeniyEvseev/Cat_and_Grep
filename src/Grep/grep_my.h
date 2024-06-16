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

struct str_pattern;

struct str_pattern *init_pattern();
void cstr(struct str_pattern *pattern, char *str);
void get_pattern(const struct str_pattern *pattern, char *str);
void add_pattern(struct str_pattern *pattern, char *str);
int is_empty(const struct str_pattern *pattern);
int len_pattern(const struct str_pattern *pattern);
void erase_pattern(struct str_pattern *pattern);
void clear_pattern(struct str_pattern *pattern);

void read_options(struct str_pattern *pattern, int argc, char *argv[], opt *options);
void add_to_pattern(struct str_pattern *pattern, char *str);

//void get_data_from_regcomp(const int optind, const char **argv, regex_t *reg,
 //                          opt *option);

#endif