#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const char *end = str1 + n;
  int res = 0;
  for (; res == 0 && str1 != end && (*str1 || *str2);
       res = *(str1++) - *(str2++))
    ;
  return res;
}
