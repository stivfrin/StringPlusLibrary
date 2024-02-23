#include "all_tests.h"

int main() {
  setenv("CK_DEFAULT_TIMEOUT", "0.5", 1);
  SRunner *string_runner = srunner_create(memchr_suite());
  srunner_add_suite(string_runner, memcmp_suite());
  srunner_add_suite(string_runner, memcpy_suite());
  srunner_add_suite(string_runner, memset_suite());
  srunner_add_suite(string_runner, strchr_suite());
  srunner_add_suite(string_runner, strcspn_suite());
  srunner_add_suite(string_runner, strerror_suite());
  srunner_add_suite(string_runner, strlen_suite());
  srunner_add_suite(string_runner, strncat_suite());
  srunner_add_suite(string_runner, strncmp_suite());
  srunner_add_suite(string_runner, strncpy_suite());
  srunner_add_suite(string_runner, strpbrk_suite());
  srunner_add_suite(string_runner, strrchr_suite());
  srunner_add_suite(string_runner, strstr_suite());
  srunner_add_suite(string_runner, strtok_suite());

  srunner_add_suite(string_runner, to_upper_suite());
  srunner_add_suite(string_runner, to_lower_suite());
  srunner_add_suite(string_runner, insert_suite());
  srunner_add_suite(string_runner, trim_suite());

  srunner_add_suite(string_runner, sprintf_suite());
  srunner_add_suite(string_runner, sscanf_suite());

  int failed = 0;
  srunner_run_all(string_runner, CK_ENV);

  failed = srunner_ntests_failed(string_runner);
  srunner_free(string_runner);
  unsetenv("CK_DEFAULT_TIMEOUT");

  printf("\nПровалено %d тестов..\n", failed);
  return 0;
}
