"""Reescreve a tabela de arquivos do GeneralsXZH.js para apontar para o GeneralsXZH.data original.

O .data do wasm-generals embute alguns arquivos do jogo (cursores, scripts da IA e uma fonte). Nao
redistribuimos esse arquivo: o instalar.ps1 baixa o original do projeto upstream. Esta ferramenta
pega o .js da nossa build e troca as posicoes (start/end) e o tamanho do pacote pelos do .js
original, arquivo por arquivo, pelo nome. Assim o nosso .js le o .data original sem alteracao.

Uso: python match_data_package.py NOSSO.js ORIGINAL.js SAIDA.js
"""
import re
import sys

ENTRY = re.compile(r'\{filename:"([^"]+)",start:(\d+),end:(\d+)\}')
SIZE = re.compile(r'remote_package_size:(\d+)')


def table(text):
    return {name: (int(a), int(b)) for name, a, b in ENTRY.findall(text)}


def main(ours_path, upstream_path, out_path):
    ours = open(ours_path, encoding="utf-8").read()
    upstream = open(upstream_path, encoding="utf-8").read()
    want, have = table(upstream), table(ours)
    if set(want) != set(have):
        sys.exit(f"listas de arquivos diferentes: so no original={sorted(set(want) - set(have))} "
                 f"so na build={sorted(set(have) - set(want))}")
    if len(ENTRY.findall(ours)) != len(have):
        sys.exit("nome de arquivo repetido na tabela da build")
    ours = ENTRY.sub(lambda m: '{filename:"%s",start:%d,end:%d}' % ((m.group(1),) + want[m.group(1)]), ours)
    sizes = SIZE.findall(upstream)
    if len(set(sizes)) != 1 or len(SIZE.findall(ours)) == 0:
        sys.exit("tamanho do pacote nao encontrado")
    ours = SIZE.sub("remote_package_size:" + sizes[0], ours)
    for name, (a, b) in want.items():
        if b - a != have[name][1] - have[name][0]:
            sys.exit(f"tamanho diferente para {name}: o arquivo de origem nao e o mesmo")
    open(out_path, "w", encoding="utf-8").write(ours)
    print(f"{len(want)} arquivos remapeados; pacote = {sizes[0]} bytes")


if __name__ == "__main__":
    main(*sys.argv[1:4])
