#include "s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* saved_p;
  if (!str) str = saved_p;
  if (str) {
    while (s21_strchr(delim, *str)) str++;
    char* p = s21_strpbrk(str, delim);
    if (p) *p++ = 0;
    saved_p = p;
  }
  return str;
}