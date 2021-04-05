(async () => {
   let pfs = require('fs').promises;
   let {printf_init, printf_env} = require(`${__dirname}/../dist/wasm-printf.min.js`);
   let example = await WebAssembly.instantiate(
      await pfs.readFile(`${__dirname}/../build/example.wasm`), {env: printf_env}
   );
   printf_init(example.instance.exports.memory);
   example.instance.exports.test();
})();
