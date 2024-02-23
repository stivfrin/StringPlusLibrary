#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL) return S21_NULL;
  char *new_str = S21_NULL;
  new_str = extra_trim(src, trim_chars);
  char *res = S21_NULL;
  res = extra_trim(new_str, trim_chars);
  free(new_str);
  return (void *)res;
}

void *extra_trim(const char *src, const char *trim_chars) {
  char *new_str = (char *)calloc(s21_strlen(src) + 1, sizeof(char));
  int i = s21_strlen(src) - 1, j = 0;
  int n = 0;
  while (i > -1) {
    for (int k = 0; k < (int)s21_strlen(trim_chars); k++) {
      if (src[i] == trim_chars[k]) {
        i--;
        n = 1;
        break;
      } else {
        n = 0;
      }
    }
    if (n == 0) break;
  }
  for (; i >= 0; i--) {
    new_str[j] = src[i];
    j++;
  }
  return (void *)new_str;
}