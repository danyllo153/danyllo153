"""Extrai os arquivos embutidos num pacote .data do Emscripten, usando a tabela do .js que o acompanha.

Usado so durante a compilacao (GitHub Actions): os arquivos extraidos servem para a build gerar a
mesma tabela de arquivos do original. Eles nunca sao publicados.

Uso: python extract_data_package.py ORIGINAL.js ORIGINAL.data PASTA_DE_SAIDA
"""
import os
import re
import sys

ENTRY = re.compile(r'\{filename:"([^"]+)",start:(\d+),end:(\d+)\}')


def main(js_path, data_path, out_dir):
    entries = ENTRY.findall(open(js_path, encoding="utf-8").read())
    if not entries:
        sys.exit("tabela de arquivos nao encontrada no .js")
    blob = open(data_path, "rb").read()
    root = os.path.realpath(out_dir)
    for name, start, end in entries:
        target = os.path.realpath(os.path.join(root, name.lstrip("/")))
        if not target.startswith(root + os.sep):
            sys.exit(f"caminho fora da pasta de saida: {name}")
        os.makedirs(os.path.dirname(target), exist_ok=True)
        with open(target, "wb") as handle:
            handle.write(blob[int(start):int(end)])
    print(f"{len(entries)} arquivos extraidos ({len(blob)} bytes)")


if __name__ == "__main__":
    main(*sys.argv[1:4])
