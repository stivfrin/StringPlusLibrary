#include "all_tests.h"

#define BUFF 100

START_TEST(strrchr_good) {
  char example = 'i';
  char* samples[] = LOREM_IPSUM;
  char* str = samples[_i];
  ck_assert_ptr_eq(strrchr(str, example), s21_strrchr(str, example));
}
END_TEST

START_TEST(strrchr_1) {
  char example = 6;
  char str_1[50] = "Hello, World!";
  ck_assert_ptr_eq(strrchr(str_1, example), s21_strrchr(str_1, example));
}
END_TEST

START_TEST(strrchr_2) {
  char example = '\0';
  char str_1[20] = "";
  ck_assert_pstr_eq(strrchr(str_1, example), s21_strrchr(str_1, example));
}
END_TEST

START_TEST(strrchr_3) {
  char example = 72;
  char str_1[20] = "H";
  ck_assert_ptr_eq(strrchr(str_1, example), s21_strrchr(str_1, example));
}
END_TEST

START_TEST(strrchr_4) {
  char example = 'a';
  char str_1[20] = "Atlant age agu";
  ck_assert_ptr_eq(strrchr(str_1, example), s21_strrchr(str_1, example));
}
END_TEST

START_TEST(strrchr_5) {
  char example = '!';
  char str_1[20] = "Atlant age agu";
  ck_assert_ptr_eq(strrchr(str_1, example), s21_strrchr(str_1, example));
}
END_TEST

Suite* strrchr_suite(void) {
  Suite* suite = suite_create("strrchr");
  TCase* strrchr_tcase = tcase_create("strrchr_tcase");

  tcase_add_loop_test(strrchr_tcase, strrchr_good, 0, 8);

  tcase_add_test(strrchr_tcase, strrchr_1);
  tcase_add_test(strrchr_tcase, strrchr_2);
  tcase_add_test(strrchr_tcase, strrchr_3);
  tcase_add_test(strrchr_tcase, strrchr_4);
  tcase_add_test(strrchr_tcase, strrchr_5);

  tcase_set_tags(strrchr_tcase, "strrchr all");
  suite_add_tcase(suite, strrchr_tcase);
  return suite;
}