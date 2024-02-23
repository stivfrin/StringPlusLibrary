#include "all_tests.h"

#define INT_SAMPLES \
  { 'Y', 48, 256, 0, -1, -1050, INT_MAX, INT_MIN }
#define FLOAT_SAMPLES \
  { 3.14, 0, 1.9876543210, 21987654321.987654321, NAN, INFINITY, -INFINITY }

#define BUF_MAX 300
#define BUF_LRS 6

#define APPEND_BUFFER_WITH(parameter, ln)             \
  int max_##ln = sizeof(parameter) / sizeof(char *);  \
  for (int i_##ln = 0; i_##ln < max_##ln; i_##ln++) { \
    strncpy(buffer[ln], buffer[ln - 1], BUF_MAX);     \
    strcat(buffer[ln], parameter[i_##ln]);

#define ITERATE_PARAMETERS         \
  APPEND_BUFFER_WITH(flags, 1)     \
  APPEND_BUFFER_WITH(flags, 2)     \
  APPEND_BUFFER_WITH(width, 3)     \
  APPEND_BUFFER_WITH(precision, 4) \
  APPEND_BUFFER_WITH(length, 5)

#define ITERATION_END \
  }                   \
  }                   \
  }                   \
  }                   \
  }

void print_formats();
void count_samples();
void setup_auto();
void teardown_auto();
void setup_manual();

enum SpecTypes {
  for_c,
  for_d,
  for_i,
  for_e,
  for_E,
  for_f,
  for_g,
  for_G,
  for_o,
  for_s,
  for_u,
  for_x,
  for_X,
  for_p,
  for_n,
  SPEC_MAX
};

static char specifiers[SPEC_MAX] = "cdieEfgGosuxXpn";
static char *flags[] = {"", "-", "+", " ", "0", "#"};
static char *width[] = {"", "0", "80", "99999999999999999999", "*", "-1"};
static char *precision[] = {"", ".", ".0", ".10", ".9999999", ".*", ".."};
static char *length[] = {"", "h", "l", "L"};

static char *title[SPEC_MAX] = {
    "\"%p\" as c // chr\t : %%", "\"%p\" as d // s-d\t : %%",
    "\"%p\" as i // s-d\t : %%", "\"%p\" as e // f-e\t : %%",
    "\"%p\" as E // f-E\t : %%", "\"%p\" as f // f-d\t : %%",
    "\"%p\" as g // m-d\t : %%", "\"%p\" as G // m-d\t : %%",
    "\"%p\" as o // u-8\t : %%", "\"%p\" as s // str\t : %%",
    "\"%p\" as u // u-d\t : %%", "\"%p\" as x // u-x\t : %%",
    "\"%p\" as X // u-X\t : %%", "\"%p\" as p // ptr\t : %%",
    "\"%p\" as n // u%%n\t : %%"};

static FILE *format_storage = NULL;
static int pos_in_file[SPEC_MAX] = {0};
static int num_formats[SPEC_MAX] = {0};
static int num_samples[SPEC_MAX] = {0};

static long int int_samples[] = INT_SAMPLES;
static long double float_samples[] = FLOAT_SAMPLES;
static char *str_samples[] = LOREM_IPSUM;

static char origin[BUF_MAX];
static char home[BUF_MAX];

// START_TEST(auto_c)
// {
//     fseek(format_storage, pos_in_file[for_c], SEEK_SET);
//     int format_num = _i / num_samples[for_c];
//     while (format_num)
//     {
//         char c = fgetc(format_storage);
//         if (c == '\n') format_num--;
//     }
//     char format[BUF_MAX];
//     fgets(format, BUF_MAX, format_storage);

//     char samp = int_samples[_i % num_samples[for_c]];
//     char str1[500], str2[500];
//     int ref = sprintf(str1, format, &samp, samp);

// }
// END_TEST

void setup_manual() {
  memset(origin, 0, BUF_MAX);
  memset(home, 0, BUF_MAX);
}

START_TEST(print_c_1) {
  char *format = "|%-3c|";
  char ch = 'w';
  int r1 = sprintf(origin, format, ch);
  int r2 = s21_sprintf(home, format, ch);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_c_2) {
  char *format = "|%*c|";
  char ch = 'w';
  int sample = 10;
  int r1 = sprintf(origin, format, sample, ch);
  int r2 = s21_sprintf(home, format, sample, ch);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_c_3)  // ОШИБКА. Но если сделать 5lc, то ок
{
  char *format = "|%6lc|";
  unsigned long ch = 'w';
  int r1 = sprintf(origin, format, ch);
  int r2 = s21_sprintf(home, format, ch);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_c_4) {
  char *format = "|%-05c|";
  char ch = 'w';
  int r1 = sprintf(origin, format, ch);
  int r2 = s21_sprintf(home, format, ch);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_d_1)  // ОШИБКА
{
  char *format = "|%0.0d|";
  int number = 12345678;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_d_2) {
  char *format = "|%8d|";
  long int number = -50;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_d_3) {
  char *format = "|%-.2d|";
  int number = -50;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_d_4) {
  char *format = "|%d|";
  int number = -50;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_d_5) {
  char *format = "|%08d|";
  int number = 10;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_1) {
  char *format = "|%9.7i|";
  int number = 58;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_2) {
  char *format = "|%010i|";
  int number = -65;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_3) {
  char *format = "|%i|";
  int number = -0b1111101;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_4) {
  char *format = "|%-8i|";
  int number = 0b11110011;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_5)  // ОШИБКА: 243 в 16 - чной записи.
{
  char *format = "|%.8i|";
  int number = 0xf3;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_6) {
  char *format = "|%+i|";
  int number = -0xf3;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_7) {
  char *format = "|%+li|";
  int number = 14228934;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_8)  // ОШИБКА
{
  char *format = "|%hi|";
  int number = 472;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_9)  // ОШИБКА
{
  char *format = "|%0hi|";
  int number = -472;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_10) {
  char *format = "|%-*i|";
  int number = -472;
  int sample = 5;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_i_11)  // И ОШИБКА, И НЕТ
{
  char *format = "|%+5.*i|";
  int number = -472;
  int sample = 5;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_e_1) {
  char *format = "|%e|";
  double number = 50.11;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_e_2) {
  char *format = "|%3.7e|";
  double number = -50.112;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_e_3) {
  char *format = "|%-2.10e|";
  double number = 9.18;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_e_4) {
  char *format = "|% 5e|";
  double number = 9.18;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_e_5) {
  char *format = "|%+5e|";
  double number = 4.32;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_e_6) {
  char *format = "|%.0e|";
  double number = 432.55;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_e_7) {
  char *format = "|%#e|";
  double number = 33.00;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_e_8) {
  char *format = "|%5.*e|";
  double number = -321.06;
  int sample = 4;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_e_9) {
  char *format = "|%-09.2e|";
  double number = 0.0;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_E_1) {
  char *format = "|%5E|";
  double number = 15.76;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(print_E_2) {
  char *format = "|%-2.10E|";
  double number = 15.76;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_E_3) {
  char *format = "|%.8E|";
  double number = -555.6254;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_E_4)  // ОШИБКА: недостаток пробела
{
  char *format = "|%+15E|";
  double number = -555.6254;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_E_5) {
  char *format = "|%15.10E|";
  double number = -555.123456789;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_E_6) {
  char *format = "|%#E|";
  double number = 123.456;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_E_7) {
  char *format = "|%5.*E|";
  double number = -123.456;
  int sample = 4;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_1) {
  char *format = "|%5f|";
  double number = 123.456;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_2) {
  char *format = "|%5.5f|";
  double number = 123.456;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_3) {
  char *format = "|%-8.15f|";
  double number = 52.16;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_4) {
  char *format = "|%-.15f|";
  double number = 3.13;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_5) {
  char *format = "|% 15f|";
  double number = 12.88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_6) {
  char *format = "|%+7f|";
  double number = 12.88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_7) {
  char *format = "|%013f|";
  double number = -12.88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_8) {
  char *format = "|%#f|";
  double number = 256.0;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_9) {
  char *format = "|%3.*f|";
  double number = -256.123;
  int sample = 4;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_f_10)  // ОШИБКА
{
  char *format = "|%13Lf|";
  long double number = 24.528;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_g_1)  // ОШИБКА
{
  char *format = "|%5g|";
  double number = 24.528;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_g_2) {
  char *format = "|%5.5g|";
  double number = -24.528;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_g_3) {
  char *format = "|%-5.15g|";
  double number = 13.58;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_g_4) {
  char *format = "|%.15g|";
  double number = 13.58;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_g_5)  // ОШИБКА
{
  char *format = "|% 5g|";
  double number = 143.5;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_g_6)  // ОШИБКА
{
  char *format = "|%+5g|";
  double number = 23.545;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_g_7)  // ОШИБКА
{
  char *format = "|%015g|";
  double number = -58.64;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_g_8) {
  char *format = "|%#g|";
  double number = 58.00;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_g_10) {
  char *format = "|%-0.0g|";
  double number = 58.125;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_G_1)  // ОШИБКА
{
  char *format = "|%5G|";
  double number = 58.125;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_G_2)  // ОШИБКА
{
  char *format = "|%5.6G|";
  double number = -58.125;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_G_3) {
  char *format = "|%-5.6G|";
  double number = 114.125;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_G_5) {
  char *format = "|% 6G|";
  double number = 145.215;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_G_6) {
  char *format = "|%+8G|";
  double number = -1555.215;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_G_7) {
  char *format = "|%080G|";
  double number = -1555.215;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_G_8) {
  char *format = "|%#G|";
  double number = 255.0;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_G_9) {
  char *format = "|%6.*G|";
  double number = -987.654;
  int sample = 6;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_o_1)  // ОШИБКА
{
  char *format = "|%15o|";
  int number = -148;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_o_2) {
  char *format = "|%-15o|";
  int number = 148;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_o_3)  // ОШИБКА
{
  char *format = "|%+o|";
  int number = 18;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_o_4)  // ОШИБКА
{
  char *format = "|% o|";
  int number = 88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_o_5) {
  char *format = "|%.8o|";
  int number = 123;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_o_6) {
  char *format = "|%ho|";
  unsigned short number = 123;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_o_7) {
  char *format = "|%lo|";
  long int number = 123;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_o_8) {
  char *format = "|%8.*o|";
  int number = 123467;
  int sample = 4;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_o_9) {
  char *format = "|%0.0o|";
  int number = 0;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_s_1)  // ERROR
{
  char *format = "|%30s|";
  char str[] = "nebunarnaya";
  int r1 = sprintf(origin, format, str);
  int r2 = s21_sprintf(home, format, str);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_s_2)  // ERROR
{
  char *format = "|%-14s|";
  char str[] = "nebunarnaya";
  int r1 = sprintf(origin, format, str);
  int r2 = s21_sprintf(home, format, str);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_s_3)  // ERROR
{
  char *format = "|%.6s|";
  char str[] = "yaponchik";
  int r1 = sprintf(origin, format, str);
  int r2 = s21_sprintf(home, format, str);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_s_4)  // ERROR
{
  char *format = "|%7.6s|";
  char str[] = "lomal steklo";
  int r1 = sprintf(origin, format, str);
  int r2 = s21_sprintf(home, format, str);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_s_5)  // ERROR
{
  char *format = "|%0.6s| |%4s|";
  char str1[] = "lomal steklo";
  char str2[] = "memasiki";
  int r1 = sprintf(origin, format, str1, str2);
  int r2 = s21_sprintf(home, format, str1, str2);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_u_1) {
  char *format = "|%-8u|";
  unsigned int number = 148;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_u_2)  // ERROR
{
  char *format = "|%+u|";
  unsigned int number = 111;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_u_3) {
  char *format = "|%.5u|";
  unsigned int number = 187;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_u_4)  // ERROR
{
  char *format = "|% u|";
  unsigned int number = 156;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_u_5) {
  char *format = "|%hu|";
  unsigned short number = 88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_u_6) {
  char *format = "|%lu|";
  unsigned long number = 88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_u_7) {
  char *format = "|%*.5u|";
  unsigned number = 12345;
  int sample = 4;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_u_8) {
  char *format = "|%0.0u|";
  int number = 0;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_x_1)  // ERROR
{
  char *format = "|%15x|";
  int number = -98;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_x_2) {
  char *format = "|%-4x|";
  int number = 198;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_x_3)  // ERROR
{
  char *format = "|%+x|";
  int number = 198;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_x_4)  // ERROR
{
  char *format = "|% x|";
  int number = 188;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_x_5) {
  char *format = "|%.8x|";
  int number = 88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_x_6) {
  char *format = "|%hx|";
  unsigned short number = 88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_x_7) {
  char *format = "|%lx|";
  long number = 123;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_x_8) {
  char *format = "|%6.*x|";
  int number = 123;
  int sample = 4;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_x_9) {
  char *format = "|%-0.0x|";
  int number = 0;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_X_1)  // ERROR
{
  char *format = "|%15X|";
  int number = -43;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_X_2)  // ERROR
{
  char *format = "|%-4X|";
  int number = -43;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_X_3)  // ERROR
{
  char *format = "|%+X|";
  int number = 200;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_X_4)  // ERROR
{
  char *format = "|% X|";
  int number = 50;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_X_5) {
  char *format = "|%.8X|";
  int number = 50;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_X_6) {
  char *format = "|%hX|";
  unsigned short number = 50;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_X_7) {
  char *format = "|%lX|";
  long number = 50;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_X_8)  // ERROR
{
  char *format = "|%*.5X|";
  int number = -52;
  int sample = 3;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_p_1)  // ERROR
{
  char *format = "|%15p|";
  int number = -88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_p_2)  // ERROR
{
  char *format = "|%-10p|";
  int number = -88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_p_3)  // ERROR
{
  char *format = "|%04p|";
  int number = -88;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_p_4)  // ERROR
{
  char *format = "|%.7p|";
  int number = 100;
  int r1 = sprintf(origin, format, number);
  int r2 = s21_sprintf(home, format, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

// START_TEST(print_p_5)       // ERROR
// {
//   char *format = "|%hp|";
//   short number = 100;
//   int r1 = sprintf(origin, format, number);
//   int r2 = s21_sprintf(home, format, number);
//   ck_assert_pstr_eq(origin, home);
//   ck_assert_int_eq(r1, r2);
// }

// START_TEST(print_p_6)       // ERROR
// {
//   char *format = "|%lp|";
//   long number = 100;
//   int r1 = sprintf(origin, format, number);
//   int r2 = s21_sprintf(home, format, number);
//   ck_assert_pstr_eq(origin, home);
//   ck_assert_int_eq(r1, r2);
// }

START_TEST(print_p_7) {
  char *format = "|%3.*p|";
  int number = 123456;
  int sample = 3;
  int r1 = sprintf(origin, format, sample, number);
  int r2 = s21_sprintf(home, format, sample, number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

START_TEST(print_n_1) {
  char *format = "|150 %n 150 150|";
  int number = 0;
  int s21_number = 0;
  int r1 = sprintf(origin, format, &number);
  int r2 = s21_sprintf(home, format, &s21_number);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(number, s21_number);
}

START_TEST(print_percent_1) {
  char *format = "|150 150 %%|";
  int r1 = sprintf(origin, format);
  int r2 = s21_sprintf(home, format);
  ck_assert_pstr_eq(origin, home);
  ck_assert_int_eq(r1, r2);
}

void setup_auto() { format_storage = fopen("formats.txt", "r"); }
void teardown_auto() {
  fclose(format_storage);
  format_storage = NULL;
}

Suite *sprintf_suite(void) {
  Suite *suite = suite_create("sprintf");
  TCase *case_auto = tcase_create("case_auto");
  TCase *case_manual = tcase_create("case_manual");

  // FILE* fp = NULL;
  // fp = fopen("formats.txt", "r");
  // if (fp) fclose(fp);
  // else print_formats();

  // tcase_add_checked_fixture(case_auto, setup_auto, teardown_auto);
  // count_samples();
  // tcase_add_loop_test(case_auto, auto_c,
  //                     0, num_formats[for_c] * num_samples[for_c]);

  tcase_add_checked_fixture(case_manual, setup_manual, NULL);

  tcase_add_test(case_manual, print_c_1);
  tcase_add_test(case_manual, print_c_2);
  tcase_add_test(case_manual, print_c_3);
  tcase_add_test(case_manual, print_c_4);

  tcase_add_test(case_manual, print_d_1);
  tcase_add_test(case_manual, print_d_2);
  tcase_add_test(case_manual, print_d_3);
  tcase_add_test(case_manual, print_d_4);
  tcase_add_test(case_manual, print_d_5);

  tcase_add_test(case_manual, print_i_1);
  tcase_add_test(case_manual, print_i_2);
  tcase_add_test(case_manual, print_i_3);
  tcase_add_test(case_manual, print_i_4);
  tcase_add_test(case_manual, print_i_5);
  tcase_add_test(case_manual, print_i_6);
  tcase_add_test(case_manual, print_i_7);
  tcase_add_test(case_manual, print_i_8);
  tcase_add_test(case_manual, print_i_9);
  tcase_add_test(case_manual, print_i_10);
  tcase_add_test(case_manual, print_i_11);

  tcase_add_test(case_manual, print_e_1);
  tcase_add_test(case_manual, print_e_2);
  tcase_add_test(case_manual, print_e_3);
  tcase_add_test(case_manual, print_e_4);
  tcase_add_test(case_manual, print_e_5);
  tcase_add_test(case_manual, print_e_6);
  tcase_add_test(case_manual, print_e_7);
  tcase_add_test(case_manual, print_e_8);
  tcase_add_test(case_manual, print_e_9);

  tcase_add_test(case_manual, print_E_1);
  tcase_add_test(case_manual, print_E_2);
  tcase_add_test(case_manual, print_E_3);
  tcase_add_test(case_manual, print_E_4);
  tcase_add_test(case_manual, print_E_5);
  tcase_add_test(case_manual, print_E_6);
  tcase_add_test(case_manual, print_E_7);

  tcase_add_test(case_manual, print_f_1);
  tcase_add_test(case_manual, print_f_2);
  tcase_add_test(case_manual, print_f_3);
  tcase_add_test(case_manual, print_f_4);
  tcase_add_test(case_manual, print_f_5);
  tcase_add_test(case_manual, print_f_6);
  tcase_add_test(case_manual, print_f_7);
  tcase_add_test(case_manual, print_f_8);
  tcase_add_test(case_manual, print_f_9);
  tcase_add_test(case_manual, print_f_10);

  tcase_add_test(case_manual, print_g_1);
  tcase_add_test(case_manual, print_g_2);
  tcase_add_test(case_manual, print_g_3);
  tcase_add_test(case_manual, print_g_4);
  tcase_add_test(case_manual, print_g_5);
  tcase_add_test(case_manual, print_g_6);
  tcase_add_test(case_manual, print_g_7);
  tcase_add_test(case_manual, print_g_8);
  tcase_add_test(case_manual, print_g_10);

  tcase_add_test(case_manual, print_G_1);
  tcase_add_test(case_manual, print_G_2);
  tcase_add_test(case_manual, print_G_3);
  tcase_add_test(case_manual, print_G_5);
  tcase_add_test(case_manual, print_G_6);
  tcase_add_test(case_manual, print_G_7);
  tcase_add_test(case_manual, print_G_8);
  tcase_add_test(case_manual, print_G_9);

  tcase_add_test(case_manual, print_o_1);
  tcase_add_test(case_manual, print_o_2);
  tcase_add_test(case_manual, print_o_3);
  tcase_add_test(case_manual, print_o_4);
  tcase_add_test(case_manual, print_o_5);
  tcase_add_test(case_manual, print_o_6);
  tcase_add_test(case_manual, print_o_7);
  tcase_add_test(case_manual, print_o_8);
  tcase_add_test(case_manual, print_o_9);

  tcase_add_test(case_manual, print_s_1);
  tcase_add_test(case_manual, print_s_2);
  tcase_add_test(case_manual, print_s_3);
  tcase_add_test(case_manual, print_s_4);
  tcase_add_test(case_manual, print_s_5);

  tcase_add_test(case_manual, print_u_1);
  tcase_add_test(case_manual, print_u_2);
  tcase_add_test(case_manual, print_u_3);
  tcase_add_test(case_manual, print_u_4);
  tcase_add_test(case_manual, print_u_5);
  tcase_add_test(case_manual, print_u_6);
  tcase_add_test(case_manual, print_u_7);
  tcase_add_test(case_manual, print_u_8);

  tcase_add_test(case_manual, print_x_1);
  tcase_add_test(case_manual, print_x_2);
  tcase_add_test(case_manual, print_x_3);
  tcase_add_test(case_manual, print_x_4);
  tcase_add_test(case_manual, print_x_5);
  tcase_add_test(case_manual, print_x_6);
  tcase_add_test(case_manual, print_x_7);
  tcase_add_test(case_manual, print_x_8);
  tcase_add_test(case_manual, print_x_9);

  tcase_add_test(case_manual, print_X_1);
  tcase_add_test(case_manual, print_X_2);
  tcase_add_test(case_manual, print_X_3);
  tcase_add_test(case_manual, print_X_4);
  tcase_add_test(case_manual, print_X_5);
  tcase_add_test(case_manual, print_X_6);
  tcase_add_test(case_manual, print_X_7);
  tcase_add_test(case_manual, print_X_8);

  tcase_add_test(case_manual, print_p_1);
  tcase_add_test(case_manual, print_p_2);
  tcase_add_test(case_manual, print_p_3);
  tcase_add_test(case_manual, print_p_4);
  // tcase_add_test(case_manual, print_p_5);
  // tcase_add_test(case_manual, print_p_6);
  tcase_add_test(case_manual, print_p_7);

  tcase_add_test(case_manual, print_n_1);

  tcase_add_test(case_manual, print_percent_1);

  tcase_set_tags(case_auto, "sprintf all auto");
  tcase_set_tags(case_manual, "sprintf all manual");
  suite_add_tcase(suite, case_auto);
  suite_add_tcase(suite, case_manual);

  return suite;
}

void print_formats() {
  format_storage = fopen("formats.txt", "w");
  if (format_storage) {
    for (int spec_type = 0; spec_type < SPEC_MAX; spec_type++) {
      char buffer[BUF_LRS][BUF_MAX];
      memset(*buffer, 0, BUF_MAX);

      pos_in_file[spec_type] = ftell(format_storage);

      strcat(*buffer, title[spec_type]);
      int spec_pos = strlen(*buffer) - 1;

      ITERATE_PARAMETERS {
        char *output = buffer[BUF_LRS - 1];
        int spec_end = strlen(output);
        output[spec_end++] = specifiers[spec_type];
        strcat(output, " \"");
        strncat(output, output + spec_pos, spec_end - spec_pos);
        strcat(output, "\"");

        fprintf(format_storage, "%s\n", output);
        num_formats[spec_type]++;
      }
      ITERATION_END
    }
    fclose(format_storage);
    format_storage = NULL;
  }
}

void count_samples() {
  num_samples[for_c] = sizeof(int_samples) / sizeof(int);
  num_samples[for_d] = num_samples[for_c];
  num_samples[for_i] = num_samples[for_c];
  num_samples[for_e] = sizeof(float_samples) / sizeof(long double);
  num_samples[for_E] = num_samples[for_e];
  num_samples[for_f] = num_samples[for_e];
  num_samples[for_g] = num_samples[for_e];
  num_samples[for_G] = num_samples[for_e];
  num_samples[for_o] = num_samples[for_c];
  num_samples[for_s] = sizeof(str_samples) / sizeof(char *);
  num_samples[for_u] = num_samples[for_c];
  num_samples[for_x] = num_samples[for_c];
  num_samples[for_X] = num_samples[for_c];
  num_samples[for_p] = num_samples[for_s];
  num_samples[for_n] = 1;
}
