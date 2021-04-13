#include <stdint.h>
#include <stddef.h>
#include <uchar.h>
int printf(char const*, ...);
void test() {
   // NOTE: output won't appear until a newline is encountered
   printf("%d %u %f %e %g\n", -1, 2, 3., 0.4, 5e-2); // conversions
   printf("%c %s %p %o %x\n", '6', "78", (void *)(0), 89, 90); // conversions
   printf("%4.3d %4.3f\n", 12, 3.4); // field width and precision
   printf("%-4d %+d % d %#f %03d\n", 56, 7, 8, 9., 12); // flags
   printf("%ld %lld\n", 12L, -45LL); // length modifiers
   printf("%Id %Iu %I32o %I64x\n", (ptrdiff_t)(12), (size_t)(34), (int32_t)(567), (uint64_t)(890)); // Win32/Win64 length modifiers
   char16_t unicode_string[] = {0x61, 0xc0, 0x1f00, 0xd835, 0xdec3, 0x0};
   printf("%Ls %Ls\n", unicode_string, u"aÀἀ𝛃");
}
