#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

#define SIZE 512

START_TEST(sscanf_EOF1) {
  char spec[] = "%d";
  char str[] = "        ";

  int res1 = s21_sscanf(str, spec, 0);
  int res2 = sscanf(str, spec, 100);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_EOF2) {
  char spec[] = "%d ";
  char str[] = "             ";
  int a1 = 0, a2 = 0;

  int res1 = s21_sscanf(str, spec, &a1);
  int res2 = sscanf(str, spec, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_just_chars) {
  char spec[] = "%c%c%c%c";
  char str[] = "qwer";
  int a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int res1 = s21_sscanf(str, spec, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, spec, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_diff_chars) {
  char spec[] = "%c %c %c      %c";
  char str[] = "7 b 2   a           ";
  int a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int res1 = s21_sscanf(str, spec, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, spec, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_d_ints) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1998 31 3008 5000";
  const char spec[] = "%d %d %d %d";

  int res1 = s21_sscanf(str, spec, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, spec, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_ld_ints) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char spec[] = "%ld %ld %ld %ld";
  const char str[] = "111 222 333 444";

  int res1 = s21_sscanf(str, spec, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, spec, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  const char str[] = "53.1 -4.1135 411231.3 +2.0001";
  const char spec[] = "%*f %f %f %f";

  int res1 = s21_sscanf(str, spec, &a1, &b1, &c1);
  int res2 = sscanf(str, spec, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_long_floats) {
  long double a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0, d1 = 1, d2 = 0;

  const char str[] = "53.1 -4.1135 41.3333 +2.0001";
  const char spec[] = "%Lf %Lf %Lf %Lf";

  int res1 = s21_sscanf(str, spec, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, spec, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_witdth_ints1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "6666 18 1005 777555";
  const char fstr[] = "%1lld %3lld %1lld %4lld";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_witdth_ints2) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1488";
  const char fstr[] = "%1lld %1lld %1lld %1lld";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_witdth_ints3) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "100000000000000001";
  const char fstr[] = "%1lld%2lld%3lld%4lld";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_witdth_ints4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1488";
  const char fstr[] = "%1lld %1lld %1lld %20lld";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_astrwidth_ints) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  const char str[] = "1112223334 0 098765432100 0 123456 1";
  const char fstr[] = "%*d %lld %*d %lld %*d %lld";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_strs1) {
  char s1[SIZE] = {'\0'};
  char s2[SIZE] = {'\0'};
  char s3[SIZE] = {'\0'};
  char s4[SIZE] = {'\0'};

  char s5[SIZE] = {'\0'};
  char s6[SIZE] = {'\0'};
  char s7[SIZE] = {'\0'};
  char s8[SIZE] = {'\0'};

  const char str[] = "linux microsoft macos ubuntu";
  const char fstr[] = "%s %s %s %s";

  int res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(sscanf_strs4) {
  char s1[SIZE] = {'\0'};
  char s2[SIZE] = {'\0'};
  char s3[SIZE] = {'\0'};
  char s4[SIZE] = {'\0'};

  char s5[SIZE] = {'\0'};
  char s6[SIZE] = {'\0'};
  char s7[SIZE] = {'\0'};
  char s8[SIZE] = {'\0'};

  const char str[] = "qwerty\tqwerty\tqwerty\tqwerty";
  const char fstr[] = "%1s%1s%1s%1s";

  int res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(sscanf_ptr) {
  char *str = "0x0080CD20";
  char *fstr = "%p";
  long res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_ptrs1) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xF2FF 0xA5AA 0x1488 0xDDE8FG";
  const char fstr[] = "%p %p %p %p";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_i1) {
  char *str = "555";
  char *fstr = "%i";
  int res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_i2) {
  char *str = "-999";
  char *fstr = "%i";
  int res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_i3) {
  char *str = "666";
  char *fstr = "%*i";
  ck_assert_int_eq(sscanf(str, fstr), s21_sscanf(str, fstr));
}
END_TEST

START_TEST(sscanf_i4) {
  char *str = "999";
  char *fstr = "%6i";
  int res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_short_int) {
  char *str = "-111";
  char *fstr = "%hi";
  short int res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_long_int) {
  char *str = "105345279";
  char *fstr = "%li";
  long res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_u1) {
  char *str = "111";
  char *fstr = "%u";
  unsigned int res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_u2) {
  char *str = "1488";
  char *fstr = "%6u";
  unsigned int res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_u3) {
  char *str = "1488";
  char *fstr = "%*u";
  ck_assert_int_eq(sscanf(str, fstr), s21_sscanf(str, fstr));
}
END_TEST

START_TEST(sscanf_some_u) {
  char *str = "115567435 054241 -999";
  char *fstr = "%u %u %u";
  unsigned a1, a2, b1, b2, c1, c2;

  ck_assert_int_eq(sscanf(str, fstr, &a1, &b1, &c1),
                   s21_sscanf(str, fstr, &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_short_u) {
  char *str = "-111";
  char *fstr = "%hu";
  unsigned short res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_long_u) {
  char *str = "105345279";
  char *fstr = "%lu";
  unsigned long res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_oct1) {
  char *str = "77";
  char *fstr = "%o";
  unsigned res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_oct2) {
  char *str = "77";
  char *fstr = "%o";
  unsigned res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_oct3) {
  char *str = "63";
  char *fstr = "%6o";
  unsigned res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_oct4) {
  char *str = "125";
  char *fstr = "%*o";
  ck_assert_int_eq(sscanf(str, fstr), s21_sscanf(str, fstr));
}
END_TEST

START_TEST(sscanf_some_oct) {
  char *str = "57234 7000 -432";
  char *fstr = "%o %o %o";
  unsigned a1, a2, b1, b2, c1, c2;
  ck_assert_int_eq(sscanf(str, fstr, &a1, &b1, &c1),
                   s21_sscanf(str, fstr, &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_short_oct) {
  char *str = "513";
  char *fstr = "%ho";
  unsigned short res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_long_oct) {
  char *str = "234567012";
  char *fstr = "%lo";
  unsigned long res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_small_x1) {
  char *str = "0xFF";
  char *fstr = "%x";
  unsigned res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_some_smallx) {
  char *str = "0xC40 0x4D2 0xE6F";
  char *fstr = "%x %x %x";
  unsigned a1, a2, b1, b2, c1, c2;
  ck_assert_int_eq(sscanf(str, fstr, &a1, &b1, &c1),
                   s21_sscanf(str, fstr, &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_short_x) {
  char *str = "-0xAEF";
  char *fstr = "%hx";
  unsigned short res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_long_x) {
  char *str = "0x7FFFFFFFFFFFFFFF";
  char *fstr = "%lx";
  unsigned long res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_large_x1) {
  char *str = "0xFF";
  char *fstr = "%X";
  unsigned res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_large_x2) {
  char *str = "0x08F1";
  char *fstr = "%6X";
  unsigned res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_some_largex) {
  char *str = "0xC40 0x4D2 0xE6F";
  char *fstr = "%X %X %X";
  unsigned a1, a2, b1, b2, c1, c2;
  ck_assert_int_eq(sscanf(str, fstr, &a1, &b1, &c1),
                   s21_sscanf(str, fstr, &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_short_lx) {
  char *str = "-0xAEF";
  char *fstr = "%hX";
  unsigned short res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_long_lx) {
  char *str = "0x7FFFFFFFFFFFFFFF";
  char *fstr = "%lX";
  unsigned long res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_small_g1) {
  char *str = "66.6";
  char *fstr = "%g";
  float res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_float_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_small_g2) {
  char *str = "123.4";
  char *fstr = "%6g";
  float res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_float_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_small_g3) {
  char *str = "4.19e-3";
  char *fstr = "%*g";
  ck_assert_int_eq(sscanf(str, fstr), s21_sscanf(str, fstr));
}
END_TEST

START_TEST(sscanf_some_small_g) {
  char *str = "12345.6789 4.20e3 -9876.54321";
  char *fstr = "%g %g %g";
  float a1, a2, b1, b2, c1, c2;
  ck_assert_int_eq(sscanf(str, fstr, &a1, &b1, &c1),
                   s21_sscanf(str, fstr, &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_ldouble_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_small_Lg) {
  char *str = "-4e20";
  char *fstr = "%Lg";
  long double res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_ldouble_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_some_G1) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "1.4441 1.e+4 -3.31e-4 0.444e-5";
  const char fstr[] = "%G %G %G %G";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_some_G2) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "inf 1.e+4 NaN 0.444e-5";
  const char fstr[] = "%G %G %G %G";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_ldouble_infinite(a1);
  ck_assert_ldouble_infinite(a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_float_nan(c1);
  ck_assert_float_nan(c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_exp1) {
  char *str = "66.6";
  char *fstr = "%e";
  float res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_float_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_exp2) {
  char *str = "123.4";
  char *fstr = "%6e";
  float res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_float_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_exp3) {
  char *str = "4.19e-3";
  char *fstr = "%*e";
  ck_assert_int_eq(sscanf(str, fstr), s21_sscanf(str, fstr));
}
END_TEST

START_TEST(sscanf_some_exp) {
  char *str = "12345.6789 4.20e3 -9876.54321";
  char *fstr = "%e %e %e";
  float a1, a2, b1, b2, c1, c2;
  ck_assert_int_eq(sscanf(str, fstr, &a1, &b1, &c1),
                   s21_sscanf(str, fstr, &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_ldouble_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_long_exp) {
  char *str = "-4e20";
  char *fstr = "%Le";
  long double res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_ldouble_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_double_exp) {
  char *str = "28e+11";
  char *fstr = "%le";
  double res1, res2;
  ck_assert_int_eq(sscanf(str, fstr, &res1), s21_sscanf(str, fstr, &res2));
  ck_assert_double_eq(res1, res2);
}
END_TEST

Suite *sscanf_suite(void) {
  Suite *suite = suite_create("s21_sscanf");
  TCase *tCase = tcase_create("s21_sscanf_tcase");

  tcase_add_test(tCase, sscanf_EOF1);
  tcase_add_test(tCase, sscanf_EOF2);
  tcase_add_test(tCase, sscanf_just_chars);
  tcase_add_test(tCase, sscanf_diff_chars);
  tcase_add_test(tCase, sscanf_d_ints);
  tcase_add_test(tCase, sscanf_ld_ints);
  tcase_add_test(tCase, sscanf_floats);
  tcase_add_test(tCase, sscanf_long_floats);
  tcase_add_test(tCase, sscanf_witdth_ints1);
  tcase_add_test(tCase, sscanf_witdth_ints2);
  tcase_add_test(tCase, sscanf_witdth_ints3);
  tcase_add_test(tCase, sscanf_witdth_ints4);
  tcase_add_test(tCase, sscanf_astrwidth_ints);
  tcase_add_test(tCase, sscanf_strs1);
  tcase_add_test(tCase, sscanf_strs4);
  tcase_add_test(tCase, sscanf_ptr);
  tcase_add_test(tCase, sscanf_ptrs1);
  tcase_add_test(tCase, sscanf_i1);
  tcase_add_test(tCase, sscanf_i2);
  tcase_add_test(tCase, sscanf_i3);
  tcase_add_test(tCase, sscanf_i4);
  tcase_add_test(tCase, sscanf_short_int);
  tcase_add_test(tCase, sscanf_long_int);
  tcase_add_test(tCase, sscanf_u1);
  tcase_add_test(tCase, sscanf_u2);
  tcase_add_test(tCase, sscanf_u3);
  tcase_add_test(tCase, sscanf_some_u);
  tcase_add_test(tCase, sscanf_short_u);
  tcase_add_test(tCase, sscanf_long_u);
  tcase_add_test(tCase, sscanf_oct1);
  tcase_add_test(tCase, sscanf_oct2);
  tcase_add_test(tCase, sscanf_oct3);
  tcase_add_test(tCase, sscanf_oct4);
  tcase_add_test(tCase, sscanf_some_oct);
  tcase_add_test(tCase, sscanf_short_oct);
  tcase_add_test(tCase, sscanf_long_oct);
  tcase_add_test(tCase, sscanf_small_x1);
  tcase_add_test(tCase, sscanf_some_smallx);
  tcase_add_test(tCase, sscanf_short_x);
  tcase_add_test(tCase, sscanf_long_x);
  tcase_add_test(tCase, sscanf_large_x1);
  tcase_add_test(tCase, sscanf_large_x2);
  tcase_add_test(tCase, sscanf_some_largex);
  tcase_add_test(tCase, sscanf_short_lx);
  tcase_add_test(tCase, sscanf_long_lx);
  tcase_add_test(tCase, sscanf_small_g1);
  tcase_add_test(tCase, sscanf_small_g2);
  tcase_add_test(tCase, sscanf_small_g3);
  tcase_add_test(tCase, sscanf_small_g1);
  tcase_add_test(tCase, sscanf_some_small_g);
  tcase_add_test(tCase, sscanf_small_Lg);
  tcase_add_test(tCase, sscanf_some_G1);
  tcase_add_test(tCase, sscanf_some_G2);
  tcase_add_test(tCase, sscanf_exp1);
  tcase_add_test(tCase, sscanf_exp2);
  tcase_add_test(tCase, sscanf_exp3);
  tcase_add_test(tCase, sscanf_some_exp);
  tcase_add_test(tCase, sscanf_long_exp);
  tcase_add_test(tCase, sscanf_double_exp);

  tcase_set_tags(tCase, "sscanf all");
  suite_add_tcase(suite, tCase);
  return suite;
}
