(async () => {
   let pfs = require('fs').promises;
   //let {printf_init, printf_env} = require('../src/printf.js');
   let {printf_init, printf_env} = require('../dist/wasm-printf.min.js');
   let test = await WebAssembly.instantiate(
      await pfs.readFile('../build/test_static.wasm'), {env: printf_env}
   );
   printf_init(test.instance.exports.memory);
   test.instance.exports.test();
})();
