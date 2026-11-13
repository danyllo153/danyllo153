# Segurança e integridade competitiva — Zero Hour

> 🧪 **Status: modelo de ameaças inicial.** As mitigações são propostas e devem ser validadas junto com o modelo de rede ([NETWORKING.md](NETWORKING.md)).

## 1. Princípios

1. **O cliente não é confiável.** Qualquer dado vindo do cliente pode estar manipulado.
2. **O servidor é a fonte da verdade** para contas, resultados, rankings, missões e progressão.
3. **Todo progresso é rastreável** até a partida que o gerou.
4. **Integridade competitiva acima da conveniência:** não simplificar a implementação abrindo brechas.
5. **Recompensas não dão poder** (DEC-005), o que reduz o incentivo a fraude com impacto na partida.

## 2. Modelo de ameaças

| # | Ameaça | Impacto | Mitigação proposta | Fase |
|---|---|---|---|---|
| T1 | Resultado falso enviado pelo cliente | Ranking corrompido | O servidor valida o resultado pelo log de comandos (re-simulação) ou pelo consenso dos hashes | F3 |
| T2 | Comandos impossíveis (recursos inexistentes, unidades de outro jogador) | Vantagem injusta | Validação dos comandos na simulação; em B, re-simulação no servidor detecta | F1/F3 |
| T3 | Map hack (ver através do fog of war) | Vantagem injusta | Difícil em lockstep. Detecção por análise de replay; servidor autoritativo (C) se o risco for inaceitável | F3 |
| T4 | Speed hack / manipulação de ticks | Vantagem injusta | Ritmo de ticks definido pelo servidor/relay | F1 |
| T5 | Dessincronização provocada de propósito | Partidas anuladas | Hash por tick; identificar o cliente divergente pela re-simulação | F1 |
| T6 | Abandono para evitar derrota | Ranking inflado | Abandono conta como derrota em ranqueadas; penalidade progressiva | F3 |
| T7 | Conluio / win trading | Ranking manipulado | Detecção estatística de padrões entre as mesmas contas | F3 |
| T8 | Contas múltiplas (smurf) | Partidas desequilibradas | Rating com incerteza alta para contas novas; 🔶 verificação a definir | F3 |
| T9 | Fraude em missões e passe | Progresso falso | Progresso calculado no servidor a partir de partidas validadas | F4 |
| T10 | Farm de missões em partidas combinadas | Progresso falso | Limites diários; partidas suspeitas não contam | F4 |
| T11 | Exposição do IP do jogador / DDoS | Derrubar adversário | Relay ou TURN em vez de P2P direto | F1 |
| T12 | Roubo de conta | Perda de conta | Hash de senha forte (por exemplo, Argon2), limite de tentativas, 🔶 2FA opcional | F2 |
| T13 | Injeção / abuso da API | Vazamento de dados | Validação de entrada, consultas parametrizadas, limite de requisições | F2 |
| T14 | Abuso no chat e assédio | Comunidade prejudicada | Denúncia, silenciar/bloquear, moderação | F2 |
| T15 | Cliente modificado | Várias acima | Verificação de versão e integridade (não é proteção absoluta); validação no servidor é a defesa principal | F1+ |

## 3. Validação de resultados (proposta para ranqueadas)

1. O relay grava a sequência oficial de comandos e os hashes enviados.
2. Ao fim da partida, os clientes declaram o resultado (`END`).
3. Se os hashes concordam e o resultado é consistente, o resultado é aceito.
4. Se há divergência, ou por amostragem, o servidor re-simula a partida a partir do log.
5. Só depois disso o ranking, as missões e o passe são atualizados.
6. Tudo é registrado em `audit_event`.

## 4. Dados e privacidade

- Coletar apenas o necessário para contas, partidas e moderação.
- Senhas nunca em texto puro.
- Comunicação sempre por TLS.
- 🔶 Avaliar obrigações da LGPD (e de outras leis, se houver jogadores de outros países) antes de abrir cadastro público.
- 🔶 Definir política de retenção de logs e replays.

## 5. Reporte de vulnerabilidades

🔶 A definir antes de qualquer versão pública: canal de contato, prazo de resposta e política de divulgação responsável.
