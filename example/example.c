int printf(char const*, ...);
void test() {
   printf("%d %u %f %e %g\n", -1, 2, 3., 0.4, 5e-2); // conversions
   printf("%c %s %p %o %x\n", '6', "78", (void *)(0), 89, 90); // conversions
   printf("%4.3d %4.3f\n", 12, 3.4); // field width and precision
   printf("%-4d %+d % d %#f %03d\n", 56, 7, 8, 9., 12); // flags
   printf("%ld %lld\n", 12L, -45LL); // length modifiers
}
