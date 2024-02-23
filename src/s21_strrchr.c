#include "s21_string.h"

char* s21_strrchr(const char* str, int c) {
  void* res = S21_NULL;
  for (char* p = (char*)str; p; p++) {
    if (*p == c) res = p;
    if (!*p) break;
  }
  return res;
}