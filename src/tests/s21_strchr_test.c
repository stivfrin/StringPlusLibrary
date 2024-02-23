#include "all_tests.h"

START_TEST(strchr_good) {
  char example = 'i';
  char* samples[] = LOREM_IPSUM;
  char* str = samples[_i];
  ck_assert_ptr_eq(strchr(str, example), s21_strchr(str, example));
}
END_TEST

START_TEST(strchr_1) {
  int example = 5;
  char str_1[50] = "Hello, World!";
  ck_assert_ptr_eq(strchr(str_1, example), s21_strchr(str_1, example));
}
END_TEST

START_TEST(strchr_2) {
  char example = '\0';
  char str_1[20] = "";
  ck_assert_pstr_eq(strchr(str_1, example), s21_strchr(str_1, example));
}
END_TEST

START_TEST(strchr_3) {
  char example = 72;
  char str_1[20] = "H";
  ck_assert_ptr_eq(strchr(str_1, example), s21_strchr(str_1, example));
}
END_TEST

START_TEST(strchr_4) {
  char example = 'a';
  char str_1[20] = "Atlant age agu";
  ck_assert_ptr_eq(strchr(str_1, example), s21_strchr(str_1, example));
}
END_TEST

Suite* strchr_suite(void) {
  Suite* suite = suite_create("strchr");
  TCase* strchr_tcase = tcase_create("strchr_tcase");

  tcase_add_loop_test(strchr_tcase, strchr_good, 0, 8);

  tcase_add_test(strchr_tcase, strchr_1);
  tcase_add_test(strchr_tcase, strchr_2);
  tcase_add_test(strchr_tcase, strchr_3);
  tcase_add_test(strchr_tcase, strchr_4);

  tcase_set_tags(strchr_tcase, "strchr all");
  suite_add_tcase(suite, strchr_tcase);
  return suite;
}
