// Emscripten + ALLOW_MEMORY_GROWTH uses a resizable ArrayBuffer for WASM
// memory. Newer browsers reject TextDecoder.decode() on resizable buffers
// ("The provided ArrayBuffer value must not be resizable"). Emscripten 6+
// no longer allows -sTEXTDECODER=0, so patch decode to copy into a fixed
// buffer when needed. Paths and short strings only; cost is negligible.
(function () {
  if (typeof TextDecoder === 'undefined') return;
  var orig = TextDecoder.prototype.decode;
  if (!orig) return;
  TextDecoder.prototype.decode = function (input, options) {
    if (input) {
      // TypedArray view of a resizable buffer
      if (input.buffer && input.buffer.resizable) {
        input = new Uint8Array(input);
      }
      // Bare resizable ArrayBuffer
      else if (input.resizable) {
        input = input.slice(0);
      }
    }
    return orig.call(this, input, options);
  };
})();
