#include "s21_string.h"

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  int res = 0;
  const unsigned char* byte1 = str1;
  const unsigned char* byte2 = str2;

  for (; n--; byte1++, byte2++) {
    if (*byte1 != *byte2) {
      res = *byte1 - *byte2;
      n = 0;
    }
  }
  return res;
}