(async () => {
   let pfs = require('fs').promises;
   let memory = new WebAssembly.Memory({initial: 2});
   let {printf_init, printf_env} = require(`${__dirname}/../dist/wasm-printf.min.js`);
   let printf_c = await WebAssembly.instantiate(
      await pfs.readFile(`${__dirname}/../dist/printf.dyn.wasm`),
      {env : {...printf_env, memory: memory}}
   );
   let test = await WebAssembly.instantiate(
      await pfs.readFile(`${__dirname}/../build/test_dynamic.wasm`), {
         env: {...printf_env, memory: memory, printf: printf_c.instance.exports.printf}
      }
   );
   printf_init(memory);
   test.instance.exports.test();
})();
