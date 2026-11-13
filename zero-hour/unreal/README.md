# RTSProto — protótipo F1 em Unreal Engine 5 (Windows)

> **Nome provisório.** Jogo de estratégia **original**, no estilo clássico. Nenhum código, asset, nome ou visual da EA ou do jogo original. As unidades são cubos da própria engine.
>
> ⚠️ **Este código ainda não foi compilado.** Foi escrito num ambiente sem Unreal. A primeira compilação no seu PC pode mostrar erros pequenos; me mande a mensagem de erro e eu corrijo.

## O que este protótipo faz

| Recurso | Situação |
|---|---|
| Câmera de RTS (WASD/setas, borda da tela, zoom com a roda) | ✅ |
| Seleção por clique e por caixa (arrastar) | ✅ |
| Ordem de movimento com botão direito, em formação | ✅ |
| 2 times com cores diferentes (azul e vermelho), 6 unidades cada | ✅ |
| Multiplayer em rede (listen server, o servidor é a autoridade) | ✅ |
| Servidor valida a ordem: só move unidades do próprio time | ✅ |
| Recursos, construção, combate | ⏳ próximas etapas |

## Requisitos (no seu PC)

- Windows 10 ou 11 (64 bits).
- Placa de vídeo com suporte a DirectX 12; recomendado 16 GB de RAM ou mais.
- Bastante espaço livre em disco: a engine e o Visual Studio ocupam dezenas de GB.
- **Epic Games Launcher** → aba Unreal Engine → instalar a **5.5** (outra 5.x provavelmente funciona; veja abaixo).
- **Visual Studio 2022** (Community é gratuito) com a carga de trabalho **“Desenvolvimento de jogos com C++”**, incluindo o componente do Unreal Engine e um Windows SDK.

## Como compilar

1. Copie a pasta `zero-hour/unreal/RTSProto` para o seu PC (ou clone o repositório).
2. Clique com o botão direito em `RTSProto.uproject` → **Generate Visual Studio project files**.
   - Se a sua engine não for a 5.5: botão direito → **Switch Unreal Engine version** e escolha a sua.
3. Abra `RTSProto.sln` no Visual Studio.
4. No topo, escolha **Development Editor** e **Win64** e compile (Ctrl+Shift+B).
5. Dê dois cliques em `RTSProto.uproject` para abrir o editor.

## Montar o mapa de teste (só uma vez)

Mapas do Unreal não podem ser escritos como texto, então este passo é manual:

1. **File → New Level → Basic** (já vem com chão e luz).
2. Aumente o chão: selecione o piso e coloque escala **X = 40, Y = 40**.
3. **Place Actors** → procure **Nav Mesh Bounds Volume** → arraste para o mapa e aumente a escala até cobrir todo o chão. Aperte **P** para ver a área verde de navegação.
4. Apague o Player Start que já existir e coloque **2 Player Start** em cantos opostos do chão.
5. Salve como `Content/Maps/Proto`.
6. **Edit → Project Settings → Maps & Modes** → *Editor Startup Map* e *Game Default Map* = `Proto`. Confira se *Default GameMode* é `RTSGameMode`.

## Como testar

1. Na barra de cima, ao lado de **Play**, abra os três pontos:
   - **Number of Players:** 2
   - **Net Mode:** Play As Listen Server
2. Clique em **Play**. Abrem duas janelas: uma é o servidor (time 0, azul), a outra é o cliente (time 1, vermelho).

| Controle | Ação |
|---|---|
| Clique esquerdo | Seleciona uma unidade |
| Arrastar com o esquerdo | Seleciona em caixa |
| Clique direito | Move as selecionadas |
| WASD / setas / borda da tela | Move a câmera |
| Roda do mouse | Zoom |

### Lista de verificação

- [ ] Compila sem erro.
- [ ] Cada janela vê 12 unidades: 6 azuis e 6 vermelhas.
- [ ] Em cada janela só dá para selecionar as unidades do próprio time.
- [ ] O movimento ordenado no cliente aparece também no servidor, e o contrário.
- [ ] Com **Net Mode = Play As Client** (servidor dedicado), tudo continua funcionando.
- [ ] Com latência simulada (console: `NetEmulation.PktLag 150`), o jogo continua jogável.

Anote o que falhar e me mande.

## Estrutura do código

| Arquivo | Papel |
|---|---|
| `Source/RTSProto/RTSGameMode` | Servidor: times, ponto inicial e unidades iniciais |
| `Source/RTSProto/RTSPlayerController` | Seleção, ordem de movimento e validação no servidor |
| `Source/RTSProto/RTSUnit` | Unidade: time replicado, cor, movimento por NavMesh |
| `Source/RTSProto/RTSCameraPawn` | Câmera de RTS |
| `Source/RTSProto/RTSHUD` | Caixa de seleção e texto de depuração |

## Limitações conhecidas (de propósito, por ser protótipo)

- Todas as unidades são enviadas a todos os jogadores (`bAlwaysRelevant`). Com névoa de guerra (F3), isso precisa mudar para evitar map hack.
- Input clássico com teclas fixas no código; migrar para Enhanced Input depois.
- Ainda sem lobby nem matchmaking; a conexão é feita pelo editor.
