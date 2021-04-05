WASMC=${WASI_SDK_DIR}/bin/clang --sysroot ${WASI_SDK_DIR}/share/wasi-sysroot
WASM_OPTS=-nostartfiles -nostdlib -Wl,--export-dynamic -Wl,--no-entry -Wl,--allow-undefined
TARGETS=dist/wasm-printf.min.js dist/wasm-printf.js dist/wasm_printf.c dist/printf.a.wasm dist/printf.dyn.wasm
all: ${TARGETS}
dist/wasm-printf.min.js: src/printf.js
	node_modules/.bin/terser --compress --mangle -- src/printf.js > dist/wasm-printf.min.js
dist/wasm-printf.js: src/printf.js
	cp src/printf.js dist/wasm-printf.js
dist/wasm_printf.c: src/printf.c
	cp src/printf.c dist/wasm_printf.c
dist/printf.a.wasm: src/printf.c
	${WASMC} -c src/printf.c -O3 -o dist/printf.a.wasm
dist/printf.dyn.wasm: src/printf.c
	${WASMC} ${WASM_OPTS} -Wl,--import-memory src/printf.c -O3 -o dist/printf.dyn.wasm
test: all
	cd test; make
clean:
	rm -f ${TARGETS}; cd test; make clean; cd ../example; make clean;
