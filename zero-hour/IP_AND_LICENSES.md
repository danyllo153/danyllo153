# Propriedade intelectual e licenças — Zero Hour

> ⚖️ **Restrição central do projeto.** Este documento não é aconselhamento jurídico. Questões de nome, marca, copyright, distribuição, licenças de software e monetização devem passar por orientação jurídica qualificada.

## 1. Posição atual do projeto

| Item | Situação |
|---|---|
| Relação com a EA ou outros titulares | **Nenhuma.** Projeto independente, não oficial, não licenciado, não afiliado |
| Uso do nome “Zero Hour” | 🔶 Apenas como nome de trabalho interno; uso público em aberto (questão 1) |
| Arquivos do jogo original no repositório | **Nenhum** e nenhum deve ser adicionado |
| Licença do jogo ou código original | 🔶 Não identificada. **Não presumir GPL** |
| Políticas de terceiros aplicáveis | 🔶 A levantar na F0, com link para a fonte oficial |
| Monetização | Proibida até haver autorização (DEC-006) |

## 2. Regras obrigatórias

- Não extrair, copiar, redistribuir ou incorporar arquivos comerciais do jogo original sem autorização.
- Não reutilizar músicas, efeitos sonoros, mapas, modelos, texturas, ícones, logotipos ou marcas sem verificar os direitos.
- Não presumir que ter uma cópia do jogo dá direito de reutilizar seus arquivos.
- Não vender acesso, itens, cosméticos, passes ou serviços relacionados sem autorização.
- Não anunciar o projeto como oficial ou afiliado.
- Usar apenas conteúdo **original**, **licenciado** ou de **domínio público com licença verificada**.
- Registrar a origem e a licença de cada dependência e asset nas tabelas abaixo **antes** de usá-los.

## 3. Investigação de direitos (F0)

| # | Pergunta | Fonte consultada | Conclusão | Data |
|---|---|---|---|---|
| 1 | Quem detém os direitos sobre nome e marca? | — | 🔶 Pendente | — |
| 2 | Quem detém o copyright do jogo e de seus assets? | — | 🔶 Pendente | — |
| 3 | Existe código-fonte relacionado publicado? Sob qual licença? | [Repositório da EA](https://github.com/electronicarts/CnC_Generals_Zero_Hour), `LICENSE.md` | Sim. Código de Generals e Zero Hour liberado em 27/02/2025 sob **GPL v3 com termos adicionais (seção 7)**: não concede marcas da EA, proíbe afirmar afiliação, exige que versões modificadas sejam marcadas como tal e não identificadas como o original, e exige manter o aviso de copyright e os termos | 2026-11-13 |
| 4 | Essa licença cobre assets (arte, áudio, mapas) ou só código? | Mesmo repositório | Só código. Os arquivos do jogo não estão incluídos; os ports existentes exigem a cópia do próprio jogador. **Não hospedar arquivos do jogo** | 2026-11-13 |
| 5 | Existem políticas oficiais para projetos de fãs ou conteúdo derivado? | — | 🔶 Pendente | — |
| 6 | O que essas políticas permitem e proíbem (nome, distribuição, monetização)? | — | 🔶 Pendente | — |
| 7 | É necessário trocar o nome para publicação? | — | 🔶 Pendente | — |

> Preencher cada linha só com fontes verificáveis (documento oficial, texto da licença, parecer jurídico). Não registrar suposições como conclusões.

## 4. Inventário de assets

| ID | Asset | Tipo | Autor / origem | Licença | Link da licença | Modificado? | Data |
|---|---|---|---|---|---|---|---|
| — | *(nenhum asset ainda)* | | | | | | |

Tipos: modelo 3D, textura, sprite, ícone, música, efeito sonoro, voz, fonte, mapa, vídeo, texto.

## 5. Inventário de dependências de software

| Dependência | Versão | Uso no projeto | Licença | Obrigações (atribuição, copyleft etc.) | Status |
|---|---|---|---|---|---|
| — | | *(nenhuma adotada ainda)* | | | |

Candidatas citadas na arquitetura proposta, com licença a confirmar na fonte oficial antes da adoção: React, TypeScript, Node.js, PostgreSQL, Redis, bibliotecas de WebSocket, WebRTC/TURN, toolchain de WebAssembly, Unreal Engine 5 (que tem termos de licença próprios e regras de royalties a analisar).

## 6. Diretrizes para protótipos

- Usar **nome provisório** em qualquer build distribuído fora da equipe.
- Facções, unidades, mapas, sons e arte devem ser **originais** ou ter licença registrada aqui.
- Reproduzir **mecânicas e regras** como referência de design não autoriza copiar textos, nomes próprios, ícones ou dados extraídos do jogo original. Em caso de dúvida, consultar orientação jurídica.
- Nenhum build público até a conclusão da F0.
