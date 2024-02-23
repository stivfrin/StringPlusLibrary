#include "s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  void* res = S21_NULL;
  for (unsigned char* p = (void*)str; !res && p && n--; p++)
    if (*p == c) res = (void*)p;
  return res;
}
