#include "all_tests.h"

#define BUFF 50

START_TEST(s21_strncat_equal) {
  char str1[BUFF] = "tempus vulnara sanas";
  char str2[BUFF] = "tempus vulnara sanas";
  char str3[BUFF] = "tempus";
  s21_size_t n = 5;
  ck_assert_pstr_eq(strncat(str1, str3, n), s21_strncat(str2, str3, n));
}
END_TEST

START_TEST(s21_strncat_diff) {
  char str1[BUFF] = "tempus vulnara sanas";
  char str2[BUFF] = "tempus vulnara sanas";
  char str3[BUFF] = "out of campus";
  s21_size_t n = 3;
  ck_assert_pstr_eq(strncat(str1, str3, n), s21_strncat(str2, str3, n));
}
END_TEST

START_TEST(s21_strncat_mid) {
  char str1[BUFF] = "Oh My God!";
  char str2[BUFF] = "Oh My God!";
  char str3[BUFF] = "\0\0\0";
  s21_size_t n = 5;
  ck_assert_pstr_eq(strncat(str1, str3, n), s21_strncat(str2, str3, n));
}
END_TEST

START_TEST(s21_strncat_mid2) {
  char str1[BUFF] = "Hello,\0 World!";
  char str2[BUFF] = "Hello,\0 World!";
  char str3[BUFF] = "again";
  s21_size_t n = 5;
  ck_assert_pstr_eq(strncat(str1, str3, n), s21_strncat(str2, str3, n));
}
END_TEST

START_TEST(s21_strncat_empty) {
  char str1[BUFF] = "";
  char str2[BUFF] = "";
  char str3[BUFF] = "tempus";
  s21_size_t n = 5;
  ck_assert_pstr_eq(strncat(str1, str3, n), s21_strncat(str2, str3, n));
}
END_TEST

START_TEST(s21_strncat_empty2) {
  char str1[BUFF] = "";
  char str2[BUFF] = "";
  char str3[BUFF] = "";
  s21_size_t n = 15;
  ck_assert_pstr_eq(strncat(str1, str2, n), s21_strncat(str2, str3, n));
}
END_TEST

START_TEST(s21_strncat_empty3) {
  char str1[BUFF] = "say hello to my little tests";
  char str2[BUFF] = "say hello to my little tests";
  char str3[BUFF] = "";
  s21_size_t n = 5;
  ck_assert_pstr_eq(strncat(str1, str3, n), s21_strncat(str2, str3, n));
}
END_TEST

START_TEST(s21_strncat_null) {
  char str1[BUFF] = "\0\0\0";
  char str2[BUFF] = "\0\0\0";
  char str3[BUFF] = "god";
  s21_size_t n = 3;
  ck_assert_pstr_eq(strncat(str1, str3, n), s21_strncat(str2, str3, n));
}
END_TEST

START_TEST(s21_strncat_null2) {
  char str1[BUFF] = "\0\0\0";
  char str2[BUFF] = "\0\0\0";
  char str3[BUFF] = "\0";
  s21_size_t n = 1;
  ck_assert_pstr_eq(strncat(str1, str3, n), s21_strncat(str2, str3, n));
}
END_TEST

Suite *strncat_suite(void) {
  Suite *suite = suite_create("strncat");
  TCase *strncat_tcase = tcase_create("strncat_tcase");

  tcase_add_test(strncat_tcase, s21_strncat_equal);
  tcase_add_test(strncat_tcase, s21_strncat_diff);
  tcase_add_test(strncat_tcase, s21_strncat_mid);
  tcase_add_test(strncat_tcase, s21_strncat_mid2);
  tcase_add_test(strncat_tcase, s21_strncat_empty);
  tcase_add_test(strncat_tcase, s21_strncat_empty2);
  tcase_add_test(strncat_tcase, s21_strncat_empty3);
  tcase_add_test(strncat_tcase, s21_strncat_null);
  tcase_add_test(strncat_tcase, s21_strncat_null2);

  tcase_set_tags(strncat_tcase, "strncat all");
  suite_add_tcase(suite, strncat_tcase);
  return suite;
}
