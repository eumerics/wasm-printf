# wasm-printf

A lightweight, standalone implementation of __C printf__ function for WebAssembly modules. It adds about __3KB__ to the WebAssembly binary and about __4KB__ to the JavaScript code. It requires a JavaScript run time environment such as node.js or a browser.

### Features

Implements the complete `printf` specification as per C11 standard with the exceptions of `long double` (`%L`), multi-byte characters (`%lc`, `%ls`) and binary output of floating point numbers (`%a`, `%A`).
 - flags: `-`, `+`, `<space>`, `#`, `0`
 - width and precision specifiers (fixed and variable `*`)
 - length modifiers: `hh`, `h`, `l`, `ll`, `j`, `z`, `t`
 - conversion specifiers:
    - integer: `%d`, `%i`
    - unsigned: `%o`, `%u`, `%x`, `%X`
    - floating point: `%f`, `%e`, `%g`, `%F`, `%E`, `%G`
    - character: `%c`, `%s`
    - other: `%p`, `%n`

#### Extensions
 - Win32/Win64 length modifiers: `I`, `I32`, `I64`
 - UTF-16 char16_t specifiers: `%Ls`

### Usage

Usage is very straightforward. Start with a declaration of `printf` function and call it as you would normally in your code.

```C
// example.c
#include <stdint.h>
#include <stddef.h>
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
```

Compile and statically link with the provided source `wasm_printf.c`.

```Bash
wasi-sdk/bin/clang --sysroot=wasi-sdk/share/wasi-sysroot -nostartfiles -nostdlib -Wl,--export-all -Wl,--no-entry -Wl,--allow-undefined example.c wasm_printf.c -O3 -o example.wasm
```

Alternatively, you can statically link with the provided `printf.a.wasm` module if your toolchain understands the `linking` and `reloc` custom sections.
```Bash
<compiler> <options> example.c printf.a.wasm
```

Run the compiled WebAssembly in node.js or a browser. You must load the provided JavaScript `wasm-printf.min.js` to specify the needed imports.

```JavaScript
(async () => {
   let pfs = require('fs').promises;
   let {printf_init, printf_env} = require('wasm-printf.min.js');
   let example = await WebAssembly.instantiate(
      await pfs.readFile('example.wasm'), {env: printf_env}
   );
   printf_init(example.instance.exports.memory);
   example.instance.exports.test();
})();
```

### Line Buffering

The `printf` output is logged to a JavaScript console window. Unfortunately, JavaScript console does not support logging without line termination. To overcome this. `printf` output is buffered until a newline character is encountered. As a consequence, you might have to force the printing either by including a `\n` character or by calling `printf_flush()` from C code.

```C
// from C code
printf("no-newline-string-stream"); // no output
printf_flush(); // force output (an artificial newline is introduced)
// equivalently
printf("no-newline-string-stream\n"); // output is logged to console
```
Alternatively, you may invoke `printf_env.flush()` from the console.
``` JavaScript
// from console
// printf_env must first be loaded into the current scope from wasm-printf.min.js
printf_env.flush(); // force output and clear the buffer
printf_env.peek(); // print the buffer but do not clear it
```

### Implementation

Parsing of `printf` format string and handling of variable arguments is implemented in C, while the formatting and output is implemented in JavaScript. There are no dynamic memory allocations arising from the WebAssembly code. It only needs to maintain read-only view of the memory to access pointers (only the `%n` specifier will lead to memory writes).
