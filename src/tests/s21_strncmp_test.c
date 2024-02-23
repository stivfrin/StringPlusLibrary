#include "all_tests.h"

START_TEST(s21_strncmp_equal) {
  char *str1 = "tempus vulnara sanas";
  char *str2 = "tempus";
  ck_assert_int_eq(strncmp(str1, str2, 6), s21_strncmp(str1, str2, 6));
}
END_TEST

START_TEST(s21_strncmp_diff) {
  char *str1 = "tempus vulnara sanas";
  char *str2 = "out of campus";
  ck_assert_int_eq(strncmp(str1, str2, 3), s21_strncmp(str1, str2, 3));
}
END_TEST

START_TEST(s21_strncmp_part_match) {
  char *str1 = "tempus vulnara sanas";
  char *str2 = "tempus mori";
  ck_assert_int_eq(strncmp(str1, str2, 6), s21_strncmp(str1, str2, 6));
}
END_TEST

START_TEST(s21_strncmp_empty) {
  char *str1 = "";
  char *str2 = "";
  ck_assert_int_eq(strncmp(str1, str2, 0), s21_strncmp(str1, str2, 0));
}
END_TEST

Suite *strncmp_suite(void) {
  Suite *suite = suite_create("strncmp");
  TCase *strncmp_tcase = tcase_create("strncmp_tcase");

  tcase_add_test(strncmp_tcase, s21_strncmp_equal);
  tcase_add_test(strncmp_tcase, s21_strncmp_diff);
  tcase_add_test(strncmp_tcase, s21_strncmp_part_match);
  tcase_add_test(strncmp_tcase, s21_strncmp_empty);

  tcase_set_tags(strncmp_tcase, "strncmp all");
  suite_add_tcase(suite, strncmp_tcase);
  return suite;
}
