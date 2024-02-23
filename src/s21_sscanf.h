#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <math.h>
#include <stdarg.h>

#include "s21_string.h"

#define LLONG_MAX 0x7fffffffffffffff
#define LLONG_MIN (-LLONG_MAX - 1LL)
#define ULLONG_MAX 0xffffffffffffffff
#define INT_MAX 0x7fffffff

typedef enum {
  spec_c,
  spec_d,
  spec_i,
  spec_e,
  spec_E,
  spec_f,
  spec_g,
  spec_G,
  spec_o,
  spec_s,
  spec_u,
  spec_x,
  spec_X,
  spec_p,
  spec_n,
  spec_unknown
} sspecs;

typedef enum lens {
  len_none,
  len_h,
  len_l,
  len_L,
} lens;

typedef struct {
  sspecs spec;
  int width;
  lens len;
  bool skip;
} specifier;

int s21_sscanf(const char *str, const char *format, ...);
specifier specifier_scanf(char **format);
bool true_digit(char c, int base);
s21_size_t converter_digit(char c, int base);
bool search_strstr(char **str, char *pat);
char to_lower(char c);
int width_processing(char **f_str);
bool big_parse(specifier spec, char **str, va_list ap, int *res, char *start);

bool str_parse(specifier spec, char **str, va_list ap);

bool int_parse(specifier spec, char **str, va_list ap);
bool search_int(char **str, int width, long long *dest);

bool uint_search(specifier spec, char **str, va_list ap);
bool hex_parse(specifier spec, char **str, va_list ap, bool neg);
bool oct_parse(specifier spec, char **str, va_list ap, bool neg);
bool uint_parse(specifier spec, char **str, va_list ap, bool neg);
bool uint_parse_based(specifier spec, char **str, va_list ap, int base,
                      bool neg);
bool search_based_uint(char **str, int width, unsigned long long *dest,
                       int base, bool neg);

bool float_parse(specifier spec, char **str, va_list ap);
bool search_float(char **str, int width, long double *dest);
bool inf_or_nan(char **str, long double *dest);
long double s21_atof(char **str, int *width);
bool search_scientific(char **str, int *width, long double *res);

bool ptr_parse(specifier spec, char **str, va_list ap);

#endif
