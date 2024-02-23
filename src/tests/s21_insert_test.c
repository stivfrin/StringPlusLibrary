#include "all_tests.h"

static char* str2;

void insert_free(void);
void insert_free(void) { free(str2); }

START_TEST(s21_insert_ok) {
  char* str1 = "rose";
  str2 = s21_insert(str1, "mary", 4);
  ck_assert_pstr_eq(str2, "rosemary");
}
END_TEST

START_TEST(s21_insert_bad1) {
  char* str1 = "rose";
  str2 = s21_insert(str1, "mary", 6);
  ck_assert_pstr_eq(str2, S21_NULL);
}
END_TEST

START_TEST(s21_insert_bad2) {
  char* str1 = S21_NULL;
  str2 = s21_insert(str1, "ction", 2);
  ck_assert_pstr_eq(str2, S21_NULL);
}
END_TEST

Suite* insert_suite(void) {
  Suite* suite = suite_create("insert");
  TCase* insert_tcase = tcase_create("insert_tcase");

  tcase_add_test(insert_tcase, s21_insert_ok);
  tcase_add_test(insert_tcase, s21_insert_bad1);
  tcase_add_test(insert_tcase, s21_insert_bad2);

  tcase_add_checked_fixture(insert_tcase, NULL, insert_free);
  tcase_set_tags(insert_tcase, "insert all");
  suite_add_tcase(suite, insert_tcase);
  return suite;
}