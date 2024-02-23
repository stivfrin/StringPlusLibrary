#include "s21_string.h"

void* s21_to_upper(const char* str) {
  char* res = S21_NULL;
  int len = 0;
  if (str) {
    len = s21_strlen(str);
    res = calloc(len + 1, sizeof(char));
  }
  if (res) {
    for (int k = 0; k < len; ++k) {
      if (str[k] > 96 && str[k] < 123)
        res[k] = str[k] - 32;
      else
        res[k] = str[k];
    }
  }
  return res;
}