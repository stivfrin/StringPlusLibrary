#include "all_tests.h"

START_TEST(memset_random) {
  char bytes[] = RANDOM_BYTES;
  int c = bytes[_i];
  char* str1[21];
  char* str2[21];
  ck_assert_mem_eq(memset(str1, c, 20), s21_memset(str2, c, 20), 20);
}
END_TEST

Suite* memset_suite(void) {
  Suite* suite = suite_create("memset");
  TCase* memset_tcase = tcase_create("memset_tcase");

  tcase_add_loop_test(memset_tcase, memset_random, 0, 7);

  tcase_set_tags(memset_tcase, "memset all");
  suite_add_tcase(suite, memset_tcase);
  return suite;
}