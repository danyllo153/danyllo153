# Motor web modificado (em andamento)

Mudanças sobre [origami-ltd/wasm-generals @ 46382a3](https://github.com/origami-ltd/wasm-generals/tree/46382a383da270e16a60a28ecf342b569b998111), código GPL-3.0:

| Arquivo | O quê |
|---|---|
| `zh-resolucao-desempenho.patch` | Resoluções 2560×1440 e 3840×2160; opção `GENERALSX_WEB_JSPI` (JSPI + exceções nativas do WebAssembly no lugar de Asyncify + exceções em JS), com o laço de quadros movido para JS |
| `extract_data_package.py` | Extrai, só durante a compilação, os arquivos embutidos no `.data` original |
| `match_data_package.py` | Faz o `.js` da nossa build ler o `GeneralsXZH.data` original, que não redistribuímos |

Compilação: workflow [`.github/workflows/motor-web.yml`](../../../.github/workflows/motor-web.yml) (GitHub Actions). Ele gera as versões `compat` e `rapida` e publica `.js` + `.wasm` na release `motor-web`. Para instalar: `instalar.ps1 -Versao rapida` (ou `compat`).

Aplicar: `git -C wasm-generals apply zh-resolucao-desempenho.patch`. Compilar a versão rápida: `cmake --preset webgpu -DGENERALSX_WEB_JSPI=ON`.
