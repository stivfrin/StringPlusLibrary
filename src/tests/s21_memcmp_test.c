#include "all_tests.h"

START_TEST(s21_memcmp_equal) {
  char *str1 = "string";
  char *str2 = "string";
  ck_assert_int_eq(memcmp(str1, str2, 6), s21_memcmp(str1, str2, 6));
}
END_TEST

START_TEST(s21_memcmp_ne) {
  char *str1 = "tempus vulnara sanas";
  char *str2 = "bibus";
  ck_assert_int_eq(memcmp(str1, str2, 6), s21_memcmp(str1, str2, 6));
}
END_TEST

START_TEST(s21_memcmp_test_register) {
  char *str1 = "audio";
  char *str2 = "Audio";
  ck_assert_int_eq(memcmp(str1, str2, 2), s21_memcmp(str1, str2, 2));
}
END_TEST

START_TEST(s21_memcmp_diff_lenght) {
  char *str1 = "meme";
  char *str2 = "memes";
  ck_assert_int_eq(memcmp(str1, str2, 5), s21_memcmp(str1, str2, 5));
}
END_TEST

START_TEST(s21_memcmp_long_string_eq) {
  char *str1 =
      "In the End, we will remember not the words of our enemies, but the "
      "silence of our friends.";
  char *str2 =
      "In the End, we will remember not the words of our enemies, but the "
      "silence of our friends.";
  ck_assert_int_eq(memcmp(str1, str2, 90), s21_memcmp(str1, str2, 90));
}
END_TEST

START_TEST(s21_memcmp_long_string_ne) {
  char *str1 =
      "In the End, we will remember not the words of our enemies, but the "
      "silence of our friends.";
  char *str2 =
      "In the And, we will remember not the words of our enemies, but the "
      "silence of our friends.";
  ck_assert_int_eq(memcmp(str1, str2, 6), s21_memcmp(str1, str2, 6));
}
END_TEST

START_TEST(s21_memcmp_numbers_eq) {
  char *str1 = "21";
  char *str2 = "21";
  ck_assert_int_eq(memcmp(str1, str2, 6), s21_memcmp(str1, str2, 6));
}
END_TEST

START_TEST(s21_memcmp_numbers_ne) {
  char *str1 = "21";
  char *str2 = "42";
  ck_assert_int_eq(memcmp(str1, str2, 2), s21_memcmp(str1, str2, 2));
}
END_TEST

Suite *memcmp_suite(void) {
  Suite *suite = suite_create("memcmp");
  TCase *memcmp_tcase = tcase_create("memcmp_tcase");

  tcase_add_test(memcmp_tcase, s21_memcmp_equal);
  tcase_add_test(memcmp_tcase, s21_memcmp_ne);
  tcase_add_test(memcmp_tcase, s21_memcmp_test_register);
  tcase_add_test(memcmp_tcase, s21_memcmp_diff_lenght);
  tcase_add_test(memcmp_tcase, s21_memcmp_long_string_eq);
  tcase_add_test(memcmp_tcase, s21_memcmp_long_string_ne);
  tcase_add_test(memcmp_tcase, s21_memcmp_numbers_eq);
  tcase_add_test(memcmp_tcase, s21_memcmp_numbers_ne);

  tcase_set_tags(memcmp_tcase, "memcmp all");
  suite_add_tcase(suite, memcmp_tcase);
  return suite;
}
