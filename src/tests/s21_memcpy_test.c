#include "all_tests.h"

#define BUFF 50

START_TEST(s21_memcpy_equal) {
  char str1[BUFF] = {0};
  char str2[BUFF] = {0};
  char str3[BUFF] = "tempus";
  s21_size_t n = 6;
  memcpy(str1, str3, n);
  s21_memcpy(str2, str3, n);
  ck_assert_mem_eq(str1, str2, n);
}
END_TEST

START_TEST(s21_memcpy_diff) {
  char str1[BUFF] = "tem";
  char str2[BUFF] = "vul";
  char str3[BUFF] = "tempus vulnara sanas";
  s21_size_t n = 3;
  memcpy(str1, str3, n);
  s21_memcpy(str2, str3, n);
  ck_assert_mem_eq(str1, str2, n);
}
END_TEST

START_TEST(s21_memcpy_part_match) {
  char str1[BUFF] = {0};
  char str2[BUFF] = "tempus";
  char str3[BUFF] = "tempus vulnara sanas";
  s21_size_t n = 6;
  memcpy(str1, str3, n);
  s21_memcpy(str2, str3, n);
  ck_assert_mem_eq(str1, str2, n);
}
END_TEST

START_TEST(s21_memcpy_empty) {
  char str1[BUFF] = "";
  char str2[BUFF] = "";
  char str3[BUFF] = "";
  s21_size_t n = 0;
  memcpy(str1, str3, n);
  s21_memcpy(str2, str3, n);
  ck_assert_mem_eq(str1, str2, n);
}
END_TEST

START_TEST(s21_memcpy_max) {
  char str1[BUFF] = "iam ";
  char str2[BUFF] = "iam ";
  char str3[BUFF] = "testwin";
  s21_size_t n = 5;
  memcpy(str1, str3, n);
  s21_memcpy(str2, str3, n);
  ck_assert_mem_eq(str1, str2, n);
}
END_TEST

START_TEST(s21_memcpy_over) {
  char str1[BUFF] = "tempus";
  char str2[BUFF] = "tempus";
  char str3[BUFF] = "";
  s21_size_t n = 6;
  memcpy(str1, str3, n);
  s21_memcpy(str2, str3, n);
  ck_assert_mem_eq(str1, str2, n);
}
END_TEST

START_TEST(s21_memcpy_null) {
  char str1[BUFF] = "tempus";
  char str2[BUFF] = "tempus";
  char str3[BUFF] = "\0";
  s21_size_t n = 1;
  memcpy(str1, str3, n);
  s21_memcpy(str2, str3, n);
  ck_assert_mem_eq(str1, str2, n);
}
END_TEST

Suite *memcpy_suite(void) {
  Suite *suite = suite_create("memcpy");
  TCase *memcpy_tcase = tcase_create("memcpy_tcase");

  tcase_add_test(memcpy_tcase, s21_memcpy_equal);
  tcase_add_test(memcpy_tcase, s21_memcpy_part_match);
  tcase_add_test(memcpy_tcase, s21_memcpy_empty);
  tcase_add_test(memcpy_tcase, s21_memcpy_max);
  tcase_add_test(memcpy_tcase, s21_memcpy_over);
  tcase_add_test(memcpy_tcase, s21_memcpy_diff);
  tcase_add_test(memcpy_tcase, s21_memcpy_null);

  tcase_set_tags(memcpy_tcase, "memcpy all");
  suite_add_tcase(suite, memcpy_tcase);
  return suite;
}
