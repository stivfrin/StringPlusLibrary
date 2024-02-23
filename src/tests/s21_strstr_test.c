#include "all_tests.h"

START_TEST(strstr_empty_2) {
  char str[] = "time can not be returned";
  ck_assert_pstr_eq(strstr(str, ""), s21_strstr(str, ""));
}
END_TEST

START_TEST(strstr_email) {
  char str[] = "stivfrin@student.21-school.ru\0";
  ck_assert_pstr_eq(strstr(str, "sc"), s21_strstr(str, "sc"));
}
END_TEST

START_TEST(strstr_array_eq) {
  char str[] = {'z', 'i', 'b', 'a', 'k', 's', 'a', 's', '\0'};
  ck_assert_pstr_eq(strstr(str, "sas"), s21_strstr(str, "sas"));
}
END_TEST

START_TEST(strstr_array_ne) {
  char str[] = {'z', 'i', 'b', 'a', 'k', 's', 'a', 's', '\0'};
  ck_assert_pstr_eq(strstr(str, "sap"), s21_strstr(str, "sap"));
}
END_TEST

START_TEST(strstr_numbers) {
  char str[] = "123456";
  ck_assert_pstr_eq(strstr(str, "34"), s21_strstr(str, "34"));
}
END_TEST

START_TEST(strstr_register) {
  char str[] = "word";
  ck_assert_pstr_eq(strstr(str, "W"), s21_strstr(str, "W"));
}
END_TEST

START_TEST(strstr_diff_lenght) {
  char str[] = "time";
  ck_assert_pstr_eq(strstr(str, "timelapse"), s21_strstr(str, "timelapse"));
}
END_TEST

START_TEST(strstr_spec_t) {
  char str[] = "Hey! What's your name?";
  ck_assert_pstr_eq(strstr(str, "\t\n"), s21_strstr(str, "\t\n"));
}
END_TEST

START_TEST(strstr_spec_0) {
  char str[] = "Hey! What's your name?";
  ck_assert_pstr_eq(strstr(str, "\0"), s21_strstr(str, "\0"));
}
END_TEST

Suite* strstr_suite(void) {
  Suite* suite = suite_create("strstr");
  TCase* strstr_case = tcase_create("strstr_case");

  tcase_add_test(strstr_case, strstr_empty_2);
  tcase_add_test(strstr_case, strstr_email);
  tcase_add_test(strstr_case, strstr_array_eq);
  tcase_add_test(strstr_case, strstr_array_ne);
  tcase_add_test(strstr_case, strstr_numbers);
  tcase_add_test(strstr_case, strstr_register);
  tcase_add_test(strstr_case, strstr_diff_lenght);
  tcase_add_test(strstr_case, strstr_spec_t);
  tcase_add_test(strstr_case, strstr_spec_0);

  tcase_set_tags(strstr_case, "strstr all");
  suite_add_tcase(suite, strstr_case);
  return suite;
}
