#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  int len;
  int cap;
} C_string;

C_string *init_string() {
  C_string *tmp = malloc(sizeof(C_string));
  tmp->cap = 0;
  tmp->len = 0;
  return tmp;
}

void cstr(C_string *pattern, char *str) {
  pattern->len = strlen(str);
  pattern->cap = pattern->len + 1;
  pattern->data = calloc(pattern->cap, sizeof(char));
  strcpy(pattern->data, str);
}

void get_string(const C_string *pattern, char *str) {
  strcpy(str, pattern->data);
}

char *get_str(const C_string *pattern) { return pattern->data; }

void add_string(C_string *pattern, char *str) {
  int len_str = strlen(str);
  while (pattern->cap - pattern->len - 1 < len_str) {
    pattern->cap += len_str;
    pattern->cap *= 2;
    pattern->data = realloc(pattern->data, (pattern->cap) * sizeof(char));
    if (pattern->data == NULL) exit(1);
  }
  if (pattern->len == 0) {
    strcpy(pattern->data, str);
  } else {
    strcat(pattern->data, str);
  }
  pattern->len += len_str;
}

void add_string_char(C_string *pattern, char charac) {
  while (pattern->cap - pattern->len - 1 < 1) {
    if (pattern->cap == 0) pattern->cap = 1;
    pattern->cap *= 2;
    if ((pattern->data =
             realloc(pattern->data, (pattern->cap) * sizeof(char))) == NULL)
      exit(1);
  }
  pattern->len += 1;
  *(pattern->data + pattern->len) = charac;
}

int is_empty(const C_string *pattern) { return (pattern->len == 0) ? 1 : 0; }
int len_string(const C_string *pattern) { return pattern->len; }

void erase_string(C_string *pattern) {
  free(pattern->data);
  free(pattern);
}

void clear_string(C_string *pattern) {
  char *tmp = pattern->data;
  for (; *(pattern->data) != '\0'; pattern->data++) {
    *(pattern->data) = '\0';
  }
  pattern->data = tmp;
  pattern->len = 0;
}

void add_string_int(C_string *str, int n) {
  char tmp[11] = {0};
  int i = 0, k = 0;
  do {
    tmp[i++] = '0' + (n % 10);
  } while ((n /= 10) > 0);
  i--;
  for (; i > k; i--, ++k) {
    char c = tmp[i];
    tmp[i] = tmp[k];
    tmp[k] = c;
  }
  add_string(str, tmp);
}