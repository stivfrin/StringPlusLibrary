#include "all_tests.h"

#define BUFF 100

START_TEST(s21_strncpy_equal) {
  char str1[BUFF] = "tempus vulnara sanas";
  char str2[BUFF] = "tempus vulnara sanas";
  char str3[BUFF] = "tempus";
  s21_size_t n = 6;
  ck_assert_pstr_eq(strncpy(str1, str3, n), s21_strncpy(str2, str3, n));
}
END_TEST

START_TEST(s21_strncpy_diff) {
  char str1[BUFF] = "tempus vulnara sanas";
  char str2[BUFF] = "tempus vulnara sanas";
  char str3[BUFF] = "out of campus";
  s21_size_t n = 3;
  ck_assert_pstr_eq(strncpy(str1, str3, n), s21_strncpy(str2, str3, n));
}
END_TEST

START_TEST(s21_strncpy_part_match) {
  char str1[BUFF] = "tempus vulnara sanas";
  char str2[BUFF] = "tempus vulnara sanas";
  char str3[BUFF] = "tempus mori";
  s21_size_t n = 6;
  ck_assert_pstr_eq(strncpy(str1, str3, n), s21_strncpy(str2, str3, n));
}
END_TEST

START_TEST(s21_strncpy_empty) {
  char str1[BUFF] = "";
  char str2[BUFF] = "";
  char str3[BUFF] = "";
  s21_size_t n = 0;
  ck_assert_pstr_eq(strncpy(str1, str3, n), s21_strncpy(str2, str3, n));
}
END_TEST

START_TEST(s21_strncpy_null) {
  char str1[BUFF] = "Tempus vulnara sanas";
  char str2[BUFF] = "Tempus vulnara sanas";
  char str3[BUFF] = "\0";
  s21_size_t n = 1;
  ck_assert_pstr_eq(strncpy(str1, str3, n), s21_strncpy(str2, str3, n));
}
END_TEST

START_TEST(s21_strncpy_symb) {
  char str1[BUFF] = "Tempus vulnara sanas";
  char str2[BUFF] = "Tempus vulnara sanas";
  char str3[BUFF] = "~!@#$^&*()_+|<>?`-=;',./";
  s21_size_t n = 13;
  ck_assert_pstr_eq(strncpy(str1, str3, n), s21_strncpy(str2, str3, n));
}
END_TEST

START_TEST(s21_strncpy_quest) {
  char str1[BUFF] = "";
  char str2[BUFF] = "";
  char str3[BUFF] = "???????????????????????";
  s21_size_t n = s21_strlen(str3);
  ck_assert_pstr_eq(strncpy(str1, str3, n), s21_strncpy(str2, str3, n));
}
END_TEST

Suite* strncpy_suite(void) {
  Suite* suite = suite_create("strncpy");
  TCase* strncpy_tcase = tcase_create("strncpy_tcase");

  tcase_add_test(strncpy_tcase, s21_strncpy_equal);
  tcase_add_test(strncpy_tcase, s21_strncpy_diff);
  tcase_add_test(strncpy_tcase, s21_strncpy_part_match);
  tcase_add_test(strncpy_tcase, s21_strncpy_empty);
  tcase_add_test(strncpy_tcase, s21_strncpy_null);
  tcase_add_test(strncpy_tcase, s21_strncpy_symb);
  tcase_add_test(strncpy_tcase, s21_strncpy_quest);

  tcase_set_tags(strncpy_tcase, "strncpy all");
  suite_add_tcase(suite, strncpy_tcase);
  return suite;
}
