#include <stdint.h>
#include <stddef.h>
#include <float.h>
#ifndef WASM_EXPORT
#define WASM_EXPORT __attribute__ ((visibility ("default")))
#endif
#define counted_printf(cs, cast, fs, ...) { \
   int length = printf(fs "%" cs "n", __VA_ARGS__, (cast*)(count)); \
   printf("length = %d " "%" cs "d\n", length, *(cast*)(count)); \
}
WASM_EXPORT void test() {
   long long int _count = 0;
   void *count = &_count;
   // signed integers
   counted_printf("", int,
      "%d, %2d, %04d, %d, %02d, %+4d, %+04d, %-4d, % d, % d, %5.3d, %05.3d, %05.d, "
      "%4d, %04d, %'d - %'d - %'d - %'d - %'d, %0*d, %.0d, %.0d\n",
      1, 2, 3, 346, 7890, 12, 34, 56, 78, -90, 12, 34, 56,
      -12, -34, 567, 8901, 23456, 789012, 3456789, 5, 123, 0, 5
   );
   // char and strings
   counted_printf("hh", char,
      "%c, %3c, %*c, %s, %3s, %*s, %.3s, %.*s, "
      "%-3c, %-*c, %-3s, %-*s\n",
      'a', 'b', 2, 'c', "de", "fg", 4, "hi", "jklm", 3, "mnop",
      'a', 2, 'b', "cd", 3, "ef"
   );
   // unsigned integers
   counted_printf("h", short,
      "%u, %2u, %04u, %4o, %5x, %5X, %#4o, %#5x, %0#5X, %5.3u, %05.3o, %05.x, "
      "%-u, %-2u, %-4u, %-4o, %-5x, %-5X, %-#4o, %-#5x, %-#5X, %#5.3o, %.0u, %.0u\n",
      1, 2, 3, 45, 67, 89, 10, 23, 45, 6, 78, 90,
      1, 2, 3, 45, 67, 89, 10, 23, 45, 6, 0, 7
   );
   // pointers
   counted_printf("l", long,
      "%p, %p, %p, %6p, %8p, %11p, %-6p, %-8p, %-11p\n",
      (void*)(0), (void*)(0x1234), (void*)(0x56789012),
      (void*)(0), (void*)(0x1234), (void*)(0x56789012),
      (void*)(0), (void*)(0x1234), (void*)(0x56789012)
   );
   // double
   counted_printf("ll", long long,
      "%f, %f, %f, %f, %f, %.0f, %#.0f, %014f, %.10f, %.10f, %.10f, %.0f, %.0F\n",
      0., 1234567890., 0.1234567890, 0.12345678e-4, 0.12345678e-8, 2., 2.,
      -1234., 0.1234567890, 0.12345678e-4, 0.12345678e-8, .999, 999.
   );
   counted_printf("j", intmax_t,
      "%e, %#e, %.0e, %#.0e, %e, %E, %e, %E, %.0e, %#.0E, %014e, %.10E, %.10e, %.10E, %.0e, %.1E\n",
      0., 0., 0., 0., 1234567890., 0.1234567890, 0.12345678e-4, 0.12345678e-8, 2., 2.,
      -1234., 0.1234567890, 0.12345678e-4, 0.12345678e-8, 999., 999.
   );
   counted_printf("z", size_t,
      "%g, %#g, %.0g, %.3g, %#.3g, %.0g, %#.0G, "
      "%g, %G, %g, %G, %g, %G, %.5g, %.6G, %#.6G, "
      "%016g, %.10G, %.0g, %.1G\n",
      0., 0., 0., 0., 0., 1., 1.,
      1e-4, 1e-5, 1e-6, 2.3e-4, 2.3e-5, 2.3e-6, 0.123e-3, 0.123e-6, 0.123e-6,
      -1234., 0.1234567890, 999., 999.
   );
   counted_printf("", int, "%f, %10f, %10G, %10e\n", -0., 1./0, -1./0, 0./0);
   // misc
   counted_printf("", int, "%% %d\n", 0);
   // long types
   counted_printf("t", ptrdiff_t,
      "%ld, %lo, %lu, %lx, %lX, "
      "%lld, %llo, %llu, %llx, %llX\n",
      1L, 34L, 56L, 78L, 90L,
      12LL<<48, 34LL, 56LL, 78LL, 90LL
   );
   // negative integers and length modifiers
   char hh = -16; short h = -32;
   counted_printf("", int, "%hhd %hhu %hho %hhx\n", hh, hh, hh, hh);
   counted_printf("", int, "%hd %hu %ho %hx\n", h, h, h, h);
   // inane specifiers
   counted_printf("", int, "%*d, %.d\n", -5, 1, 2);
   // unsupported
   counted_printf("", int, "%Lf, %A\n", 0.L, 0.);
}
