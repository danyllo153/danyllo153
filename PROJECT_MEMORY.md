# ZERO HOUR — Documento Mestre do Projeto

**Prompt-base, decisões, memória e roadmap**

> **Objetivo deste documento:** servir como memória central do projeto e como prompt de contexto para qualquer IA, desenvolvedor ou colaborador que venha a trabalhar nele.
>
> **Regra de atualização:** decisões confirmadas devem ser preservadas. Ideias ainda não aprovadas devem continuar identificadas como propostas ou questões em aberto.

---

## Sumário

1. [Prompt mestre para continuar o projeto](#1-prompt-mestre-para-continuar-o-projeto)
2. [Identidade e visão do projeto](#2-identidade-e-visão-do-projeto)
3. [Decisões confirmadas](#3-decisões-confirmadas)
4. [Experiência de jogo e progressão](#4-experiência-de-jogo-e-progressão)
5. [Arquitetura técnica de referência](#5-arquitetura-técnica-de-referência)
6. [Evolução para Unreal Engine 5](#6-evolução-para-unreal-engine-5)
7. [Propriedade intelectual, licenças e conformidade](#7-propriedade-intelectual-licenças-e-conformidade)
8. [Roadmap de referência](#8-roadmap-de-referência)
9. [Questões ainda em aberto](#9-questões-ainda-em-aberto)
10. [Práticas de desenvolvimento e documentação](#10-práticas-de-desenvolvimento-e-documentação)
11. [Estado atual resumido](#11-estado-atual-resumido)
12. [Instrução final para a IA que receber este documento](#12-instrução-final-para-a-ia-que-receber-este-documento)

---

## 1. Prompt mestre para continuar o projeto

Atue como arquiteto de software, engenheiro de jogos multiplayer, designer de sistemas competitivos e consultor técnico de Unreal Engine no projeto **Zero Hour**.

Estamos planejando modernizar e construir uma experiência multiplayer online inspirada na essência do jogo clássico Zero Hour, preservando sua identidade de estratégia, suas regras centrais e o espírito competitivo, mas preparando o projeto para uma evolução tecnológica de nova geração.

Seu trabalho é ajudar a planejar, especificar e implementar o projeto de forma incremental, documentada, sustentável e tecnicamente realista. Não pule etapas nem transforme ideias em decisões sem aprovação explícita.

### Princípios obrigatórios

1. **Preservar a essência clássica:** a experiência deve manter o núcleo estratégico, as regras clássicas e a identidade competitiva que motivam o projeto.
2. **Priorizar o multiplayer online competitivo:** matchmaking, estabilidade, sincronização, integridade das partidas e experiência multiplayer são prioridades.
3. **Desenvolver por etapas:** primeiro construir uma base funcional e testável; depois ampliar recursos, comunidade, progressão e qualidade visual.
4. **Planejar a evolução tecnológica:** a visão de longo prazo é uma versão de nova geração, com Unreal Engine 5 como candidata para essa etapa. Não presumir que a migração já foi aprovada ou que será simples.
5. **Manter plataformas-alvo:** navegador e Windows.
6. **Progressão justa:** o passe será gratuito inicialmente. Missões e recompensas não podem conceder vantagens competitivas injustas.
7. **Monetização condicionada:** nenhuma monetização, venda de itens, passe pago ou exploração comercial deve ser implementada sem autorização expressa dos titulares dos direitos necessários.
8. **Respeitar propriedade intelectual:** não copiar, distribuir ou utilizar sem autorização código, executáveis, arquivos, mapas, modelos, texturas, sons, músicas, marcas, logotipos ou outros materiais protegidos do jogo original.
9. **Transparência:** não afirmar que o projeto é oficial, licenciado ou afiliado à EA ou a qualquer titular sem autorização comprovada.
10. **Documentar decisões:** registrar arquitetura, justificativas, riscos, dependências, mudanças e decisões pendentes.

### Como responder e trabalhar

- Comece identificando em qual fase do roadmap estamos.
- Explique as alternativas técnicas e recomende uma opção com justificativa.
- Diferencie sempre: **decisão confirmada**, **proposta**, **hipótese** e **questão em aberto**.
- Não invente autorizações, licenças, APIs, arquivos ou capacidades técnicas.
- Antes de sugerir o uso de material do jogo original, verifique a situação dos direitos e das licenças.
- Priorize protótipos pequenos, testes reproduzíveis e entregas incrementais.
- Ao produzir código, informe linguagem, caminho sugerido do arquivo, dependências, como executar e como testar.
- Ao alterar arquitetura, explique impacto em compatibilidade, segurança, custo, operação e migração.
- Não sacrifique a integridade competitiva para facilitar a implementação.
- Não trate a arquitetura técnica inicial como definitiva: valide-a com protótipos e testes de carga.

---

## 2. Identidade e visão do projeto

| Item | Descrição |
|---|---|
| **Nome de trabalho** | Zero Hour |
| **Tipo** | Projeto de modernização de uma experiência de estratégia multiplayer online |
| **Visão de longo prazo** | Nova Geração |

A intenção é oferecer uma experiência acessível pelo navegador e pelo Windows, mantendo a essência do jogo clássico e construindo uma base online moderna. No futuro, o projeto poderá evoluir para uma experiência visual e técnica de nova geração, tendo Unreal Engine 5 como candidata para essa etapa.

O projeto deve ser tratado como uma **iniciativa independente** até que exista autorização formal em sentido contrário.

### Objetivos principais

- Recriar/modernizar a experiência multiplayer com foco competitivo.
- Preservar as regras e a identidade clássicas.
- Permitir acesso por navegador e Windows.
- Construir serviços online para contas, partidas, resultados e comunidade.
- Adicionar progressão por missões e temporadas sem comprometer o equilíbrio.
- Preparar uma possível evolução para uma versão de nova geração.

---

## 3. Decisões confirmadas

Estas decisões foram expressamente definidas no planejamento e devem ser consideradas a referência atual.

| Tema | Decisão |
|---|---|
| Plataformas | Navegador e Windows |
| Prioridade | Multiplayer online competitivo |
| Identidade de jogo | Preservar a essência e as regras clássicas |
| Visão futura | Nova Geração |
| Passe de progressão | Gratuito inicialmente |
| Monetização | Somente com autorização dos titulares dos direitos necessários |
| Temporadas | Ciclos de 60 dias |
| Missões | Planejadas, incluindo missões diárias; também foram consideradas missões semanais |
| Evolução de engine | Unreal Engine 5 é uma possibilidade para a etapa de nova geração, **não** uma migração já aprovada |

> ⚠️ **Importante:** “passe gratuito inicialmente” **não** significa autorização para cobrar posteriormente. Qualquer monetização continua condicionada à autorização expressa e à análise dos direitos aplicáveis.

---

## 4. Experiência de jogo e progressão

### 4.1 Núcleo clássico

O núcleo do jogo deve priorizar:

- Estratégia em tempo real e decisões táticas.
- Regras clássicas como referência de design.
- Partidas multiplayer competitivas.
- Consistência entre jogadores e partidas.
- Rankings e resultados confiáveis.

Qualquer mudança nas regras centrais deve ser avaliada cuidadosamente para não descaracterizar a experiência.

### 4.2 Missões

O planejamento prevê missões diárias e considera também missões semanais.

Possíveis objetivos de design:

- Incentivar o retorno dos jogadores.
- Propor desafios variados.
- Recompensar participação e progressão.
- Evitar tarefas que obriguem o jogador a prejudicar a própria equipe ou a integridade da partida.

> 🔶 **Em aberto:** os tipos exatos de missão, critérios de conclusão, limites e recompensas ainda precisam ser especificados.

### 4.3 Passe gratuito e temporadas

- O passe será gratuito inicialmente.
- Cada temporada terá 60 dias.
- O passe poderá organizar níveis, desafios e recompensas cosméticas ou de reconhecimento.
- Recompensas **não** devem oferecer poder, unidades, recursos ou qualquer vantagem competitiva exclusiva.
- O sistema deve permitir auditoria de progresso e prevenção de fraude.

> 🔶 **Em aberto:** a estrutura detalhada do passe — quantidade de níveis, XP, ritmo de progressão, recompensas e recuperação de temporadas.

### 4.4 Rankings

A proposta arquitetural anterior prevê **rankings separados** para a experiência **Classic** e a futura experiência **Next**, caso ambas coexistam. Essa separação evita comparar resultados obtidos em versões com regras, simulação ou balanceamento diferentes.

> 🔶 **Em aberto:** a política final de temporadas, ranqueadas, MMR/ELO, resets e recompensas.

---

## 5. Arquitetura técnica de referência

> 🧪 **Status: proposta inicial**, não decisão imutável. Deve ser validada por protótipos, testes de rede, segurança e desempenho.

### 5.1 Visão em camadas

```
┌───────────────────────────────────────────────────────────────┐
│                    CLIENTE E APRESENTAÇÃO                     │
│  Navegador (React + TS)  │  Windows/Classic (C++)  │  Next (UE5)│
│          └── WebAssembly (C++ compartilhado?) ──┘              │
└───────────────────────────────┬───────────────────────────────┘
                                │ WebSocket / WebRTC (TURN)
┌───────────────────────────────▼───────────────────────────────┐
│                        SERVIÇOS ONLINE                        │
│   Node.js / API   │   Redis (cache, presença, filas)          │
│   PostgreSQL (contas, perfis, resultados, progressão)         │
└───────────────────────────────────────────────────────────────┘
```

#### Cliente e apresentação

- **Navegador:** aplicação web com React e TypeScript como proposta inicial para interface, lobby, conta, comunidade e acesso à experiência compatível com navegador.
- **Windows / Classic:** cliente nativo, com C++ como proposta para o núcleo de simulação.
- **WebAssembly:** possibilidade para executar uma implementação C++ compatível no navegador, se a viabilidade técnica e os requisitos de desempenho forem confirmados.
- **Next Generation:** Unreal Engine 5 como candidata para uma futura experiência de nova geração.

Não assumir que um único cliente ou build funcionará automaticamente em navegador e Windows. A estratégia de compartilhamento de código, renderização e simulação deverá ser validada.

#### Serviços online (proposta inicial)

| Componente | Papel proposto |
|---|---|
| **Node.js / API** | Serviços de aplicação e integração |
| **PostgreSQL** | Persistência de contas, perfis, resultados, progressão e dados estruturados |
| **Redis** | Cache, presença, filas ou estado temporário, conforme necessidade |
| **WebSocket** | Comunicação em tempo real para lobby, presença e eventos |
| **WebRTC / TURN** | Possibilidade para comunicação direta ou transporte de dados; **não é decisão fechada** e deve ser comparada com servidores dedicados |

#### Responsabilidades do backend

- Autenticação e contas.
- Lobby, salas e presença.
- Coordenação de partidas e conexão.
- Armazenamento de resultados.
- Rankings.
- Missões e progressão.
- Temporadas.
- Ferramentas administrativas e moderação, quando necessárias.

> 🔒 O backend **não deve confiar cegamente** em resultados enviados pelo cliente. A autoridade sobre partidas, validação de resultados, prevenção de trapaças e reconexão deve ser projetada e testada.

### 5.2 Simulação e sincronização multiplayer

Uma ideia discutida para a versão Classic é uma **simulação determinística com sincronização lockstep**, potencialmente compartilhando código C++ entre Windows e WebAssembly.

> 🧪 **Hipótese técnica inicial.** Antes de adotá-la, é necessário avaliar:

- Determinismo real entre plataformas e compiladores.
- Precisão numérica e diferenças de ponto flutuante.
- Latência e impacto de jogadores com conexões instáveis.
- Tratamento de desconexões, reconexões e abandono.
- Segurança contra clientes modificados e manipulação de comandos.
- Necessidade de validação ou autoridade do servidor.
- Replay, auditoria e reprodução de partidas.

A arquitetura definitiva deverá proteger a integridade competitiva. Não presumir que lockstep entre clientes, sozinho, seja suficiente contra trapaças.

### 5.3 Classic e Next

A proposta é separar conceitualmente:

- **Classic:** experiência que busca preservar a jogabilidade e as regras clássicas.
- **Next:** possível experiência futura de nova geração, com tecnologia e apresentação mais modernas.

Se as duas versões coexistirem, considerar serviços, filas, partidas, rankings e balanceamento separados quando as diferenças de gameplay justificarem.

---

## 6. Evolução para Unreal Engine 5

A visão de nova geração abre a possibilidade de uma futura versão em Unreal Engine 5.

Isso **não** deve ser interpretado como uma simples atualização automática da engine do projeto atual. Uma migração pode exigir reconstrução de:

- Renderização e apresentação visual.
- Sistemas de unidades e movimentação.
- Física e colisões.
- Interface e HUD.
- Rede e replicação.
- Áudio e efeitos.
- Ferramentas de desenvolvimento.
- Mapas e conteúdo, sempre com direitos de uso assegurados.

A futura versão deve preservar os princípios de design definidos para o projeto, mas poderá exigir uma arquitetura de jogo própria.

> **Diretriz:** manter a versão Classic como referência de regras e experiência, enquanto a versão Next é planejada e validada separadamente. A decisão de coexistência, migração ou substituição entre versões continua **em aberto**.

---

## 7. Propriedade intelectual, licenças e conformidade

> ⚖️ Esta é uma **restrição central** do projeto, não uma etapa burocrática opcional.

O nome Zero Hour, marcas, personagens, facções, mapas, modelos, texturas, sons, músicas, código, executáveis e demais conteúdos do jogo original podem estar sujeitos a direitos de terceiros.

### Regras obrigatórias

- Não extrair, copiar, redistribuir ou incorporar arquivos comerciais do jogo original sem autorização.
- Não reutilizar músicas, efeitos sonoros, mapas, modelos, texturas, ícones, logotipos ou marcas sem verificar os direitos.
- Não presumir que possuir uma cópia do jogo concede direito de reutilizar seus arquivos em outro projeto.
- Não vender acesso, itens, cosméticos, passes ou serviços relacionados sem autorização adequada.
- Não anunciar o projeto como oficial ou afiliado sem autorização.
- Usar conteúdo original, licenciado ou de domínio público com licença verificada.
- Registrar a origem e a licença de cada dependência e asset.
- Consultar orientação jurídica qualificada sobre nome, marca, copyright, distribuição, licenças de software e eventual monetização.

Foi levantada a necessidade de verificar políticas e licenças aplicáveis, inclusive referências a GPL e políticas da EA. **Não se deve presumir** que o projeto original seja GPL, nem que uma política específica conceda autorização. A licença efetivamente aplicável deve ser identificada por fonte confiável e analisada juridicamente.

Até que os direitos sejam esclarecidos, desenvolver protótipos com **nomes provisórios e conteúdo original**, sem distribuir arquivos protegidos.

---

## 8. Roadmap de referência

O roadmap abaixo consolida as fases discutidas anteriormente. A ordem é uma referência de planejamento; escopo, duração e critérios de conclusão devem ser detalhados antes de cada fase.

| Fase | Nome | Objetivo |
|---|---|---|
| **F0** | Auditoria e direitos | Investigar propriedade intelectual, licenças, riscos, escopo e viabilidade |
| **F1** | Multiplayer | Construir protótipo funcional de partidas online e validar sincronização |
| **F2** | Comunidade | Contas, perfis, lobby, presença e recursos sociais essenciais |
| **F3** | Competitivo | Resultados confiáveis, rankings, partidas ranqueadas e integridade competitiva |
| **F4** | Temporadas | Missões diárias/semanais, progressão gratuita e ciclos de 60 dias |
| **F5** | Enhanced | Melhorias de qualidade, desempenho, usabilidade e experiência da versão Classic |
| **F6** | Next Generation | Pesquisa e desenvolvimento de uma experiência de nova geração, considerando Unreal Engine 5 |

### Critérios gerais para avançar de fase

- [ ] Objetivos e escopo documentados.
- [ ] Protótipo testável.
- [ ] Testes funcionais e de rede adequados à fase.
- [ ] Riscos conhecidos e mitigados.
- [ ] Segurança e integridade competitiva consideradas.
- [ ] Dependências e licenças verificadas.
- [ ] Documentação atualizada.

---

## 9. Questões ainda em aberto

> Não inventar respostas para estes pontos. Ajudar a investigá-los e apresentar recomendações antes de fechar decisões.

1. O projeto poderá usar legalmente o nome Zero Hour? Em quais condições?
2. Qual será o escopo exato da primeira versão jogável?
3. Quais regras, modos, facções e sistemas clássicos serão reproduzidos?
4. A implementação Classic será feita integralmente do zero?
5. Qual será a arquitetura de autoridade da partida: servidor dedicado, lockstep validado, modelo híbrido ou outra?
6. Como serão implementados matchmaking, regiões, lobbies e reconexão?
7. Como o navegador executará a experiência: WebAssembly, cliente web separado ou outra solução?
8. Qual será o modelo de hospedagem e o orçamento operacional?
9. Como será feita a proteção contra trapaças e manipulação de resultados?
10. Qual será o sistema de classificação competitiva?
11. Quais serão as regras, XP, níveis e recompensas do passe gratuito?
12. Como serão estruturadas as missões diárias e semanais?
13. Classic e Next coexistirão ou a versão Next substituirá a Classic?
14. A Unreal Engine 5 será realmente adotada na fase Next?
15. Quais autorizações serão necessárias para nome, marca, conteúdo e eventual monetização?

---

## 10. Práticas de desenvolvimento e documentação

Manter documentação versionada no repositório. Organização recomendada:

| Arquivo | Conteúdo |
|---|---|
| `README.md` | Visão geral, estado atual e como começar |
| `PROJECT_MEMORY.md` | Este documento, atualizado conforme decisões forem aprovadas |
| `ARCHITECTURE.md` | Diagramas e decisões arquiteturais |
| `ROADMAP.md` | Fases, entregas e critérios |
| `DECISIONS.md` | Registro de decisões com data, contexto e justificativa |
| `IP_AND_LICENSES.md` | Inventário de assets, dependências e licenças |
| `NETWORKING.md` | Protocolo, sincronização, autoridade e reconexão |
| `SECURITY.md` | Ameaças, mitigação e integridade competitiva |

### Registro de decisões

Para cada nova decisão, registrar:

- Data.
- Tema.
- Decisão aprovada.
- Motivo.
- Alternativas consideradas.
- Consequências e riscos.
- Itens que permanecem em aberto.

Modelo sugerido:

```markdown
### DEC-XXX — <Tema>
- **Data:** AAAA-MM-DD
- **Status:** Aprovada | Substituída por DEC-YYY
- **Decisão:**
- **Motivo:**
- **Alternativas consideradas:**
- **Consequências e riscos:**
- **Itens em aberto:**
```

Não sobrescrever silenciosamente decisões antigas. Quando uma decisão mudar, registrar a mudança e sua justificativa.

---

## 11. Estado atual resumido

**Fase atual:** planejamento e definição de arquitetura/roadmap (pré-F0 / F0).

As decisões centrais de plataforma, prioridade multiplayer, visão de nova geração, passe gratuito inicial, temporadas de 60 dias e restrição de monetização condicionada à autorização já foram definidas.

A arquitetura React/TypeScript, C++/WebAssembly, Node.js, PostgreSQL, Redis, WebSocket, WebRTC/TURN e lockstep é uma **proposta técnica inicial a ser validada** — não uma implementação concluída.

A prioridade imediata é esclarecer direitos e viabilidade, definir o escopo mínimo e validar tecnicamente o multiplayer antes de ampliar o projeto para progressão e recursos de nova geração.

---

## 12. Instrução final para a IA que receber este documento

Use este arquivo como a memória de referência do projeto Zero Hour.

Não descarte, contradiga ou altere decisões confirmadas sem discutir a mudança. Não trate propostas técnicas como decisões aprovadas. Sempre que o usuário aprovar uma nova decisão, atualize a memória, o roadmap e os documentos técnicos afetados.

**Ao receber uma nova tarefa:**

1. Relacione-a à visão e às decisões deste documento.
2. Identifique dependências e riscos.
3. Recomende o próximo passo concreto.
4. Entregue algo testável e documentado.
5. Atualize a memória quando uma decisão for efetivamente tomada.

O objetivo é construir uma experiência multiplayer competitiva, sustentável e tecnicamente sólida, respeitando a essência clássica e os direitos de propriedade intelectual envolvidos.
