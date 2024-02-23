#include "s21_string.h"

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  s21_size_t simbDEST = s21_strlen(dest);
  for (s21_size_t i = 0; i < n && src[i] != '\0'; i++) {
    dest[simbDEST + i] = src[i];
  }
  dest[simbDEST + n] = '\0';
  return dest;
}