#include "all_tests.h"

START_TEST(to_lower_1) {
  char* samples_1 = "ATTENTION";
  char* samples_2 = "attention";
  char* samples_3 = s21_to_lower(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_lower_2) {
  char* samples_1 = "224";
  char* samples_2 = "224";
  char* samples_3 = s21_to_lower(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_lower_3) {
  char* samples_1 = "!!.?";
  char* samples_2 = "!!.?";
  char* samples_3 = s21_to_lower(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_lower_4) {
  char* samples_1 = "";
  char* samples_2 = "";
  char* samples_3 = s21_to_lower(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_lower_5) {
  char* samples_1 = "\0";
  char* samples_2 = "\0";
  char* samples_3 = s21_to_lower(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_lower_6) {
  char* samples_1 = "\n";
  char* samples_2 = "\n";
  char* samples_3 = s21_to_lower(samples_1);
  ck_assert_pstr_eq(samples_3, samples_2);
  free(samples_3);
}
END_TEST

START_TEST(to_lower_8) {
  char* samples_1 = S21_NULL;
  char* samples_2 = s21_to_lower(samples_1);
  ck_assert_ptr_null(samples_2);
  free(samples_2);
}
END_TEST

START_TEST(to_lower_9) {
  char* samples_1 = "~!@#$^&*()_+-WhATS=`;',./<>?:|";
  char* samples_2 = s21_to_lower(samples_1);
  ck_assert_pstr_eq(samples_2, "~!@#$^&*()_+-whats=`;',./<>?:|");
  if (samples_2) free(samples_2);
}
END_TEST

Suite* to_lower_suite(void) {
  Suite* suite = suite_create("to_lower");
  TCase* to_lower_tcase = tcase_create("to_lower_tcase");

  tcase_add_test(to_lower_tcase, to_lower_1);
  tcase_add_test(to_lower_tcase, to_lower_2);
  tcase_add_test(to_lower_tcase, to_lower_3);
  tcase_add_test(to_lower_tcase, to_lower_4);
  tcase_add_test(to_lower_tcase, to_lower_5);
  tcase_add_test(to_lower_tcase, to_lower_6);
  tcase_add_test(to_lower_tcase, to_lower_8);
  tcase_add_test(to_lower_tcase, to_lower_9);

  tcase_set_tags(to_lower_tcase, "to_lower all");
  suite_add_tcase(suite, to_lower_tcase);
  return suite;
}