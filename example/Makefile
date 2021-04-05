WASMC=${WASI_SDK_DIR}/bin/clang --sysroot ${WASI_SDK_DIR}/share/wasi-sysroot
WASM_OPTS=-nostartfiles -nostdlib -Wl,--export-all -Wl,--no-entry -Wl,--allow-undefined
all: ../build/example.wasm
../build/example.wasm: example.c ../dist/wasm_printf.c
	${WASMC} ${WASM_OPTS} example.c ../dist/wasm_printf.c -O3 -o ../build/example.wasm
clean:
	rm -f ../build/example.wasm
