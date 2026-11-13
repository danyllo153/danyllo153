# Registro de decisões — Zero Hour

> **Regras deste registro**
>
> - Só entram aqui decisões **aprovadas explicitamente**. Propostas e hipóteses ficam em [ARCHITECTURE.md](ARCHITECTURE.md) e [NETWORKING.md](NETWORKING.md); questões em aberto ficam no [PROJECT_MEMORY.md](PROJECT_MEMORY.md).
> - Nunca apagar nem sobrescrever uma decisão. Quando ela mudar, criar uma nova entrada e marcar a antiga como **Substituída por DEC-YYY**.
> - Ao registrar uma decisão, atualizar também o [PROJECT_MEMORY.md](PROJECT_MEMORY.md) e o [ROADMAP.md](ROADMAP.md), se forem afetados.

## Índice

| ID | Tema | Status |
|---|---|---|
| DEC-001 | Plataformas-alvo | ✅ Aprovada |
| DEC-002 | Prioridade do projeto | ✅ Aprovada |
| DEC-003 | Identidade de jogo | ✅ Aprovada |
| DEC-004 | Visão de longo prazo | ✅ Aprovada |
| DEC-005 | Passe de progressão gratuito | ✅ Aprovada |
| DEC-006 | Monetização condicionada | ✅ Aprovada |
| DEC-007 | Duração das temporadas | ✅ Aprovada |
| DEC-008 | Missões | ✅ Aprovada (parcial) |
| DEC-009 | Unreal Engine 5 como candidata | Substituída por DEC-010 |
| DEC-010 | Versão em Unreal Engine 5 para Windows | ✅ Aprovada (adiada para depois da Classic, ver DEC-011) |
| DEC-011 | Classic primeiro: navegador + Windows com crossplay, multiplayer e ranqueada | ✅ Aprovada |
| DEC-012 | Resoluções 1080p, 1440p (2K) e 2160p (4K) | ✅ Aprovada |

> As decisões DEC-001 a DEC-009 foram tomadas na fase de planejamento, antes da criação deste registro, e foram registradas aqui em 2026-11-13. As alternativas consideradas na época não foram documentadas.

---

### DEC-001 — Plataformas-alvo
- **Data do registro:** 2026-11-13
- **Status:** ✅ Aprovada
- **Decisão:** o projeto terá como plataformas-alvo o **navegador** e o **Windows**.
- **Motivo:** facilitar o acesso dos jogadores e manter a plataforma tradicional do jogo clássico.
- **Alternativas consideradas:** não registradas.
- **Consequências e riscos:** pode exigir builds ou clientes diferentes por plataforma; o desempenho no navegador ainda precisa ser validado.
- **Itens em aberto:** como o navegador vai executar a experiência (WebAssembly, cliente web separado ou outra solução).

### DEC-002 — Prioridade do projeto
- **Data do registro:** 2026-11-13
- **Status:** ✅ Aprovada
- **Decisão:** a prioridade é o **multiplayer online competitivo**.
- **Motivo:** é a razão central do projeto.
- **Alternativas consideradas:** não registradas.
- **Consequências e riscos:** matchmaking, estabilidade, sincronização e integridade das partidas vêm antes de recursos visuais e de progressão.
- **Itens em aberto:** modelo de autoridade da partida, matchmaking e sistema de classificação.

### DEC-003 — Identidade de jogo
- **Data do registro:** 2026-11-13
- **Status:** ✅ Aprovada
- **Decisão:** preservar a **essência e as regras clássicas** como referência de design.
- **Motivo:** manter a identidade estratégica e competitiva que motiva o projeto.
- **Alternativas consideradas:** não registradas.
- **Consequências e riscos:** mudanças nas regras centrais precisam de avaliação cuidadosa. Reproduzir regras não autoriza copiar código ou assets protegidos (ver [IP_AND_LICENSES.md](IP_AND_LICENSES.md)).
- **Itens em aberto:** quais regras, modos, facções e sistemas serão reproduzidos.

### DEC-004 — Visão de longo prazo
- **Data do registro:** 2026-11-13
- **Status:** ✅ Aprovada
- **Decisão:** a visão de longo prazo é uma versão **Nova Geração**.
- **Motivo:** preparar o projeto para evolução tecnológica e visual.
- **Alternativas consideradas:** não registradas.
- **Consequências e riscos:** a arquitetura deve separar Classic e Next conceitualmente.
- **Itens em aberto:** coexistência, migração ou substituição entre Classic e Next.

### DEC-005 — Passe de progressão gratuito
- **Data do registro:** 2026-11-13
- **Status:** ✅ Aprovada
- **Decisão:** o passe será **gratuito inicialmente**. Missões e recompensas não podem conceder vantagem competitiva.
- **Motivo:** progressão justa e preservação da integridade competitiva.
- **Alternativas consideradas:** não registradas.
- **Consequências e riscos:** recompensas limitadas a itens cosméticos ou de reconhecimento. “Gratuito inicialmente” **não** autoriza cobrança futura (ver DEC-006).
- **Itens em aberto:** níveis, XP, ritmo de progressão, recompensas e recuperação de temporadas.

### DEC-006 — Monetização condicionada
- **Data do registro:** 2026-11-13
- **Status:** ✅ Aprovada
- **Decisão:** nenhuma monetização, venda de itens, passe pago ou exploração comercial será implementada sem **autorização expressa dos titulares dos direitos** necessários.
- **Motivo:** respeito à propriedade intelectual e redução de risco jurídico.
- **Alternativas consideradas:** não registradas.
- **Consequências e riscos:** o projeto não deve ter fluxos de pagamento até que exista autorização comprovada.
- **Itens em aberto:** quais autorizações seriam necessárias.

### DEC-007 — Duração das temporadas
- **Data do registro:** 2026-11-13
- **Status:** ✅ Aprovada
- **Decisão:** temporadas em **ciclos de 60 dias**.
- **Motivo:** definido no planejamento.
- **Alternativas consideradas:** não registradas.
- **Consequências e riscos:** missões, passe e possíveis resets de ranking devem se alinhar a esse ciclo.
- **Itens em aberto:** política de reset de ranking e recompensas de fim de temporada.

### DEC-008 — Missões
- **Data do registro:** 2026-11-13
- **Status:** ✅ Aprovada (parcial)
- **Decisão:** haverá **missões diárias**. Missões **semanais** foram consideradas, mas não confirmadas.
- **Motivo:** incentivar o retorno e recompensar a participação.
- **Alternativas consideradas:** não registradas.
- **Consequências e riscos:** missões não podem incentivar o jogador a prejudicar a própria equipe ou a integridade da partida.
- **Itens em aberto:** confirmação das missões semanais, tipos de missão, critérios, limites e recompensas.

### DEC-009 — Unreal Engine 5 como candidata
- **Data do registro:** 2026-11-13
- **Status:** Substituída por DEC-010
- **Decisão:** Unreal Engine 5 é uma **possibilidade** para a etapa Nova Geração; a migração **não** está aprovada.
- **Motivo:** manter a opção aberta sem assumir compromisso prematuro.
- **Alternativas consideradas:** não registradas.
- **Consequências e riscos:** uma migração pode exigir reconstruir renderização, unidades, física, HUD, rede, áudio, ferramentas e conteúdo.
- **Itens em aberto:** adoção real da UE5 na F6.

### DEC-010 — Versão em Unreal Engine 5 para Windows
- **Data:** 2026-11-13
- **Status:** ✅ Aprovada
- **Contexto:** a pesquisa mostrou que não existe versão pública do jogo em UE5, que o código liberado pela EA (GPL v3) não pode ser combinado com o UE5 e que os assets, o nome e a marca continuam protegidos.
- **Decisão:** desenvolver a versão em **Unreal Engine 5**, jogada no **Windows**. O protótipo começa já na F1 (`unreal/RTSProto`).
- **Motivo:** decisão do responsável pelo projeto, que quer a versão em UE5 rodando e liberada ao público.
- **Alternativas consideradas:** usar o código GPL da EA (incompatível com o UE5); manter a UE5 só para a F6.
- **Consequências e riscos:**
  - A versão UE5 é escrita do zero, sem código GPL da EA.
  - Para ser publicada, precisa ter nome, facções, unidades, arte, sons e mapas originais (princípio 8 e [IP_AND_LICENSES.md](IP_AND_LICENSES.md)).
  - O UE5 não exporta para navegador; a versão UE5 não roda no navegador.
  - Sujeita aos termos de licença da Epic, a verificar antes do lançamento.
- **Itens em aberto:** nome definitivo e cenário original; se haverá experiência jogável no navegador (DEC-001) e como; modelo de rede definitivo da versão UE5.

### DEC-011 — Classic primeiro: navegador + Windows com crossplay
- **Data:** 2026-11-13
- **Status:** ✅ Aprovada
- **Contexto:** o responsável pelo projeto decidiu seguir o roadmap e entregar a versão Classic antes da versão UE5. A pesquisa encontrou vários ports do motor original para WebAssembly, todos derivados do código GPL v3 liberado pela EA e todos exigindo que o jogador forneça os próprios arquivos do jogo.
- **Decisão:**
  - A versão **Classic** vem antes da versão UE5. O protótipo UE5 (`unreal/RTSProto`) fica pausado até a F6.
  - A Classic deve ser jogável no **navegador** e no **Windows**, com **crossplay** entre eles.
  - Foco em **multiplayer**, **ranqueada** e **melhoria gráfica**.
- **Motivo:** decisão do responsável pelo projeto, alinhada ao roadmap original (F1 a F5 antes da F6).
- **Alternativas consideradas:** continuar a versão UE5 primeiro.
- **Consequências e riscos:**
  - Crossplay exige que navegador e Windows rodem **o mesmo código de simulação**, com o mesmo resultado (lockstep com verificação de CRC). Diferenças entre WebAssembly e x86 são o maior risco técnico.
  - O navegador não usa UDP direto: o multiplayer precisa de relay (WebSocket ou WebRTC) também para os clientes Windows.
  - A melhoria gráfica fica, a princípio, no renderizador (resolução, anti-aliasing, sombras, filtragem). Assets em HD só se forem originais ou licenciados.
- **Itens em aberto:** base técnica (proposta abaixo, aguardando confirmação); nome público do projeto; sistema de classificação.

**Base técnica proposta (🧪 aguardando confirmação):** fork de um port existente do código GPL da EA para WebAssembly, com estas condições, que vêm dos termos de licença:
- Código do motor continua **GPL v3 com os termos adicionais da EA** e precisa ser publicado.
- O jogador fornece os **arquivos do próprio jogo** (por exemplo, da cópia da Steam). Nós **não hospedamos** arquivos do jogo.
- Nenhuma marca da EA (“Command & Conquer” e outras) no nome do projeto; versão marcada como modificada e não apresentada como o original; nenhuma afirmação de afiliação.
- Serviços online (contas, lobby, ranking) são programas separados e podem ter licença própria.

### DEC-012 — Resoluções suportadas
- **Data:** 2026-11-13
- **Status:** ✅ Aprovada
- **Decisão:** suportar **1920×1080 (1080p)**, **2560×1440 (2K)** e **3840×2160 (4K)**, no navegador e no Windows.
- **Motivo:** requisito do responsável pelo projeto para a melhoria gráfica.
- **Consequências e riscos:** a interface original foi feita para resoluções baixas; em 4K precisa de escala da interface para continuar legível. No navegador, 4K depende do desempenho da GPU e do WebGL/WebGPU.
- **Itens em aberto:** suporte a ultrawide (21:9) e a outras proporções.

---

## Modelo para novas decisões

```markdown
### DEC-XXX — <Tema>
- **Data:** AAAA-MM-DD
- **Status:** ✅ Aprovada | Substituída por DEC-YYY
- **Contexto:**
- **Decisão:**
- **Motivo:**
- **Alternativas consideradas:**
- **Consequências e riscos:**
- **Itens em aberto:**
```
