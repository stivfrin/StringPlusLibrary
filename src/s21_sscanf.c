#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int result = *str ? 0 : -1;
  va_list ap;
  va_start(ap, format);

  char *s_str = (char *)str;
  char *start = s_str;
  char *f_str = (char *)format;
  while (*s_str && *f_str && result != -1) {
    if (*f_str == '%') {
      f_str++;
      if (*f_str != '%') {
        specifier spec = specifier_scanf(&f_str);
        result += big_parse(spec, &s_str, ap, &result, start);
      } else {
        if (*s_str == '%') {
          s_str++;
          f_str++;
        } else {
          result = -1;
        }
      }
    } else {
      if (*s_str == *f_str) {
        s_str++;
        f_str++;
      } else if (*f_str == ' ') {
        f_str++;
      } else {
        break;
      }
    }
  }
  if (*f_str == '%' && *(f_str + 1) == 'n') {
    *va_arg(ap, long int *) = s_str - start;
  }

  va_end(ap);

  return result;
}

specifier specifier_scanf(char **format) {
  specifier res = {0};
  if (**format == '*') {
    res.skip = true;
    (*format)++;
  }

  if (true_digit(**format, 10)) {
    res.width = width_processing(format);
  }

  if (**format == 'l') {
    res.len = len_l;
    (*format)++;
    if (**format == 'l') {
      res.len = len_L;
      (*format)++;
    }
  } else if (**format == 'h') {
    res.len = len_h;
    (*format)++;
  } else if (**format == 'L') {
    res.len = len_L;
    (*format)++;
  } else {
    res.len = len_none;
  }
  const char *spec_str = "cdieEfgGosuxXpn";
  char *pos = s21_strchr(spec_str, **format);
  if (pos) {
    res.spec = (sspecs)(pos - spec_str);
  } else {
    res.spec = spec_unknown;
  }
  (*format)++;
  return res;
}

bool true_digit(char c, int base) {
  bool res;
  if (base <= 10) {
    res = c >= '0' && c < '0' + base;
  } else {
    res = (c >= '0' && c <= '9') || (c >= 'A' && c < 'A' + base - 10) ||
          (c >= 'a' && c < 'a' + base - 10);
  }
  return res;
}

s21_size_t converter_digit(char c, int base) {
  s21_size_t res = 0;
  if (base <= 10) {
    res = c - '0';
  } else {
    if (c <= '9') {
      res = c - '0';
    } else if (c <= 'A' + base - 10) {
      res = c - 'A' + 10;
    } else {
      res = c - 'a' + 10;
    }
  }
  return res;
}

bool search_strstr(char **str, char *pat) {
  bool res = false;
  char *s = *str;
  while (*s && to_lower(*s) == to_lower(*pat)) {
    s++;
    pat++;
  }
  if (*pat == '\0') {
    *str = s;
    res = true;
  }
  return res;
}

char to_lower(char c) {
  if (c >= 'A' && c <= 'Z') {
    c += 'a' - 'A';
  }
  return c;
}

int width_processing(char **f_str) {
  int res = 0;
  while (true_digit(**f_str, 10)) {
    res = res * 10 + (**f_str - '0');
    (*f_str)++;
  }
  return res;
}

bool big_parse(specifier spec, char **str, va_list ap, int *res, char *start) {
  bool result = false;
  while (**str == ' ') {
    (*str)++;
  }
  if (**str) {
    switch (spec.spec) {
      case spec_c:
        result = str_parse(spec, str, ap);
        break;
      case spec_d:
        result = int_parse(spec, str, ap);
        break;
      case spec_i:
        result = uint_search(spec, str, ap);
        break;
      case spec_e:
        result = float_parse(spec, str, ap);
        break;
      case spec_E:
        result = float_parse(spec, str, ap);
        break;
      case spec_f:
        result = float_parse(spec, str, ap);
        break;
      case spec_g:
        result = float_parse(spec, str, ap);
        break;
      case spec_G:
        result = float_parse(spec, str, ap);
        break;
      case spec_o:
        result = oct_parse(spec, str, ap, false);
        break;
      case spec_s:
        result = str_parse(spec, str, ap);
        break;
      case spec_u:
        result = uint_parse(spec, str, ap, false);
        break;
      case spec_x:
        result = hex_parse(spec, str, ap, false);
        break;
      case spec_X:
        result = hex_parse(spec, str, ap, false);
        break;
      case spec_p:
        result = ptr_parse(spec, str, ap);
        break;
      case spec_n:
        *va_arg(ap, long int *) = *str - start;
        break;
      case spec_unknown:
        *res = -1;
        break;
      default:
        *res = -1;
        break;
    }
  } else {
    *res = -1;
  }
  return result;
}

bool str_parse(specifier spec, char **str, va_list ap) {
  bool result = false;
  char *d = va_arg(ap, char *);
  if (spec.width == 0) {
    if (spec.spec == spec_c) {
      spec.width = 1;
    } else {
      spec.width = INT_MAX;
    }
  }
  while (**str && spec.width > 0 && **str != ' ') {
    *d++ = **str;
    (*str)++;
    spec.width--;
  }
  if (spec.spec == spec_s) {
    *d = '\0';
  }
  result = true;

  return result;
}

bool int_parse(specifier spec, char **str, va_list ap) {
  long long res = 0;
  bool result = search_int(str, spec.width, &res);
  result &= !spec.skip;
  if (result) {
    switch (spec.len) {
      case len_none:
        *(va_arg(ap, int *)) = (int)res;
        break;
      case len_h:
        *(va_arg(ap, short *)) = (short)res;
        break;
      case len_l:
        *(va_arg(ap, long *)) = (long)res;
        break;
      case len_L:
        *(va_arg(ap, long long *)) = (long long)res;
        break;
    }
  }
  return result;
}

bool search_int(char **str, int width, long long *dest) {
  bool flag = false, find = false, neg = false;
  if (width == 0) {
    width = INT_MAX;
  }
  long long res = 0;
  if (**str == '-') {
    neg = true;
    (*str)++;
    width--;
  } else if (**str == '+') {
    (*str)++;
    width--;
  }
  if (true_digit(**str, 10)) {
    find = true;
  } else if (neg) {
    (*str)--;
  }
  if (find) {
    while (true_digit(**str, 10) && width--) {
      if (res > (LLONG_MAX - (**str - '0')) / 10) {
        find = false;
        flag = true;
        res = LLONG_MAX;
        if (neg) res = -res - 1;
        while (**str && width--) (*str)++;
        break;
      }
      res = res * 10 + (**str - '0');
      (*str)++;
    }
  }
  if (find && neg) {
    res = -res;
  }
  if (find || flag) {
    *dest = res;
  }
  return find || flag;
}

bool uint_search(specifier spec, char **str, va_list ap) {
  bool neg = false;
  if (**str == '-') {
    neg = true;
    (*str)++;
    spec.width--;
  } else if (**str == '+') {
    (*str)++;
    spec.width--;
  }
  bool res = false;
  if (**str == '0') {
    (*str)++;
    if (**str == 'x') {
      (*str)++;
      res = hex_parse(spec, str, ap, neg);
    } else {
      res = oct_parse(spec, str, ap, neg);
    }
  } else {
    res = uint_parse(spec, str, ap, neg);
  }
  return res;
}

bool hex_parse(specifier spec, char **str, va_list ap, bool neg) {
  bool res = neg;
  if (**str == '-' && !neg) {
    (*str)++;
    spec.width--;
    neg = true;
  } else if (**str == '+') {
    (*str)++;
    spec.width--;
  }
  if (**str == '0' && ((*(*str + 1) == 'x') || *(*str + 1) == 'X')) {
    *str += 2;
    res |= true;
  }
  res |= uint_parse_based(spec, str, ap, 16, neg);
  return res;
}

bool oct_parse(specifier spec, char **str, va_list ap, bool neg) {
  bool res = neg;
  if (**str == '-' && !neg) {
    neg = true;
    (*str)++;
    spec.width--;
  } else if (**str == '+') {
    (*str)++;
    spec.width--;
  }
  if (**str == '0') {
    (*str)++;
    spec.width--;
    res |= true;
  }
  res |= uint_parse_based(spec, str, ap, 8, neg);
  return res;
}

bool uint_parse(specifier spec, char **str, va_list ap, bool neg) {
  bool res = false;
  bool f = true;
  if (**str == '-') {
    if (!neg) {
      (*str)++;
      spec.width--;
      neg = true;
    } else {
      f = false;
    }
  } else if (**str == '+') {
    (*str)++;
    spec.width--;
  }
  if (f) {
    res |= uint_parse_based(spec, str, ap, 10, neg);
  }
  return res;
}

bool uint_parse_based(specifier spec, char **str, va_list ap, int base,
                      bool neg) {
  unsigned long long res = 0;
  bool result = search_based_uint(str, spec.width, &res, base, neg) || neg;
  result &= !spec.skip;
  if (result) {
    switch (spec.len) {
      case len_none:
        *(va_arg(ap, unsigned int *)) = (unsigned int)res;
        break;
      case len_h:
        *(va_arg(ap, unsigned short *)) = (unsigned short)res;
        break;
      case len_l:
        *(va_arg(ap, unsigned long *)) = (unsigned long)res;
        break;
      case len_L:
        *(va_arg(ap, unsigned long long *)) = (unsigned long long)res;
        break;
    }
  }
  return result;
}

bool search_based_uint(char **str, int width, unsigned long long *dest,
                       int base, bool neg) {
  bool find = false;
  if (width == 0) width = INT_MAX;
  unsigned long long res = 0;
  if (true_digit(**str, base)) {
    find = true;
  }
  if (find) {
    while (true_digit(**str, base) && width--) {
      if (res > (ULLONG_MAX - converter_digit(**str, base)) / base) {
        res = ULLONG_MAX;
        while (**str && width--) (*str)++;
      } else {
        res = res * base + converter_digit(**str, base);
        (*str)++;
      }
    }
    if (neg) res = -res;
    *dest = res;
  }
  return find;
}

bool float_parse(specifier spec, char **str, va_list ap) {
  bool res = false;
  if (spec.width == 0) {
    spec.width = INT_MAX;
  }
  long double res_d = 0;
  res = search_float(str, spec.width, &res_d);
  res &= !spec.skip;
  if (res) {
    switch (spec.len) {
      case len_none:
        *(va_arg(ap, float *)) = (float)res_d;
        break;
      case len_h:
        *(va_arg(ap, float *)) = (float)res_d;
        break;
      case len_l:
        *(va_arg(ap, double *)) = (double)res_d;
        break;
      case len_L:
        *(va_arg(ap, long double *)) = res_d;
        break;
      default:
        break;
    }
  }
  return res;
}

bool search_float(char **str, int width, long double *dest) {
  bool find = false;
  bool neg = false;
  long double res = 0;
  if (**str == '-') {
    neg = true;
    (*str)++;
    width--;
  } else if (**str == '+') {
    (*str)++;
    width--;
  }
  if (inf_or_nan(str, &res)) {
    find = true;
  } else if (true_digit(**str, 10) || **str == '.') {
    find = true;
    if (**str == '.') {
      find = false;
      if (true_digit(*(*str + 1), 10)) {
        find = true;
      }
    }
    res = s21_atof(str, &width);
    search_scientific(str, &width, &res);
  } else if (neg) {
    (*str)--;
  }
  if (find) {
    if (neg) res = -res;
    *dest = res;
  }
  return find;
}

bool inf_or_nan(char **str, long double *dest) {
  bool res = false;
  if (search_strstr(str, "nan")) {
    res = true;
    *dest = NAN;
  } else if (search_strstr(str, "inf")) {
    res = true;
    *dest = INFINITY;
  }
  return res;
}

long double s21_atof(char **str, int *width) {
  long double res = 0;
  while (true_digit(**str, 10) && width) {
    res = res * 10 + (**str - '0');
    (*str)++;
    (*width)--;
  }
  if (**str == '.') {
    (*str)++;
    (*width)--;
    long double frac_coef = 1;
    int frac_width = 0;
    while (true_digit(*(*str + frac_width), 10) && (*width)--) frac_width++;
    while (frac_width--) {
      frac_coef /= 10;
      res += frac_coef * (**str - '0');
      (*str)++;
    }
  }
  return res;
}

bool search_scientific(char **str, int *width, long double *res) {
  long long exp = 0;
  bool find = false;

  if (**str == 'e' || **str == 'E') {
    (*str)++;
    (*width)--;
    find = search_int(str, *width, &exp);
  }

  *res *= pow(10, exp);
  return find;
}

bool ptr_parse(specifier spec, char **str, va_list ap) {
  spec.len = len_l;
  return hex_parse(spec, str, ap, false);
}