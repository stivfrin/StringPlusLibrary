#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t n = s21_strlen(needle);
  while (*haystack) {
    if (!s21_memcmp(haystack, needle, n)) {
      return (char *)haystack;
    }
    haystack++;
  }
  return S21_NULL;
}
