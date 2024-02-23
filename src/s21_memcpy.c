#include "s21_string.h"

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  unsigned char* src1 = (void*)src;
  unsigned char* dest1 = (void*)dest;
  for (s21_size_t i = 0; i < n; i++) {
    *(dest1 + i) = *(src1 + i);
  }
  return dest1;
}