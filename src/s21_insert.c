#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result_str = S21_NULL;
  s21_size_t src_len = src ? s21_strlen(src) : 0;
  s21_size_t str_len = str ? s21_strlen(str) : 0;
  if (start_index <= src_len && src && str) {
    result_str = (char *)calloc(src_len + str_len + 1, sizeof(char));
    if (result_str) {
      for (s21_size_t i = 0, j = 0, l = 0; i < src_len + str_len;) {
        if (i == start_index)
          for (; *(str + j); ++j) result_str[i++] = str[j];
        else
          result_str[i++] = src[l++];
      }
    }
  }
  return result_str;
}
