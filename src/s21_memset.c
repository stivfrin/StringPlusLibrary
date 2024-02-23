#include "s21_string.h"

void* s21_memset(void* str, int c, s21_size_t n) {
  unsigned char* p = str;
  while (p && n--) *p++ = (unsigned char)c;
  return str;
}