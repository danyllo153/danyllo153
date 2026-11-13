# Arquitetura — Zero Hour

> 🧪 **Status: proposta inicial.** Nada neste documento é decisão definitiva. Cada componente precisa ser validado por protótipos, testes de rede, de segurança, de desempenho e de carga antes de ser aprovado em [DECISIONS.md](DECISIONS.md).

## 1. Restrições que a arquitetura deve respeitar

Estas vêm de decisões já confirmadas (ver [DECISIONS.md](DECISIONS.md)):

| Restrição | Origem |
|---|---|
| Rodar no **navegador** e no **Windows** | ✅ DEC-001 |
| Priorizar **multiplayer online competitivo** | ✅ DEC-002 |
| Preservar a **essência e as regras clássicas** | ✅ DEC-003 |
| Permitir uma futura versão **Nova Geração** | ✅ DEC-004 / DEC-009 |
| Progressão sem **vantagem competitiva** | ✅ DEC-005 |
| Nenhum fluxo de **monetização** sem autorização | ✅ DEC-006 |

## 2. Visão em camadas

```
┌──────────────────────────────────────────────────────────────────┐
│                     CLIENTE E APRESENTAÇÃO                       │
│                                                                  │
│  ┌────────────────┐  ┌──────────────────┐  ┌──────────────────┐  │
│  │ Web (React+TS) │  │ Windows / Classic│  │ Next (UE5?)      │  │
│  │ lobby, conta,  │  │ cliente nativo   │  │ futura, separada │  │
│  │ comunidade     │  │ C++              │  │                  │  │
│  └───────┬────────┘  └────────┬─────────┘  └────────┬─────────┘  │
│          │   ┌────────────────┴─────────┐           │            │
│          └──►│ Núcleo de simulação C++  │           │            │
│              │ (WebAssembly no browser?)│           │            │
│              └──────────────────────────┘           │            │
└──────────────────────────┬──────────────────────────┬────────────┘
                           │ WebSocket / WebRTC+TURN  │
┌──────────────────────────▼──────────────────────────▼────────────┐
│                        SERVIÇOS ONLINE                           │
│                                                                  │
│  API Node.js: contas · lobby · partidas · resultados · rankings  │
│               missões · temporadas · moderação                   │
│                                                                  │
│  ┌────────────────────┐   ┌──────────────────────────────────┐   │
│  │ Redis              │   │ PostgreSQL                       │   │
│  │ presença, filas,   │   │ contas, perfis, resultados,      │   │
│  │ cache, sessões     │   │ progressão, temporadas, auditoria│   │
│  └────────────────────┘   └──────────────────────────────────┘   │
│                                                                  │
│  (?) Servidores de partida / relay / validação: em aberto        │
└──────────────────────────────────────────────────────────────────┘
```

## 3. Componentes

### 3.1 Cliente

| Componente | Proposta | Status | O que validar |
|---|---|---|---|
| Interface web | React + TypeScript | 🧪 | Desempenho do lobby, acessibilidade, integração com o núcleo |
| Cliente Windows (Classic) | C++ nativo | 🧪 | Toolchain, distribuição, atualização automática |
| Núcleo de simulação | C++ compartilhado | 🧪 | Determinismo entre compiladores e plataformas |
| Execução no navegador | WebAssembly | 🧪 | Desempenho, tamanho do download, threads, memória |
| Next Generation | Unreal Engine 5 | 🧪 | Ver seção 6 do [PROJECT_MEMORY.md](PROJECT_MEMORY.md) |

> ⚠️ Não assumir que um único build serve navegador e Windows. Renderização, entrada, áudio e rede podem precisar de implementações separadas por plataforma.

### 3.2 Serviços online

| Componente | Papel proposto | Status |
|---|---|---|
| API Node.js | Regras de aplicação, autenticação, orquestração | 🧪 |
| PostgreSQL | Dados persistentes e auditáveis | 🧪 |
| Redis | Presença, filas de matchmaking, cache, estado temporário | 🧪 |
| WebSocket | Tempo real para lobby, presença e eventos | 🧪 |
| WebRTC / TURN | Transporte direto entre jogadores, se adotado | 🧪 comparar com servidor dedicado |

### 3.3 Responsabilidades do backend

- Autenticação e contas.
- Lobby, salas e presença.
- Coordenação de partidas e conexão.
- Armazenamento e **validação** de resultados.
- Rankings (separados para Classic e Next, se ambas coexistirem).
- Missões, progressão e temporadas de 60 dias.
- Ferramentas administrativas e moderação.

> 🔒 O backend **nunca** confia cegamente em resultados enviados pelo cliente. Ver [SECURITY.md](SECURITY.md).

## 4. Modelo de autoridade da partida

🔶 **Questão em aberto central.** Detalhes em [NETWORKING.md](NETWORKING.md).

| Alternativa | Resumo |
|---|---|
| A. Lockstep P2P puro | Clientes trocam comandos; nenhum servidor simula |
| B. Lockstep com relay e validação | Servidor repassa comandos, registra a partida e pode re-simular para validar |
| C. Servidor dedicado autoritativo | Servidor simula; clientes enviam entradas e recebem estado |
| D. Híbrido | Lockstep para casuais; validação ou servidor autoritativo para ranqueadas |

**Recomendação provisória:** prototipar **B** primeiro. Ela preserva o modelo clássico de RTS (muitas unidades, pouca banda), mantém um registro confiável de cada partida e permite validar resultados ranqueados re-simulando no servidor. Isso só vale se o determinismo for comprovado na F1. Se não for, reavaliar C.

## 5. Modelo de dados inicial (rascunho)

🧪 Apenas para orientar protótipos.

| Entidade | Campos principais |
|---|---|
| `account` | id, nome de exibição, credenciais, criado_em, status |
| `profile` | account_id, avatar, preferências |
| `match` | id, modo (classic/next), versão da simulação, mapa, início, fim, status |
| `match_player` | match_id, account_id, equipe, resultado, desconectou_em |
| `match_log` | match_id, hash da sequência de comandos, local do replay |
| `rating` | account_id, fila, temporada, valor, incerteza |
| `season` | id, início, fim (60 dias), modo |
| `mission` | id, tipo (diária/semanal), critério, recompensa cosmética |
| `mission_progress` | account_id, mission_id, progresso, concluída_em, origem (match_id) |
| `audit_event` | quem, o quê, quando, antes/depois |

Princípio: todo progresso e toda mudança de ranking aponta para a partida que o gerou (`match_id`), para permitir auditoria.

## 6. Classic e Next

- **Classic:** referência de regras e experiência.
- **Next:** desenvolvimento separado, com arquitetura de jogo própria se necessário.
- Se coexistirem: filas, rankings, balanceamento e versões de simulação separados.

🔶 Coexistência, migração ou substituição continua em aberto.

## 7. Critérios para aprovar a arquitetura

- [ ] Protótipo de simulação determinística rodando igual em Windows e WebAssembly (mesmo hash de estado após N ticks).
- [ ] Teste de rede com latência e perda de pacotes simuladas.
- [ ] Teste de desconexão e reconexão.
- [ ] Teste de carga dos serviços de lobby e matchmaking.
- [ ] Estimativa de custo de hospedagem.
- [ ] Modelo de ameaças revisado ([SECURITY.md](SECURITY.md)).
- [ ] Decisão registrada em [DECISIONS.md](DECISIONS.md).
