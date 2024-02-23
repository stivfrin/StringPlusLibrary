#include "s21_string.h"

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t res = 0;
  s21_size_t lenght_str1 = s21_strlen(str1);
  s21_size_t lenght_str2 = s21_strlen(str2);
  int flag = 1;
  int arr[256] = {};
  for (s21_size_t i = 0; i < lenght_str2; i++) {
    arr[(int)str2[i]] = 1;
  }
  for (s21_size_t i = 0; i < lenght_str1 && flag; i++) {
    if (arr[(int)str1[i]] == 1) {
      res = i;
      flag = 0;
    }
  }
  if (flag) res = lenght_str1;
  return res;
}