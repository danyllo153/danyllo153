# Motor web modificado (em andamento)

Mudanças sobre [origami-ltd/wasm-generals @ 46382a3](https://github.com/origami-ltd/wasm-generals/tree/46382a383da270e16a60a28ecf342b569b998111), código GPL-3.0:

| Arquivo | O quê |
|---|---|
| `zh-resolucao-desempenho.patch` | Resoluções 2560×1440 e 3840×2160; opção `GENERALSX_WEB_JSPI` (JSPI + exceções nativas do WebAssembly no lugar de Asyncify + exceções em JS), com o laço de quadros movido para JS |
| `match_data_package.py` | Faz o `.js` da nossa build ler o `GeneralsXZH.data` original, que não redistribuímos |

Estado: **não compilado ainda**. O ambiente de nuvem bloqueia os downloads do GitHub que o vcpkg precisa; próximo passo proposto é compilar via GitHub Actions.

Aplicar: `git -C wasm-generals apply zh-resolucao-desempenho.patch`. Compilar a versão rápida: `cmake --preset webgpu -DGENERALSX_WEB_JSPI=ON`.
