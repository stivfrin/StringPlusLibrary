#include "all_tests.h"

START_TEST(strerror_all) { ck_assert_pstr_eq(strerror(_i), s21_strerror(_i)); }
END_TEST

Suite* strerror_suite(void) {
  Suite* suite = suite_create("strerror");
  TCase* strerror_tcase = tcase_create("strerror_tcase");

  tcase_add_loop_test(strerror_tcase, strerror_all, -2, 150);

  tcase_set_tags(strerror_tcase, "strerror all");
  suite_add_tcase(suite, strerror_tcase);
  return suite;
}