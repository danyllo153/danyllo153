# Classic Web: jogar com um amigo pelo Tailscale

Roda a versão web (WebAssembly + WebGPU) **no seu PC** e a publica **só para a sua rede Tailscale**, com HTTPS. Você e seu amigo jogam pelo navegador e se encontram no **multiplayer LAN** do jogo. Custo: R$ 0.

```
Seu PC (Windows)
 ├─ serve-webgpu.py  →  http://127.0.0.1:8766   página + motor + relay do multiplayer
 └─ tailscale serve  →  https://<seu-pc>.<tailnet>.ts.net:8765   (só a sua tailnet enxerga)
        ▲                          ▲
     você (Chrome/Edge)        amigo (Chrome/Edge, via Tailscale)
```

Os arquivos do jogo (`.big`) **não passam pelo servidor**: cada um escolhe, no navegador, a pasta da **própria** cópia do Zero Hour.

## O que cada um precisa

| | Você (host) | Amigo |
|---|---|---|
| Zero Hour instalado (Ultimate Collection) | ✅ | ✅ |
| Chrome ou Edge atualizado (WebGPU) | ✅ | ✅ |
| Tailscale instalado e logado | ✅ | ✅ |
| Python 3.10+ ([python.org](https://www.python.org/downloads/), marque *Add to PATH*) | ✅ | — |

## 1. Configurar o Tailscale (uma vez, no painel)

1. Entre em [login.tailscale.com/admin/dns](https://login.tailscale.com/admin/dns).
2. Ligue **MagicDNS** e, mais abaixo, **HTTPS Certificates**.
3. Dar acesso ao amigo (escolha **um**):
   - **Compartilhar só o seu PC (recomendado):** em [Machines](https://login.tailscale.com/admin/machines), clique nos `…` do seu PC → **Share…** → mande o convite. Ele só enxerga essa máquina.
   - **Convidar para a sua rede:** em [Users](https://login.tailscale.com/admin/users) → **Invite users**.

## 2. Instalar (uma vez, no seu PC)

Baixe esta pasta `classic-web` e, dentro dela, no PowerShell:

```powershell
powershell -ExecutionPolicy Bypass -File .\instalar.ps1
```

Baixa ~20 MB para `%USERPROFILE%\ZeroHourWeb`, de um commit fixo do projeto [origami-ltd/wasm-generals](https://github.com/origami-ltd/wasm-generals), conferindo o SHA-256 de cada arquivo. Também remove o Google Analytics da página.

## 3. Ligar o servidor (toda vez que forem jogar)

```powershell
powershell -ExecutionPolicy Bypass -File .\iniciar.ps1
```

Ele mostra (e copia) um link como `https://meu-pc.tail1234.ts.net:8765/`. Mande para o amigo.

Para desligar:

```powershell
powershell -ExecutionPolicy Bypass -File .\parar.ps1
```

## 4. Jogar

1. **Os dois** abrem o link `https://…ts.net:8765/` no Chrome ou Edge. Você também usa esse link, não `localhost`, para cair no mesmo relay.
2. Na primeira vez, a página pede a pasta do jogo. Escolha a pasta onde estão os `*ZH.big`.
   - O navegador bloqueia pastas dentro de `C:\Program Files`. Se reclamar, copie as pastas do **Generals** e do **Zero Hour** para algo como `C:\Jogos\` e escolha `C:\Jogos`: a página acha as duas sozinha.
3. No jogo: **Multiplayer → Network (LAN)**. Um cria a partida, o outro entra.

## Problemas comuns

| Sintoma | Causa provável |
|---|---|
| `tailscale serve` falha | HTTPS Certificates desligado no painel (passo 1.2) |
| Página abre mas diz que falta WebGPU ou SharedArrayBuffer | Navegador sem WebGPU (use Chrome/Edge atualizado) ou aberto por `http://` |
| O amigo não abre o link | Ele não está logado no Tailscale ou o compartilhamento não foi aceito |
| A partida não aparece na lista LAN | Um dos dois abriu por outro endereço. Os dois devem usar exatamente o mesmo link `…ts.net:8765` |
| Ver quem está conectado no relay | Abra `https://…ts.net:8765/GeneralsXLanStatus` |

## Licenças e créditos

- **Motor:** GPL-3.0 com os termos adicionais da EA, derivado de [GeneralsX](https://github.com/fbraz3/GeneralsX) e do [código liberado pela EA](https://github.com/electronicarts/CnC_Generals_Zero_Hour). Código-fonte do binário usado: [origami-ltd/wasm-generals @ 46382a3](https://github.com/origami-ltd/wasm-generals/tree/46382a383da270e16a60a28ecf342b569b998111).
- **Página web:** licença MIT-PoU do projeto wasm-generals, que pede crédito: *Includes material from origami-ltd/wasm-generals — https://generals.wasm.ltd*.
- O pacote `GeneralsXZH.data` do projeto original traz alguns arquivos pequenos do jogo (cursores e scripts de IA). Por isso esta configuração é **privada** (só a sua tailnet) e **não deve virar um site público**, e esses binários **não são guardados neste repositório**.
- Projeto independente, sem afiliação nem endosso da EA. Marcas pertencem aos seus donos.
