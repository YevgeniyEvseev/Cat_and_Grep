#include <stdio.h>
#include <stdlib.h>

#include "grep_my.h"

int main() {
  struct C_string *buf = init_string();
  char str[100] = {0};
  cstr(buf, "");
  add_string(buf, "fuc");
  get_string(buf, str);
  printf("%s", str);
  clear_string(buf);
  add_string(buf, " you");

  printf("%s", get_str(buf));
  add_string_int(buf, 12345);
  get_string(buf, str);
  printf("%s", str);

  erase_string(buf);
}