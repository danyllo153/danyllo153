# HANDOFF — Zero Hour (estado em 2026-11-15)

> Leia este arquivo primeiro ao retomar o projeto numa conversa nova.
> Depois leia o [PROJECT_MEMORY.md](PROJECT_MEMORY.md) (regras e princípios) e o [DECISIONS.md](DECISIONS.md) (decisões completas).

## Resumo em 30 segundos

- **Já é jogável:** o Zero Hour roda no navegador do responsável, servido pelo PC dele e publicado **só na tailnet** do Tailscale (HTTPS, porta 8765), com relay de multiplayer LAN. Cada jogador usa a **própria cópia** do jogo (Ultimate Collection no EA app).
- **Motor próprio:** patch sobre o [origami-ltd/wasm-generals](https://github.com/origami-ltd/wasm-generals) com **2K/4K**, versão **rápida** (JSPI + exceções nativas de WebAssembly) e **sem o limite de 60 FPS**. Compilado pelo **GitHub Actions** e publicado na release **`motor-web`** deste repositório (só `.js` e `.wasm`, sem arquivos da EA).
- **Confirmado pelo responsável:** motor `rapida` roda, oferece **2560×1440** e o limite de 60 FPS saiu. Antes: 38 FPS (motor original, 1080p, partida longa). Depois: 42 FPS com **velocidade da partida acelerada ([80])** em 1440p, então ainda falta uma medição justa em velocidade normal ([30]).
- **Ainda não testado:** partida LAN real com o amigo.

## Onde está tudo

- **Repositório:** `danyllo153/danyllo153`, branch `claude/serene-newton-2z4se1` (sem pull request aberto).
- **Pasta do projeto:** `zero-hour/`. O `README.md` da raiz é o perfil do GitHub; não mexer.

| Caminho | Conteúdo |
|---|---|
| `PROJECT_MEMORY.md` | Documento mestre: prompt-base, princípios, questões em aberto |
| `DECISIONS.md` | DEC-001 a DEC-013 |
| `ROADMAP.md` | Fases F0–F6 + **trilha Classic C1–C9** |
| `ARCHITECTURE.md`, `NETWORKING.md`, `SECURITY.md` | Propostas técnicas (🧪, não aprovadas) |
| `IP_AND_LICENSES.md` | Direitos, termos da GPL da EA, inventários |
| `classic-web/` | **O que está em uso:** scripts Windows (`instalar.ps1`, `iniciar.ps1`, `parar.ps1`) e guia ([README](classic-web/README.md)) |
| `classic-web/engine/` | Patch do motor (`zh-resolucao-desempenho.patch`), ferramentas do pacote `.data` e [README](classic-web/engine/README.md) |
| `.github/workflows/motor-web.yml` | Compila as versões `compat` e `rapida` e publica a release `motor-web` |
| `unreal/RTSProto/` | Protótipo UE5 em C++ (**pausado**, nunca compilado) |

## Como funciona o `classic-web` (estado atual)

```
PC do responsável (Windows)
 ├─ %USERPROFILE%\ZeroHourWeb\www      página + motor (instalar.ps1)
 ├─ serve-webgpu.py → 127.0.0.1:8766   página, relay LAN (/GeneralsXLan), cabeçalhos COOP/COEP
 └─ tailscale serve → https://<pc>.<tailnet>.ts.net:8765   (só a tailnet; o amigo entra por "Share…")
```

- `instalar.ps1 [-Versao original|compat|rapida]`:
  - baixa a página e o `.data` do wasm-generals no commit `46382a3`, conferindo o SHA-256;
  - remove o Google Analytics e os botões de doação/wasm.ltd/GitHub, deixando um rodapé de crédito (exigido pela GPL e pela licença MIT-PoU da página);
  - troca `.js`/`.wasm` pelos da release `motor-web` (`compat` ou `rapida`, conferindo `SHA256SUMS-<versao>.txt`).
- O **`.data` original** traz alguns arquivos da EA (cursores, scripts da IA, uma fonte). Por isso: só tailnet, nunca site público; nunca guardar `.data` neste repositório. Nossa build usa `match_data_package.py` para ler esse mesmo `.data` sem redistribuí-lo.
- Porta pública **8765** é obrigatória: o motor procura o relay em `wss://<host>:8765/GeneralsXLan`.
- A janela do Python precisa ficar aberta enquanto jogam.
- `?fpscap=1` no link volta ao ritmo antigo de 60 FPS (versão `rapida`).

## Motor (`classic-web/engine/zh-resolucao-desempenho.patch`)

| Mudança | Arquivo no wasm-generals |
|---|---|
| Resoluções 2560×1440 e 3840×2160 + contagem de modos tirada da tabela (estava fixa em 6) | `Core/GameEngineDevice/Source/WebGPUDevice/WebGPUD3D8.cpp` |
| Tamanho da tela físico (CSS × `devicePixelRatio`), para não esconder 1440p em monitor com escala de 125% | `GeneralsMD/.../W3DDevice/GameClient/W3DDisplay.cpp` |
| Opção `GENERALSX_WEB_JSPI` (JSPI + `-fwasm-exceptions` + setjmp nativo) | `cmake/webgpu.cmake`, `GeneralsMD/Code/Main/CMakeLists.txt` |
| Laço de quadros em JS via export `GeneralsXPump`: `requestAnimationFrame` + temporizador reserva de 16 ms quando o rAF para há 50 ms (LAN não dessincroniza) | `GeneralsMD/Code/GameEngineDevice/Source/SDL3GameEngine.cpp` |
| Triplet do vcpkg `wasm32-emscripten-wasmeh` + toolchain que injeta os flags (o vcpkg ignora `VCPKG_C_FLAGS` com toolchain encadeado) | `triplets/` |

- Toolchain: Emscripten **6.0.2**, vcpkg no commit `533a5fd`.
- `compat` ≈ 15 MB de `.wasm`; `rapida` ≈ 7,3 MB (sem a instrumentação do Asyncify).
- **Atenção:** qualquer push que mexa em `zero-hour/classic-web/engine/**` ou no workflow recompila (≈ 7–8 min) e **substitui** a release `motor-web`.
- **Este ambiente de nuvem não compila o motor:** o proxy bloqueia os downloads de arquivos do GitHub que o vcpkg usa. Compile pelo workflow; acompanhe pelas ferramentas `mcp__github__actions_*`.

## Decisões em vigor (resumo)

| ID | Decisão |
|---|---|
| DEC-001 | Plataformas: navegador e Windows |
| DEC-002 | Prioridade: multiplayer online competitivo |
| DEC-003 | Preservar a essência e as regras clássicas |
| DEC-004 | Visão de longo prazo: Nova Geração |
| DEC-005 | Passe gratuito; recompensas sem vantagem competitiva |
| DEC-006 | Nenhuma monetização sem autorização dos titulares dos direitos |
| DEC-007 | Temporadas de 60 dias |
| DEC-008 | Missões diárias (semanais só consideradas) |
| DEC-009 | ~~UE5 só como candidata~~ → substituída pela DEC-010 |
| DEC-010 | Versão UE5 para Windows, escrita do zero, com nome e conteúdo originais. **Adiada para a F6** |
| DEC-011 | **Classic primeiro:** navegador + Windows com **crossplay**, foco em multiplayer, ranqueada e melhoria gráfica |
| DEC-012 | Resoluções **1080p, 1440p (2K) e 2160p (4K)** |
| DEC-013 | **Primeiro jogável:** wasm-generals servido no PC do responsável e publicado só na tailnet (`classic-web/`). Desde 2026-11-15 com **motor próprio** (patch + release `motor-web`) |

## Pesquisa (resumo)

1. **Não existe Zero Hour público em UE5.** Código GPL não pode ser usado com o UE5; a versão UE5 tem de ser escrita do zero.
2. **A EA liberou o código de Generals e Zero Hour em 27/02/2025** (GPL v3 + termos adicionais, [repositório](https://github.com/electronicarts/CnC_Generals_Zero_Hour)): sem marcas da EA no nome, sem afirmar afiliação, versões modificadas marcadas como tal, manter avisos. **Arquivos do jogo não incluídos: nós não hospedamos.**
3. **Ports para o navegador:**

| Projeto | Estado |
|---|---|
| [origami-ltd/wasm-generals](https://github.com/origami-ltd/wasm-generals) (base GeneralsX) | **Em uso.** Jogo completo, WebGPU, LAN por relay WebSocket. Página depende de pacotes privados (`@wasm/runtime`, `@wasm/shell`): só o `web/dist` pronto é utilizável. Página sob MIT-PoU (exige crédito) |
| [Lolendor/Generals-WebAssembly](https://github.com/Lolendor/Generals-WebAssembly) | Jogável, multiplayer WebRTC em desenvolvimento. ⚠️ Prevê hospedar os arquivos do jogo: **não fazer isso** |
| [TheodoryLabs/...-web](https://github.com/TheodoryLabs/command-and-conquer-generals-zero-hour-web) | Parcial (skirmish, sem áudio) |
| [meerzulee/GeneralsXWeb](https://github.com/meerzulee/GeneralsXWeb) | Experimental |

4. **Windows:** [TheSuperHackers/GeneralsGameCode](https://github.com/TheSuperHackers/GeneralsGameCode) e Generals Online.

## Pendências

**Do responsável (testes):**
- [ ] Partida **LAN com o amigo** (cópia própria + Tailscale + convite "Share…" da máquina, não da tailnet inteira, porque nela há outro servidor).
- [ ] Medir FPS do `rapida` em partida longa com velocidade normal (**[30]** no contador) e comparar com os 38 do original.
- [ ] Ver se a interface fica legível em 1440p.
- [ ] Definir o **nome público** do projeto.

**Melhorias propostas (aguardando escolha):**

| # | Melhoria | Esforço |
|---|---|---|
| 1 | `iniciar.ps1` atualiza o motor sozinho a partir da release | Pequeno |
| 2 | Otimizações extras do motor (LTO, SIMD), como 3ª versão para comparar | Pequeno |
| 3 | Atalhos na área de trabalho (**sem** iniciar com o Windows: o responsável recusou isso) | Pequeno |
| 4 | Escala da interface em 1440p/4K | Médio |
| 5 | Página em português e com nome próprio | Médio |
| 6 | **Site público sem Tailscale:** tirar os arquivos da EA do `.data` (ler cursores e scripts da pasta do jogador) + relay na internet (Fly.io grátis ou VPS ~US$ 5/mês) | Grande |
| 7 | Lobby, ranking, temporadas (C2–C9) | Grande, depende do 6 |
| 8 | Crossplay com o jogo nativo no Windows (determinismo/CRC) | Grande, maior risco |

Sugestão já dada: **1 + 2** agora; **6** depois do teste com o amigo.

## Regras que não podem ser esquecidas

- Distinguir sempre **decisão confirmada**, **proposta**, **hipótese** e **questão em aberto**.
- Não hospedar nem distribuir arquivos do jogo original (incluindo o `.data` do wasm-generals).
- Não usar marcas da EA no nome nem afirmar afiliação.
- Manter o rodapé de crédito/código-fonte na página.
- Nenhuma monetização (DEC-006).
- Nova decisão aprovada → registrar em `DECISIONS.md` e atualizar `PROJECT_MEMORY.md`, `ROADMAP.md` e este handoff.
- Commits só no branch `claude/serene-newton-2z4se1`; não abrir PR sem pedido.
- O usuário fala português; respostas em português.

## Prompt para retomar

```
Leia zero-hour/HANDOFF.md no repositório danyllo153/danyllo153
(branch claude/serene-newton-2z4se1), depois zero-hour/PROJECT_MEMORY.md e zero-hour/DECISIONS.md.
O classic-web já roda (motor rapida, 2K, sem limite de 60 FPS).
Quero seguir com a melhoria <número da tabela de melhorias>.
```
