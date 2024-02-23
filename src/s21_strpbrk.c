#include "s21_string.h"

char* s21_strpbrk(const char* str1, const char* str2) {
  char* res = S21_NULL;
  for (char* p = (char*)str1; p && *p && !res; p++)
    if (s21_strchr(str2, *p)) res = p;
  return res;
}
