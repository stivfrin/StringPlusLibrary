#ifndef STRING_TEST_H
#define STRING_TEST_H

#include <check.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../s21_string.h"

#define LOREM_IPSUM                                                           \
  {                                                                           \
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, ",              \
        "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", \
        "Ut enim ad minim veniam, quis nostrud exercitation ullamco",         \
        "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure "   \
        "dolor",                                                              \
        "in reprehenderit in voluptate velit esse cillum",                    \
        "dolore eu fugiat nulla pariatur.",                                   \
        "Excepteur sint occaecat cupidatat non proident",                     \
        "sunt in culpa qui officia deserunt mollit anim id est laborum."      \
  }

#define RANDOM_BYTES \
  { 'H', 21, '1', 0, '\r', '0', -1 }

Suite* memchr_suite(void);
Suite* memcmp_suite(void);
Suite* memcpy_suite(void);
Suite* memset_suite(void);
Suite* strchr_suite(void);
Suite* strcspn_suite(void);
Suite* strerror_suite(void);
Suite* strlen_suite(void);
Suite* strncat_suite(void);
Suite* strncmp_suite(void);
Suite* strncpy_suite(void);
Suite* strpbrk_suite(void);
Suite* strrchr_suite(void);
Suite* strstr_suite(void);
Suite* strtok_suite(void);

Suite* to_upper_suite(void);
Suite* to_lower_suite(void);
Suite* insert_suite(void);
Suite* trim_suite(void);

Suite* sprintf_suite(void);
Suite* sscanf_suite(void);

#endif /* STRING_TEST_H */