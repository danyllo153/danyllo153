# Roadmap — Zero Hour

> A ordem das fases é uma referência de planejamento. Escopo, duração e critérios de conclusão de cada fase devem ser detalhados e aprovados **antes** de a fase começar. Nenhuma fase tem prazo definido ainda.

**Fase atual:** pré-F0 / F0, planejamento e auditoria.

## Visão geral

| Fase | Nome | Objetivo | Status |
|---|---|---|---|
| **F0** | Auditoria e direitos | Investigar propriedade intelectual, licenças, riscos, escopo e viabilidade | 🔄 Em andamento |
| **F1** | Multiplayer | Protótipo funcional de partidas online e validação da sincronização | ⏳ Não iniciada |
| **F2** | Comunidade | Contas, perfis, lobby, presença e recursos sociais essenciais | ⏳ Não iniciada |
| **F3** | Competitivo | Resultados confiáveis, rankings, ranqueadas e integridade competitiva | ⏳ Não iniciada |
| **F4** | Temporadas | Missões diárias/semanais, passe gratuito e ciclos de 60 dias | ⏳ Não iniciada |
| **F5** | Enhanced | Qualidade, desempenho, usabilidade e experiência da versão Classic | ⏳ Não iniciada |
| **F6** | Next Generation | Pesquisa e desenvolvimento da nova geração, considerando Unreal Engine 5 | ⏳ Não iniciada |

## Critérios gerais para avançar de fase

- [ ] Objetivos e escopo documentados.
- [ ] Protótipo testável.
- [ ] Testes funcionais e de rede adequados à fase.
- [ ] Riscos conhecidos e mitigados.
- [ ] Segurança e integridade competitiva consideradas.
- [ ] Dependências e licenças verificadas.
- [ ] Documentação atualizada.

---

## F0 — Auditoria e direitos

**Objetivo:** saber o que pode e o que não pode ser feito antes de investir em código.

Entregas propostas:

- [ ] Levantamento de quem detém os direitos sobre nome, marca e conteúdo do jogo original.
- [ ] Identificação, por fonte confiável, da licença realmente aplicável a qualquer código ou material relacionado (sem presumir GPL).
- [ ] Lista de políticas de terceiros aplicáveis (por exemplo, políticas da EA), com link para a fonte oficial.
- [ ] Orientação jurídica qualificada sobre nome, marca, copyright, distribuição e monetização.
- [ ] Definição de nome provisório e diretrizes de conteúdo original para os protótipos.
- [ ] Escopo mínimo da primeira versão jogável (questão 2 do [PROJECT_MEMORY.md](PROJECT_MEMORY.md)).
- [ ] Lista de regras, modos e sistemas clássicos a reproduzir (questão 3).
- [ ] `IP_AND_LICENSES.md` preenchido com a situação encontrada.

**Saída:** decisão registrada sobre a viabilidade e as condições do projeto.

## F1 — Multiplayer

**Objetivo:** provar que uma partida online é jogável, sincronizada e justa.

Entregas propostas:

- [ ] Núcleo de simulação mínimo (mapa simples, poucas unidades, conteúdo original).
- [ ] Teste de determinismo: mesmo hash de estado em Windows e WebAssembly.
- [ ] Protótipo do modelo de autoridade escolhido para teste (ver [NETWORKING.md](NETWORKING.md)).
- [ ] Partida 1v1 online de ponta a ponta.
- [ ] Testes com latência, jitter e perda de pacotes simulados.
- [ ] Detecção de dessincronização.
- [ ] Desconexão e reconexão básicas.
- [ ] Gravação e reprodução de replay.

**Saída:** decisão registrada sobre o modelo de autoridade e a estratégia de cliente para o navegador.

## F2 — Comunidade

- [ ] Contas e autenticação.
- [ ] Perfis.
- [ ] Lobby e salas.
- [ ] Presença online.
- [ ] Recursos sociais essenciais (amigos, convites), escopo a definir.
- [ ] Moderação básica e denúncia.

## F3 — Competitivo

- [ ] Resultados validados pelo servidor.
- [ ] Matchmaking por regiões.
- [ ] Sistema de classificação (🔶 MMR/ELO/outro a definir).
- [ ] Partidas ranqueadas.
- [ ] Política de abandono e penalidades.
- [ ] Medidas contra trapaça ([SECURITY.md](SECURITY.md)).

## F4 — Temporadas

- [ ] Temporadas de 60 dias (✅ decidido).
- [ ] Passe gratuito (✅ decidido), com estrutura de níveis e XP a definir.
- [ ] Missões diárias (✅ planejadas) e semanais (🔶 consideradas).
- [ ] Recompensas apenas cosméticas ou de reconhecimento.
- [ ] Auditoria de progresso e prevenção de fraude.

## F5 — Enhanced

- [ ] Melhorias de desempenho.
- [ ] Usabilidade e acessibilidade.
- [ ] Qualidade visual e sonora com assets originais ou licenciados.
- [ ] Ferramentas de observação, replays e torneios, escopo a definir.

## F6 — Next Generation

- [ ] Pesquisa de viabilidade com Unreal Engine 5 (🧪 candidata, não aprovada).
- [ ] Protótipo isolado.
- [ ] Estimativa de esforço de reconstrução (renderização, unidades, física, HUD, rede, áudio, ferramentas, conteúdo).
- [ ] Decisão sobre coexistência, migração ou substituição da Classic (🔶 em aberto).
