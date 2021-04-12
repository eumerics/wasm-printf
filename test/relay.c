#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#define PRINTF_RELAY
#define WASM_EXPORT
char format_string[32]; // we will use a global since this file is for testing only
void set_format(int flags, int width, int precision, char length_char, uint8_t length, char type)
{
   int index = 0;
   int const flag_left_align = 0x01;
   int const flag_plus_sign = 0x02;
   int const flag_plus_space = 0x04;
   int const flag_zero_pad = 0x08;
   int const flag_thousands_separator = 0x10;
   int const flag_hash_modifier = 0x20;
   format_string[index++] = '%';
   if(flags & flag_left_align) format_string[index++] = '-';
   if(flags & flag_plus_sign) format_string[index++] = '+';
   if(flags & flag_plus_space) format_string[index++] = ' ';
   if(flags & flag_zero_pad) format_string[index++] = '0';
   if(flags & flag_hash_modifier) format_string[index++] = '#';
   if(width != -1) index += sprintf(format_string + index, "%d", width);
   if(precision != -1) index += sprintf(format_string + index, ".%d", precision);
   if(length_char == 1) {
      format_string[index++] = 'l';
      format_string[index++] = 'l';
   } else if(length_char == 2) {
      format_string[index++] = 'h';
      format_string[index++] = 'h';
   } else if(length_char == 'I') {
      format_string[index++] = 'I';
      if(length == 4) {
         format_string[index++] = '3';
         format_string[index++] = '2';
      } else {
         format_string[index++] = '6';
         format_string[index++] = '4';
      }
   } else if(length_char != 0) {
      format_string[index++] = length_char;
   }
   format_string[index++] = type;
   format_string[index++] = 0;
}
int printf_string(char const* begin, char const* end)
{
   return printf("%.*s", (int)(end - begin), begin);
}
int printf_integer(int flags, int width, int precision, char length_char, uint8_t length, char type, int value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_int32(int flags, int width, int precision, char length_char, uint8_t length, char type, int32_t value)
{
   //set_format(flags, width, precision, length_char, length, type);
   //return printf(format_string, value);
   return 0;
}
int printf_int64(int flags, int width, int precision, char length_char, uint8_t length, char type, int64_t value)
{
   //set_format(flags, width, precision, length_char, length, type);
   //return printf(format_string, value);
   return 0;
}
int printf_long(int flags, int width, int precision, char length_char, uint8_t length, char type, long value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_long_long(int flags, int width, int precision, char length_char, uint8_t length, char type, long long value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_intmax(int flags, int width, int precision, char length_char, uint8_t length, char type, intmax_t value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_signed_size(int flags, int width, int precision, char length_char, uint8_t length, char type, size_t value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_ptrdiff(int flags, int width, int precision, char length_char, uint8_t length, char type, ptrdiff_t value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_unsigned(int flags, int width, int precision, char length_char, uint8_t length, char type, unsigned value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_uint32(int flags, int width, int precision, char length_char, uint8_t length, char type, uint32_t value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_uint64(int flags, int width, int precision, char length_char, uint8_t length, char type, uint64_t value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_unsigned_long(int flags, int width, int precision, char length_char, uint8_t length, char type, unsigned long value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_unsigned_long_long(int flags, int width, int precision, char length_char, uint8_t length, char type, unsigned long long value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_uintmax(int flags, int width, int precision, char length_char, uint8_t length, char type, uintmax_t value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_size(int flags, int width, int precision, char length_char, uint8_t length, char type, size_t value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_unsigned_ptrdiff(int flags, int width, int precision, char length_char, uint8_t length, char type, ptrdiff_t value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_double(int flags, int width, int precision, char length_char, uint8_t length, char type, double value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_long_double(int flags, int width, int precision, char length_char, uint8_t length, char type, long double value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_cstring(int flags, int width, int precision, char length_char, uint8_t length, char type, char const* value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_char(int flags, int width, int precision, char length_char, uint8_t length, char type, char value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}
int printf_pointer(int flags, int width, int precision, char length_char, uint8_t length, char type, void* value)
{
   set_format(flags, width, precision, length_char, length, type);
   return printf(format_string, value);
}

#define printf printf_relay
#include "../src/printf.c"
#include "test.h"

int main() {
   test();
   return 0;
}
