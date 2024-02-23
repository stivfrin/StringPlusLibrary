#include "all_tests.h"

START_TEST(to_upper_1) {
  char* samples_1 = "attention";
  char* samples_2 = "ATTENTION";
  char* samples_3 = s21_to_upper(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_upper_2) {
  char* samples_1 = "224";
  char* samples_2 = "224";
  char* samples_3 = s21_to_upper(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_upper_3) {
  char* samples_1 = "!!.?";
  char* samples_2 = "!!.?";
  char* samples_3 = s21_to_upper(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_upper_4) {
  char* samples_1 = "";
  char* samples_2 = "";
  char* samples_3 = s21_to_upper(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_upper_5) {
  char* samples_1 = "\0";
  char* samples_2 = "\0";
  char* samples_3 = s21_to_upper(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_upper_6) {
  char* samples_1 = "\n";
  char* samples_2 = "\n";
  char* samples_3 = s21_to_upper(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_upper_8) {
  char* samples_1 = S21_NULL;
  char* samples_2 = s21_to_upper(samples_1);
  ck_assert_ptr_null(samples_2);
  free(samples_2);
}
END_TEST

START_TEST(to_upper_9) {
  char* samples_1 = "~!@#$^&*()_+-WhATS=`;',./<>?:|";
  char* samples_2 = s21_to_upper(samples_1);
  ck_assert_pstr_eq(samples_2, "~!@#$^&*()_+-WHATS=`;',./<>?:|");
  if (samples_2) free(samples_2);
}
END_TEST

Suite* to_upper_suite(void) {
  Suite* suite = suite_create("to_upper");
  TCase* to_upper_tcase = tcase_create("to_upper_tcase");

  tcase_add_test(to_upper_tcase, to_upper_1);
  tcase_add_test(to_upper_tcase, to_upper_2);
  tcase_add_test(to_upper_tcase, to_upper_3);
  tcase_add_test(to_upper_tcase, to_upper_4);
  tcase_add_test(to_upper_tcase, to_upper_5);
  tcase_add_test(to_upper_tcase, to_upper_6);
  tcase_add_test(to_upper_tcase, to_upper_8);
  tcase_add_test(to_upper_tcase, to_upper_9);

  tcase_set_tags(to_upper_tcase, "to_upper all");
  suite_add_tcase(suite, to_upper_tcase);
  return suite;
}