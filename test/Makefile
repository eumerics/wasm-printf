WASMC=${WASI_SDK_DIR}/bin/clang --sysroot ${WASI_SDK_DIR}/share/wasi-sysroot
WASM_OPTS=-nostartfiles -nostdlib -Wl,--export-dynamic -Wl,--no-entry -Wl,--allow-undefined
all: ../build/test_static.wasm ../build/test_dynamic.wasm ../build/test_stdio ../build/test_relay
../build/test_static.wasm: ../src/printf.c test.h static.c
	${WASMC} ${WASM_OPTS} static.c ../src/printf.c -O3 -o ../build/test_static.wasm
../build/test_dynamic.wasm: test.h dynamic.c
	${WASMC} ${WASM_OPTS} -Wl,--import-memory dynamic.c -O3 -o ../build/test_dynamic.wasm
../build/test_stdio: test.h stdio.c
	clang stdio.c -O3 -o ../build/test_stdio
../build/test_relay: test.h ../src/printf.c relay.c
	clang relay.c -O3 -o ../build/test_relay
clean:
	rm ../build/test_*
