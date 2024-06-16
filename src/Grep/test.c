#include <stdio.h>
#include <stdlib.h>

#include "grep_my.h"

int main() {
  struct str_pattern *buf = init_pattern();
  char str[100] = {0};
  cstr(buf, str);
  add_pattern(buf, "fuc");
  get_pattern(buf, str);
  printf("%s", str);
  clear_pattern(buf);
  add_pattern(buf, " you");
  get_pattern(buf, str);
  printf("%s", str);
}