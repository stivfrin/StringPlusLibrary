#include "all_tests.h"

START_TEST(strcspn_good) {
  char* samples[] = LOREM_IPSUM;
  char* str1 = samples[_i];
  char str2[] = "im";
  ck_assert_uint_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_bad) {
  char str1[] = "";
  char str2[] = "im";
  ck_assert_uint_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

Suite* strcspn_suite(void) {
  Suite* suite = suite_create("strcspn");
  TCase* strcspn_tcase = tcase_create("strcspn_tcase");

  tcase_add_loop_test(strcspn_tcase, strcspn_good, 0, 8);
  tcase_add_test(strcspn_tcase, strcspn_bad);

  tcase_set_tags(strcspn_tcase, "strcspn all");
  suite_add_tcase(suite, strcspn_tcase);
  return suite;
}