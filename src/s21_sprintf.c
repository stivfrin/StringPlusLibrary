#include "s21_string.h"

#define BUFFER_MAX 100
#define FLAGS "0+#- "
#define SPECS "cdieEfgGosuxXpn%"

#define IS_NUM(a) ((a) >= '0' && (a) <= '9')

enum SpecFlags { ZERO, PLUS, HASH, MINUS, SPACE, FLAGS_MAX };

typedef union SpecValue {
  char* sp;
  int dic;
  unsigned int ouxX;
  double eEfgG;
  short int h_di;
  short unsigned int h_ouxX;
  long int l_dic;
  long unsigned int l_ouxX;
  long double L_eEfgG;
} val_t;

typedef struct Spec {
  int type;
  val_t value;
  int flags[FLAGS_MAX];
  int width;
  int precision;
  int length;
} spec_t;

int s21_sprintf(char* str, const char* format, ...);
char* print_d(char* dest, spec_t* s);
char* print_f(char** dest, spec_t* s);
char* print_e(char** dest, spec_t* s);
char* print_uxo(char* dest, spec_t* s, int base);
char* print_c(char* dest, spec_t* s);
char* print_s(char** str, spec_t* s);

void SetFlag(spec_t* s, char ch);
void AddDigit(int* dest, char digit);
void GetValue(spec_t* s, va_list* args_p);
void SetDefaults(spec_t* s);
int CheckG(spec_t* s);
void CutForRealG(long long* to_cut, spec_t* s);

int number_to_char_mass(long long full_ch, spec_t* s, char* var, int i,
                        int shift_for_counter);
char sign_token(int negative, spec_t* s);
void spec_e_zero(char** str, spec_t* s, int negative, int sign);
void spec_e_not_zero(long double ch, char** str, spec_t* s, int negative,
                     int sign);
void spaces_with_minus_for_specs_e_g(char** str, spec_t* s, int sign,
                                     int deleted_zeros);
int writting_exp(char* var, int i, int exp_counter);

void ParseSpec(char** format_p, spec_t* s, va_list* args_p, char* start);
void PrintSpec(char** dest_p, spec_t* s);

// // ST TEST DELETE LATER!
// int main()
// {
//     double val1 = 13.58;
//     int prec = 5;
//     // int val2 = 0;
//     // double val2 = 99993333.11;
//     // int val3 = 90;
//     // double val2 = 3.14;
//     // char* str_test = "test string";
//     char* format = "|%6.*g|";
//     char buffer1[100] = {0};
//     char buffer2[100] = {0};

//     sprintf(buffer2, format, val1);
//     printf("ref \"%s\"\n", buffer2);

//     s21_sprintf(buffer1, format, val1);
//     printf("rep \"%s\"\n", buffer1);
//     return 0;
// }

int s21_sprintf(char* str, const char* format, ...) {
  spec_t Spec;
  char* dest = str;
  va_list args;
  va_start(args, format);
  while (*format) {
    if (*format == '%') {
      ParseSpec((char**)&format, &Spec, &args, str);
      PrintSpec(&dest, &Spec);
    } else
      *dest++ = *format++;
  }
  va_end(args);
  return dest - str;
}

void AddDigit(int* dest, char digit) {
  *dest *= 10;
  *dest += digit - '0';
}

void SetFlag(spec_t* s, char ch) {
  switch (ch) {
    case '0':
      s->flags[ZERO] = 1;
      break;
    case '+':
      s->flags[PLUS] = 1;
      break;
    case '#':
      s->flags[HASH] = 1;
      break;
    case '-':
      s->flags[MINUS] = 1;
      break;
    case ' ':
      s->flags[SPACE] = 1;
      break;
  }
}

void ParseSpec(char** format_p, spec_t* s, va_list* args_p, char* start) {
  s21_memset(s, 0, sizeof(spec_t));
  char* src = *format_p + 1;
  while (s21_strchr(FLAGS, *src)) SetFlag(s, *src++);
  while (IS_NUM(*src)) AddDigit(&(s->width), *src++);
  if (*src == '*') {
    src++;
    s->width = va_arg(*args_p, int);
  }
  if (*src == '.') {
    src++;
    while (IS_NUM(*src)) AddDigit(&(s->precision), *src++);
    if (*src == '*') {
      src++;
      s->precision = va_arg(*args_p, int);
    }
  } else
    s->precision = -1;

  while (s21_strchr("hlL", *src)) s->length = *src++;
  if (s21_strchr(SPECS, *src)) s->type = *src++;

  if (s->type == 'n') {
    s->value.dic = s21_strlen(start);
  }
  GetValue(s, args_p);
  SetDefaults(s);
  *format_p = src;
}

void GetValue(spec_t* s, va_list* args_p) {
  switch (s->length) {
    case 'h':
      if (s21_strchr("di", s->type)) {
        s->value.h_di = (short int)va_arg(*args_p, int);
      }
      if (s21_strchr("ouxX", s->type)) {
        s->value.h_ouxX = (short unsigned int)va_arg(*args_p, unsigned int);
      }
      break;
    case 'l':
      if (s21_strchr("dic", s->type)) {
        s->value.l_dic = va_arg(*args_p, long int);
      }
      if (s21_strchr("ouxX", s->type)) {
        s->value.l_ouxX = va_arg(*args_p, long unsigned int);
      }
      break;
    case 'L':
      if (s21_strchr("eEfgG", s->type)) {
        s->value.L_eEfgG = va_arg(*args_p, long double);
      }
      break;
    default:
      if (s21_strchr("dic", s->type)) {
        s->value.dic = va_arg(*args_p, int);
      }
      if (s21_strchr("ouxX", s->type)) {
        s->value.ouxX = va_arg(*args_p, unsigned int);
      }
      if (s21_strchr("eEfgG", s->type)) {
        s->value.eEfgG = va_arg(*args_p, double);
      }
      if (s21_strchr("sp", s->type)) {
        s->value.sp = va_arg(*args_p, char*);
      }
      if (s->type == 'n') {
        *va_arg(*args_p, int*) = s->value.dic;
      }
      break;
  }
}

void SetDefaults(spec_t* s) {
  if (s->precision == 0) {
    if (s21_strchr("gG", s->type)) s->precision = 1;
  }
  if (s->precision == -1) {
    s->precision = 0;
    if (s21_strchr("eEfgG", s->type)) s->precision = 6;
    if (s21_strchr("diouxXpn", s->type)) s->precision = 1;
  }
}

void PrintSpec(char** dest_p, spec_t* s) {
  switch (s->type) {
    case 'c':
      *dest_p = print_c(*dest_p, s);
      break;
    case 'd':
      *dest_p = print_d(*dest_p, s);
      break;
    case 'i':
      *dest_p = print_d(*dest_p, s);
      break;
    case 'e':
      *dest_p = print_e(dest_p, s);
      break;
    case 'E':
      *dest_p = print_e(dest_p, s);
      break;
    case 'f':
      *dest_p = print_f(dest_p, s);
      break;
    case 'g':
      if (CheckG(s))
        *dest_p = print_e(dest_p, s);
      else
        *dest_p = print_f(dest_p, s);
      break;
    case 'G':
      if (CheckG(s))
        *dest_p = print_e(dest_p, s);
      else
        *dest_p = print_f(dest_p, s);
      break;
    case 'o':
      *dest_p = print_uxo(*dest_p, s, 8);
      break;
    case 's':
      *dest_p = print_s(dest_p, s);
      break;
    case 'u':
      *dest_p = print_uxo(*dest_p, s, 10);
      break;
    case 'x':
      *dest_p = print_uxo(*dest_p, s, 16);
      break;
    case 'X':
      *dest_p = print_uxo(*dest_p, s, 16);
      break;
    case 'p':
      s->value.l_dic = (long int)s->value.sp;
      s->type = 'x';
      s->flags[HASH] = 1;
      *dest_p = print_uxo(*dest_p, s, 16);
      break;
    case '%':
      s->value.dic = '%';
      *dest_p = print_c(*dest_p, s);
  }
}

int CheckG(spec_t* s) {
  int res = 0;
  char buffer[BUFFER_MAX];
  char* b_p = buffer;
  s->type = s->type - 2;
  print_e(&b_p, s);
  char* p = s21_strchr(buffer, s->type);
  int X = (*++p == '+') ? 1 : -1;
  X *= (*(p + 1) - '0') * 10 + (*(p + 2) - '0');
  if (X < s->precision && X >= -4) {
    s->precision = s->precision - 1 - X;
  } else {
    res = 1;
    s->precision = s->precision - 1;
  }
  return res;
}

void CutForRealG(long long* to_cut, spec_t* s) {
  while (*to_cut % 10 == 0 && *to_cut / 10) {
    *to_cut /= 10;
    s->precision--;
  }
}

char* print_d(char* dest, spec_t* s) {
  long int value = 0;
  int positive = 1;
  if (s->length == 'l')
    value = s->value.l_dic;
  else if (s->length == 'h')
    value = s->value.h_di;
  else
    value = s->value.dic;

  if (value < 0) {
    value = -value;
    positive = 0;
  }
  int len = 0;
  char buffer[BUFFER_MAX] = {0};
  for (long int i = value; i / 10 || i % 10; i /= 10) {
    buffer[len++] = 48 + i % 10;
  }
  while (len < s->precision) buffer[len++] = '0';
  while (len < s->width) buffer[len++] = ' ';
  char* sign_place = s21_strchr(buffer, ' ');
  if (s->flags[ZERO]) {
    for (char* p = buffer; p <= buffer + len; p++)
      if (*p == ' ') *p = '0';
    sign_place = s21_strrchr(buffer, '0');
  }
  if (!sign_place) sign_place = buffer + len;
  if (!positive) {
    *sign_place = '-';
  } else {
    if (s->flags[SPACE] || s->flags[PLUS]) {
      if (s->flags[SPACE]) *sign_place = ' ';
      if (s->flags[PLUS]) *sign_place = '+';
    } else {
      sign_place--;
    }
  }
  char* start = s21_strchr(buffer, 0) - 1;
  if (s->flags[MINUS]) start = sign_place;
  while (start >= buffer) {
    *dest++ = *start--;
    len--;
  }
  while (len > 0) {
    *dest++ = ' ';
    len--;
  }
  return dest;
}

char* print_c(char* dest, spec_t* s) {
  int ch = s->value.dic;
  if (s->flags[MINUS]) {
    *(dest++) = ch;
    for (int i = 0; i < s->width - 1; i++) *(dest++) = ' ';
  } else if (!s->flags[MINUS]) {
    for (int i = 0; i < s->width - 1; i++)
      *(dest++) = s->flags[ZERO] ? '0' : ' ';
    *dest++ = ch;
  }
  return dest;
}

char* print_uxo(char* dest, spec_t* s, int base) {
  long unsigned int value = 0;
  if (s->length == 'l')
    value = s->value.l_ouxX;
  else if (s->length == 'h')
    value = s->value.h_ouxX;
  else
    value = s->value.ouxX;

  int len = 0;
  char buffer[BUFFER_MAX] = {0};
  for (long unsigned int i = value; i / base || i % base; i /= base) {
    int digit = i % base;
    if (digit > 9)
      buffer[len++] = (s->type == 'X') ? '@' + digit - 9 : 96 + digit - 9;
    else
      buffer[len++] = 48 + digit;
  }
  while (len < s->precision) buffer[len++] = '0';
  if (s->flags[HASH]) {
    if (base == 16) buffer[len++] = s->type;
    buffer[len++] = '0';
  }
  while (len < s->width) {
    buffer[len++] = ' ';
  }
  char* sign_place = s21_strchr(buffer, ' ');
  if (!sign_place) sign_place = buffer + len;

  char* start = buffer + len - 1;
  if (s->flags[MINUS]) start = sign_place - 1;
  while (start >= buffer) {
    *dest++ = *start--;
    len--;
  }
  while (len > 0) {
    *dest++ = ' ';
    len--;
  }
  return dest;
}

char* print_f(char** dest, spec_t* s) {
  long double ch = 0;
  int negative = 0, int_counter = 0;
  int sign = 0;
  int point = 0;

  if (s->length == 'L')
    ch = s->value.L_eEfgG;
  else
    ch = s->value.eEfgG;

  if (ch < 0) {
    negative = 1;
    ch = -ch;
  }
  if ((negative || s->flags[PLUS] || s->flags[SPACE])) sign = 1;
  long long int_ch = s->precision == 0 ? (long long)round(ch) : (long long)(ch);
  double prov = ch - (long double)int_ch;
  long long float_ch = round((prov)*pow(10, s->precision));

  if (s->type != 'f' && !(s->flags[HASH])) CutForRealG(&float_ch, s);

  int ch_for_counter = int_ch;
  while (ch_for_counter != 0) {
    ch_for_counter = ch_for_counter / 10;
    int_counter++;
  }

  char var[BUFFER_MAX] = {0};
  int i = number_to_char_mass(float_ch, s, var, 0, 0);
  if (s->precision != 0 || s->flags[HASH]) {
    var[i++] = '.';
    point = 1;
  }
  if (!int_counter)
    var[i++] = '0';
  else
    i = number_to_char_mass(
        int_ch, s, var, i,
        int_counter + ((s->precision == 0 && !s->flags[HASH]) ? 0 : 1));
  if (s->flags[ZERO] && !s->flags[MINUS])
    for (; i < s->width - sign; i++) var[i] = '0';
  if (sign) var[i++] = sign_token(negative, s);
  if (!s->flags[MINUS])
    for (; i < s->width; i++) var[i] = ' ';

  for (i--; i >= 0; i--) {
    **dest = var[i];
    (*dest)++;
  }
  if (s->flags[MINUS]) {
    for (int j = 0; j < s->width - s->precision -
                            (int_counter > 0 ? int_counter : 1) - sign - point;
         j++) {
      **dest = ' ';
      (*dest)++;
    }
  }
  return *dest;
}

int number_to_char_mass(long long full_ch, spec_t* s, char* var, int i,
                        int shift_for_counter) {
  for (int del = 0; i < s->precision + shift_for_counter; i++) {
    del = full_ch % 10;
    var[i] = (char)(del + 48);
    full_ch /= 10;
  }
  return i;
}

char sign_token(int negative, spec_t* s) {
  char sign = ' ';
  if (!negative && s->flags[SPACE])
    sign = ' ';
  else if (s->flags[PLUS] && !negative)
    sign = '+';
  else if (negative)
    sign = '-';
  return sign;
}

char* print_e(char** dest, spec_t* s) {
  long double ch = 0;
  int negative = 0, sign = 0;

  if (s->length == 'L')
    ch = s->value.L_eEfgG;
  else
    ch = s->value.eEfgG;
  if (ch < 0.0) {
    negative = 1;
    ch = -ch;
  }
  if (negative || s->flags[PLUS] || s->flags[SPACE]) sign = 1;
  if (ch != 0)
    spec_e_not_zero(ch, dest, s, negative, sign);
  else if (ch == 0)
    spec_e_zero(dest, s, negative, sign);

  return *dest;
}

void spec_e_not_zero(long double ch, char** str, spec_t* s, int negative,
                     int sign) {
  int exp_counter = 0;
  double ch_for_sign = ch;

  if (ch >= 1) {
    while (ch >= 1) {
      ch /= 10;
      exp_counter++;
    }
    exp_counter--;
  } else if (ch < 1) {
    while (ch < 1) {
      ch *= 10;
      exp_counter++;
    }
    ch /= 10;
  }
  long long full_ch = round(
      ch * pow(10, s->precision +
                       (fabsl(ch - 1.0L) < 1.0L / (powl(10, s->precision + 1))
                            ? 0
                            : 1)));
  char var[BUFFER_MAX] = {0};
  var[0] = '\0';
  int i = writting_exp(
      var, 0,
      exp_counter -
          (fabsl(ch - 1.0L) < 1.0L / (powl(10, s->precision + 1)) ? 1 : 0));
  var[i++] = ch_for_sign >= 1.0 ? '+' : '-';
  var[i++] = s->type;
  int del1 = 0, j = i;
  for (; j < s->precision + 4; j++) {
    del1 = full_ch % 10;
    var[j] = (char)(del1 + 48);
    full_ch = full_ch / 10;
  }
  i = j;
  if (s->precision >= 1 || s->flags[HASH]) var[i++] = '.';
  var[i++] = (char)((full_ch % 10) + 48);
  if (s->flags[ZERO] && !s->flags[MINUS])
    for (; i < s->width - sign; i++) var[i] = '0';
  if (sign) var[i++] = sign_token(negative, s);
  if (!s->flags[MINUS])
    for (; i < s->width; i++) var[i] = ' ';

  for (i--; i >= 0; i--) {
    **str = var[i];
    (*str)++;
  }
  if (s->flags[MINUS]) spaces_with_minus_for_specs_e_g(str, s, sign, -1);
}

int writting_exp(char* var, int i, int exp_counter) {
  for (int del = 0, exp_counter_for_count = exp_counter;
       i < (exp_counter >= 10 ? 2 : 1); i++) {
    del = exp_counter_for_count % 10;
    var[i] = (char)(del + 48);
    exp_counter_for_count /= 10;
  }
  if (exp_counter < 10) var[i++] = '0';
  return i;
}

void spaces_with_minus_for_specs_e_g(char** str, spec_t* s, int sign,
                                     int deleted_zeros) {
  for (int j = 0; j <= s->width - s->precision - 5 - sign + deleted_zeros;
       j++) {
    **str = ' ';
    (*str)++;
  }
}

void spec_e_zero(char** str, spec_t* s, int negative, int sign) {
  int i = 0;
  char var[BUFFER_MAX] = {0};
  for (; i < 2; i++) var[i] = '0';
  var[i++] = '+';
  var[i++] = s->type;
  for (; i < s->precision + 4; i++) var[i] = '0';
  if (s->precision > 0 || s->flags[HASH]) var[i++] = '.';
  var[i++] = '0';
  if (sign) var[i++] = sign_token(negative, s);
  if (!s->flags[MINUS])
    for (; i < s->width + sign; i++) var[i] = ' ';
  for (i--; i >= 0; --i) {
    **str = var[i];
    (*str)++;
  }
  if (s->flags[MINUS]) {
    char var_for_spaces[s->width];
    int j = 0;
    if (s->flags[MINUS] && s->width > s->precision + 5 + (sign | 1)) {
      for (; j < s->width - s->precision - 5 - sign - 1; j++)
        var_for_spaces[j] = ' ';
      for (j--; j >= 0; j--) {
        **str = var_for_spaces[j];
        (*str)++;
      }
    }
  }
}

char* print_s(char** str, spec_t* s) {
  char* add_str = s->value.sp;
  int len = s21_strlen(add_str);
  **str = '\0';
  if (s->precision && s->precision < len) len = s->precision;
  if (s->width > len) {
    int len_spaces = s->width - len;
    char spaces[len_spaces + 1];
    for (int i = 0; i < len_spaces; i++) spaces[i] = ' ';
    spaces[len_spaces] = '\0';
    if (s->flags[MINUS]) {
      s21_strncat(*str, add_str, len);
      s21_strncat(*str, spaces, len_spaces);
    } else {
      if (s->flags[ZERO]) {
        s21_memset(spaces, '0', len_spaces);
      }
      s21_strncat(*str, spaces, len_spaces);
      s21_strncat(*str, add_str, len);
    }
  } else
    s21_strncat(*str, add_str, len);
  *str += s21_strlen(*str);
  return *str;
}