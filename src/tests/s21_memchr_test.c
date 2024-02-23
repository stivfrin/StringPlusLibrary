#include "all_tests.h"

START_TEST(memchr_good) {
  char example = 'm';
  char* samples[] = LOREM_IPSUM;
  char* str = samples[_i];
  ck_assert_ptr_eq(memchr(str, example, 100), s21_memchr(str, example, 100));
}
END_TEST

START_TEST(memchr_1) {
  int example = 5;
  char str_1[50] = "Hello, World!";
  ck_assert_ptr_eq(memchr(str_1, example, 100),
                   s21_memchr(str_1, example, 100));
}
END_TEST

START_TEST(memchr_2) {
  char example = '\0';
  char str_1[20] = "";
  ck_assert_ptr_eq(memchr(str_1, example, 100),
                   s21_memchr(str_1, example, 100));
}
END_TEST

START_TEST(memchr_3) {
  char example = 72;
  char str_1[20] = "H";
  ck_assert_ptr_eq(memchr(str_1, example, 100),
                   s21_memchr(str_1, example, 100));
}
END_TEST

Suite* memchr_suite(void) {
  Suite* suite = suite_create("memchr");
  TCase* memchr_tcase = tcase_create("memchr_tcase");

  tcase_add_loop_test(memchr_tcase, memchr_good, 0, 8);

  tcase_add_test(memchr_tcase, memchr_1);
  tcase_add_test(memchr_tcase, memchr_2);
  tcase_add_test(memchr_tcase, memchr_3);

  tcase_set_tags(memchr_tcase, "memchr all");
  suite_add_tcase(suite, memchr_tcase);
  return suite;
}