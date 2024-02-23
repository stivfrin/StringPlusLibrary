#include "all_tests.h"
#define BUFF 100

START_TEST(strpbrk_good) {
  char* samples[] = LOREM_IPSUM;
  char* str1 = samples[_i];
  char* str2 = "mq";
  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_god) {
  char str1[BUFF] = "Oh my GOD!";
  char str2[BUFF] = "!";
  ck_assert_pstr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_spec) {
  char str1[BUFF] = "In the \n\t\bend its just beginning!";
  char str2[BUFF] = "Fru\nits";
  ck_assert_pstr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_end) {
  char str1[BUFF] = "\0";
  char str2[BUFF] = "";
  ck_assert_pstr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_empty) {
  char str1[BUFF] = "";
  char str2[BUFF] = "";
  ck_assert_pstr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_num) {
  char str1[BUFF] = "456738490057";
  char str2[BUFF] = "38";
  ck_assert_pstr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_ne) {
  char str1[BUFF] = "jameson";
  char str2[BUFF] = "zZz";
  ck_assert_pstr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

Suite* strpbrk_suite(void) {
  Suite* suite = suite_create("strpbrk");
  TCase* strpbrk_tcase = tcase_create("strpbrk_tcase");

  tcase_add_loop_test(strpbrk_tcase, strpbrk_good, 0, 8);
  tcase_add_test(strpbrk_tcase, strpbrk_god);
  tcase_add_test(strpbrk_tcase, strpbrk_spec);
  tcase_add_test(strpbrk_tcase, strpbrk_end);
  tcase_add_test(strpbrk_tcase, strpbrk_empty);
  tcase_add_test(strpbrk_tcase, strpbrk_num);
  tcase_add_test(strpbrk_tcase, strpbrk_ne);

  tcase_set_tags(strpbrk_tcase, "strpbrk all");
  suite_add_tcase(suite, strpbrk_tcase);
  return suite;
}
