#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  int len;
  int cap;
} str_pattern;

str_pattern *init_pattern() {
  str_pattern *tmp = malloc(sizeof(str_pattern));
  tmp->cap = 0;
  tmp->len = 0;
  return tmp;
}

void cstr(str_pattern *pattern, char *str) {
  pattern->len = strlen(str);
  pattern->cap = pattern->len + 1;
  pattern->data = malloc(pattern->cap * sizeof(char));
  strcpy(pattern->data, str);
}

void get_pattern(const str_pattern *pattern, char *str) {
  strcpy(str, pattern->data);
}

void add_pattern(str_pattern *pattern, char *str) {
  int len_str = strlen(str);
  while (pattern->cap - pattern->len - 1 < len_str) {
    pattern->cap += len_str;
    pattern->cap *= 2;
    if ((pattern->data = realloc(
             pattern->data, (pattern->cap + len_str) * sizeof(char))) == NULL)
      exit(1);
  }
  pattern->len += len_str;
  strcat(pattern->data, str);
}
int is_empty(const str_pattern *pattern) { return (pattern->len == 0) ? 1 : 0; }
int len_pattern(const str_pattern *pattern) { return pattern->len; }

void erase_pattern(str_pattern *pattern) {
  free(pattern->data);
  free(pattern);
}
