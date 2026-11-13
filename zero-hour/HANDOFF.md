# HANDOFF — Zero Hour (estado em 2026-11-13)

> Leia este arquivo primeiro ao retomar o projeto numa conversa nova.
> Depois leia o [PROJECT_MEMORY.md](PROJECT_MEMORY.md) (regras e princípios) e o [DECISIONS.md](DECISIONS.md) (decisões completas).

## Onde está tudo

- **Repositório:** `danyllo153/danyllo153`, branch `claude/serene-newton-2z4se1` (sem pull request aberto).
- **Pasta do projeto:** `zero-hour/`. O `README.md` da raiz é o perfil do GitHub; não mexer.

| Arquivo | Conteúdo |
|---|---|
| `PROJECT_MEMORY.md` | Documento mestre: prompt-base, princípios, questões em aberto |
| `DECISIONS.md` | DEC-001 a DEC-012 |
| `ROADMAP.md` | Fases F0–F6 + **trilha Classic C1–C9** |
| `ARCHITECTURE.md`, `NETWORKING.md`, `SECURITY.md` | Propostas técnicas (🧪, não aprovadas) |
| `IP_AND_LICENSES.md` | Direitos, termos da GPL da EA, inventários |
| `unreal/RTSProto/` | Protótipo UE5 em C++ (**pausado**, nunca compilado) |

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

## O que a pesquisa descobriu

1. **Não existe Zero Hour público em UE5.** Só vídeos de projetos privados.
2. **A EA liberou o código de Generals e Zero Hour em 27/02/2025**, sob GPL v3 com termos adicionais ([repositório](https://github.com/electronicarts/CnC_Generals_Zero_Hour)):
   - Não concede marcas da EA: nada de "Command & Conquer" no nome.
   - Proíbe afirmar afiliação com a EA.
   - Versões modificadas devem ser marcadas como tal, sem se apresentar como o original.
   - Manter o aviso de copyright e os termos em qualquer distribuição.
   - Só o código: **arquivos do jogo não estão incluídos**. O jogador usa a própria cópia (por exemplo, Steam). **Nós não hospedamos arquivos do jogo.**
3. **Código GPL não pode ser usado com o UE5.** Por isso a versão UE5 tem de ser escrita do zero.
4. **Já existem ports do motor original para o navegador (WebAssembly):**

| Projeto | Estado | Multiplayer |
|---|---|---|
| [Lolendor/Generals-WebAssembly](https://github.com/Lolendor/Generals-WebAssembly) | Jogável, mais de 2.000 commits | WebRTC com salas, em desenvolvimento. ⚠️ Prevê que quem publica hospede os arquivos do jogo: **não fazer isso** |
| [TheodoryLabs/command-and-conquer-generals-zero-hour-web](https://github.com/TheodoryLabs/command-and-conquer-generals-zero-hour-web) | Parcial (skirmish, sem áudio) | Não; tem ponto preparado para WebRTC |
| [meerzulee/GeneralsXWeb](https://github.com/meerzulee/GeneralsXWeb) | Experimental, 1024×768 | Não |
| openzh, wasm-generals, scr2em | Iniciais ou pausados | — |

5. **Comunidade no Windows:** [TheSuperHackers/GeneralsGameCode](https://github.com/TheSuperHackers/GeneralsGameCode) (base comunitária do código da EA) e Generals Online (multiplayer moderno em cima dela).

## Pendências do usuário (bloqueiam a C1)

- [ ] **Escolher a base:**
  - **Lolendor** (recomendação provisória): mais avançado, multiplayer em andamento. Falta confirmar que compila também para Windows a partir do mesmo código.
  - **TheodoryLabs** (alternativa): menos avançado, mas mais perto do TheSuperHackers no Windows, o que pode facilitar o crossplay.
- [ ] **Fazer o fork no GitHub** com um nome **sem marcas da EA** e passar o nome do repositório. Depois, a IA usa `add_repo` para adicioná-lo à sessão. O motor fica num repositório próprio em GPL, separado do perfil.
- [ ] **Ter o jogo comprado** para testar (a IA não pode usar arquivos do jogo).
- [ ] Definir o **nome público** do projeto.

## Próximo passo técnico (C1)

1. Clonar o fork escolhido e compilar para **Web** (Emscripten) e para **Windows** a partir do mesmo código.
2. Confirmar uma partida skirmish contra a IA nos dois, com os arquivos do próprio jogador.
3. Fazer um teste de determinismo: mesmo replay em Windows e no navegador deve dar o mesmo CRC. **É o maior risco do crossplay.**
4. Depois seguir C2–C9 no [ROADMAP.md](ROADMAP.md).

## Regras que não podem ser esquecidas

- Distinguir sempre **decisão confirmada**, **proposta**, **hipótese** e **questão em aberto**.
- Não hospedar nem distribuir arquivos do jogo original.
- Não usar marcas da EA no nome nem afirmar afiliação.
- Nenhuma monetização (DEC-006).
- Nova decisão aprovada → registrar em `DECISIONS.md` e atualizar `PROJECT_MEMORY.md`, `ROADMAP.md` e este handoff.
- Commits só no branch `claude/serene-newton-2z4se1`; não abrir PR sem pedido.

## Prompt para retomar

```
Leia zero-hour/HANDOFF.md, depois zero-hour/PROJECT_MEMORY.md e zero-hour/DECISIONS.md
no repositório danyllo153/danyllo153 (branch claude/serene-newton-2z4se1).
Escolhi a base <Lolendor | TheodoryLabs> e meu fork é <usuario/repositorio>.
Vamos começar a etapa C1 da trilha Classic.
```
