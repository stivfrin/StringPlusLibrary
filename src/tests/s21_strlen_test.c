#include "all_tests.h"

START_TEST(strlen_good) {
  char* samples[] = LOREM_IPSUM;
  char* str = samples[_i];
  ck_assert_uint_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_bad) {
  char str[] = "";
  ck_assert_uint_eq(strlen(str), s21_strlen(str));
}
END_TEST

Suite* strlen_suite(void) {
  Suite* suite = suite_create("strlen");
  TCase* strlen_tcase = tcase_create("strlen_tcase");

  tcase_add_loop_test(strlen_tcase, strlen_good, 0, 8);
  tcase_add_test(strlen_tcase, strlen_bad);

  tcase_set_tags(strlen_tcase, "strlen all");
  suite_add_tcase(suite, strlen_tcase);
  return suite;
}