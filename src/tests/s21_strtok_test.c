#include "all_tests.h"

START_TEST(strtok_good) {
  char* samp[] = LOREM_IPSUM;
  char* delim = "5";
  char* str1 = strcpy(calloc(strlen(samp[_i]) + 1, sizeof(char)), samp[_i]);
  char* str2 = strcpy(calloc(strlen(samp[_i]) + 1, sizeof(char)), samp[_i]);
  char* text1[21];
  char* text2[21];

  text1[0] = strtok(str1, delim);
  text2[0] = s21_strtok(str2, delim);
  int k = 0;
  while (text1[k] && text2[k]) {
    k++;
    text1[k] = strtok(NULL, delim);
    text2[k] = s21_strtok(NULL, delim);
  }

  for (int k = 0; k < 21; k++)
    if (text1[k] && text2[k]) {
      ck_assert_pstr_eq(text1[k], text2[k]);
    } else
      k = 21;

  free(str1);
  free(str2);
}
END_TEST

Suite* strtok_suite(void) {
  Suite* suite = suite_create("strtok");
  TCase* strtok_tcase = tcase_create("strtok_tcase");

  tcase_add_loop_test(strtok_tcase, strtok_good, 0, 8);

  tcase_set_tags(strtok_tcase, "strtok all");
  suite_add_tcase(suite, strtok_tcase);
  return suite;
}