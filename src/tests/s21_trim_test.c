#include "all_tests.h"

START_TEST(test_trim) {
  char *res1_1 = S21_NULL;
  res1_1 = s21_trim(" YaLomalstekloH B  ", " ");
  char *res1_2 = "YaLomalstekloH B";
  char *res2_1 = S21_NULL;
  res2_1 = s21_trim("GarryPotter228 genderBOY", "GY");
  char *res2_2 = "arryPotter228 genderBO";
  char *res3_1 = S21_NULL;
  res3_1 = s21_trim("", "528741");
  char *res3_2 = "";
  char *res4_1 = S21_NULL;
  res4_1 = s21_trim(" GarryPotter228! * > @ < genderBOY", " GaY");
  char *res4_2 = "rryPotter228! * > @ < genderBO";
  char *res5_1 = S21_NULL;
  res5_1 = s21_trim("#@# ()****) #@       ", "#@ ");
  char *res5_2 = "()****)";

  ck_assert_str_eq(res1_1, res1_2);
  ck_assert_str_eq(res2_1, res2_2);
  ck_assert_str_eq(res3_1, res3_2);
  ck_assert_str_eq(res4_1, res4_2);
  ck_assert_str_eq(res5_1, res5_2);

  if (res1_1) free(res1_1);
  if (res2_1) free(res2_1);
  if (res3_1) free(res3_1);
  if (res4_1) free(res4_1);
  if (res5_1) free(res5_1);
}
END_TEST

Suite *trim_suite(void) {
  Suite *suite = suite_create("trim");
  TCase *trim_tcase = tcase_create("trim_tcase");

  tcase_add_test(trim_tcase, test_trim);

  tcase_set_tags(trim_tcase, "trim all");
  suite_add_tcase(suite, trim_tcase);
  return suite;
}