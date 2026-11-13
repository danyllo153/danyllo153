# Rede e sincronização — Zero Hour

> 🧪 **Status: hipóteses e propostas.** O modelo de autoridade da partida é uma questão em aberto (questão 5 do [PROJECT_MEMORY.md](PROJECT_MEMORY.md)) e deve ser decidido na F1, com base em protótipos e testes.

## 1. Requisitos

| Requisito | Por quê |
|---|---|
| Integridade competitiva | Prioridade do projeto (DEC-002) |
| Muitas unidades com pouca banda | Característica de RTS clássico |
| Funcionar em navegador e Windows | DEC-001; o navegador limita o transporte (sem UDP direto; WebSocket ou WebRTC) |
| Tolerar conexões instáveis | Jogadores reais têm latência, jitter e perda de pacotes |
| Reconexão | Uma queda não deve encerrar a partida automaticamente |
| Replay e auditoria | Validar resultados, resolver disputas, investigar trapaças |
| Partidas Classic e Next isoladas | Versões de simulação diferentes não podem se misturar |

## 2. Modelos candidatos

### A. Lockstep determinístico P2P
Cada cliente roda a simulação completa; só os comandos dos jogadores são trocados.

- ✅ Banda mínima, mesmo com milhares de unidades.
- ❌ Exige determinismo perfeito entre plataformas.
- ❌ Cada cliente conhece o estado completo (facilita map hack).
- ❌ Sem árbitro: resultados dependem da palavra dos clientes.
- ❌ A latência do jogador mais lento afeta todos.

### B. Lockstep com relay e validação no servidor
Os clientes enviam comandos a um servidor relay, que define a ordem oficial, repassa a todos e grava a sequência.

- ✅ Mantém a eficiência do lockstep.
- ✅ Ordem de comandos oficial e registro confiável da partida.
- ✅ Permite re-simular no servidor para validar resultados ranqueados.
- ✅ Esconde o IP dos jogadores entre si.
- ❌ Continua exigindo determinismo.
- ❌ Não resolve sozinho o map hack.
- ❌ Custo de servidor (menor que o de servidor autoritativo).

### C. Servidor dedicado autoritativo
O servidor roda a simulação; clientes enviam entradas e recebem estado (com predição e interpolação).

- ✅ Maior resistência a trapaças; permite esconder informação (fog of war no servidor).
- ✅ Não exige determinismo entre clientes.
- ❌ Banda alta com muitas unidades.
- ❌ Maior custo de hospedagem e complexidade.
- ❌ Pode alterar a sensação do jogo clássico.

### D. Híbrido
Por exemplo: B para partidas casuais e ranqueadas, com re-simulação no servidor para as ranqueadas, e C avaliado para a Next.

### Recomendação provisória
Prototipar **B** na F1. Critério de saída: se o determinismo entre Windows e WebAssembly não for comprovado, ou se o map hack se mostrar um risco inaceitável, reavaliar C ou D.

### Versão UE5 (DEC-010)
🧪 O protótipo em `unreal/RTSProto` usa a **replicação nativa do Unreal com servidor autoritativo** (modelo C): o servidor move as unidades e valida cada ordem, e os clientes só enviam ordens. É o caminho mais rápido no UE5. Pontos a medir antes de aprovar:
- Banda com centenas de unidades (replicação de movimento por unidade custa mais que lockstep).
- Uso de Replication Graph ou Iris para escalar.
- Relevância por visão do time, para a névoa de guerra não vazar informação.

## 3. Determinismo: o que precisa ser verdade

- [ ] Simulação com **matemática de ponto fixo** (ou ponto flutuante rigorosamente controlado e testado).
- [ ] Sem dependência de ordem de iteração de containers não ordenados.
- [ ] Gerador de números aleatórios próprio, com semente compartilhada.
- [ ] Nenhuma leitura de relógio, threads ou estado de plataforma dentro da simulação.
- [ ] Simulação separada da renderização (tick fixo; renderização interpolada).
- [ ] Hash do estado a cada N ticks, comparado entre clientes para detectar dessincronização.
- [ ] Teste automatizado: mesma sequência de comandos → mesmo hash em Windows (MSVC/Clang) e WebAssembly.

## 4. Protocolo (rascunho)

🧪 Apenas para orientar o protótipo da F1.

### Canais

| Canal | Transporte proposto | Uso |
|---|---|---|
| Lobby / presença / eventos | WebSocket (TLS) | Salas, chat, convites, matchmaking |
| Partida | WebSocket ou WebRTC DataChannel via relay | Comandos e confirmações por tick |

### Mensagens de partida

| Mensagem | Direção | Conteúdo |
|---|---|---|
| `JOIN` | cliente → servidor | id da partida, token de sessão, versão da simulação |
| `START` | servidor → clientes | semente do RNG, lista de jogadores, tick inicial, atraso de comando |
| `CMD` | cliente → servidor | tick-alvo, sequência, comandos do jogador |
| `TURN` | servidor → clientes | tick, comandos ordenados de todos os jogadores |
| `HASH` | cliente → servidor | tick, hash do estado |
| `DESYNC` | servidor → clientes | tick em que os hashes divergiram |
| `PAUSE` / `RESUME` | servidor → clientes | motivo (por exemplo, jogador reconectando) |
| `END` | cliente → servidor | resultado declarado (o servidor valida, não aceita cegamente) |

### Atraso de comando
Comandos são agendados para `tick_atual + atraso`. O atraso pode se ajustar à latência medida, com limites mínimo e máximo a definir em teste.

## 5. Desconexão e reconexão

| Situação | Comportamento proposto |
|---|---|
| Queda curta | Pausa ou espera limitada; o cliente reconecta e recebe os comandos perdidos |
| Reconexão após muito tempo | Cliente recebe snapshot ou re-simula a partir do log de comandos |
| Não volta no tempo limite | Jogador é considerado desistente; a regra para ranqueadas é definida em [SECURITY.md](SECURITY.md) |
| Queda do relay | 🔶 Em aberto: encerrar sem resultado ou migrar |

## 6. Matchmaking e regiões

🔶 Em aberto (questão 6). Pontos a decidir:

- Regiões de servidores e como escolher a do jogador.
- Fila por modo (Classic / Next) e por tipo (casual / ranqueada).
- Equilíbrio entre tempo de espera, qualidade da conexão e diferença de rating.

## 7. Testes de rede da F1

- [ ] Latência simulada: 50, 100, 200 e 300 ms.
- [ ] Jitter e perda de pacotes: 1%, 5%, 10%.
- [ ] Desconexão no meio da partida e reconexão.
- [ ] Partida longa (mais de 40 minutos) sem dessincronização.
- [ ] Mesmo replay reproduzido em Windows e navegador com o mesmo hash final.
- [ ] Carga: número de partidas simultâneas por instância de relay.
