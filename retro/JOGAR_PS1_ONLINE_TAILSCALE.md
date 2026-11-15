# Jogar jogos de PS1 online com Tailscale

RetroArch + netplay pelo Tailscale. Exemplo usado no guia: battle para 4 no Bomberman Party Edition.

> Este guia não traz links para baixar BIOS nem jogos: cada jogador usa a própria cópia.

## O que cada jogador precisa

- RetroArch, a mesma versão nos 4 PCs.
- O mesmo núcleo de PS1 nos 4 (SwanStation ou Beetle PSX; o PCSX-ReARMed roda sem BIOS).
- A mesma imagem do jogo (.bin/.cue ou .chd), idêntica byte a byte, feita da cópia de cada um.
- A BIOS do PS1 (ex.: `scph5501.bin`) na pasta Sistema/BIOS do RetroArch, extraída do próprio console.
- Tailscale com acesso ao PC do host (no painel do Tailscale: **Machines → … → Share…** só da máquina do host).
- Um controle por pessoa.

## Configuração (uma vez, em cada PC)

1. **Instalar o núcleo:** Menu principal → Carregar núcleo → Baixar um núcleo.
2. **BIOS:** colocar o arquivo diretamente na pasta de Configurações → Diretório → Sistema/BIOS.
   - Conferir em Menu principal → Informação → Informação do núcleo → Firmware ("Presente").
   - Cuidado com extensão escondida (`.bin.bin`) e com `.zip`: o RetroArch não lê a BIOS compactada.
   - O nome tem que ser exatamente um dos listados pelo núcleo, em minúsculas.
3. **Multitap (necessário para 4 jogadores):** com o jogo aberto, F1 → Menu rápido → Opções do núcleo.
   - SwanStation: Controller → Multitap Mode → Port 1 Only.
   - Beetle PSX: Input → Port 1: PSX Multitap → Enabled.
   - PCSX-ReARMed: Input → Multitap → ligado.
   - Depois: Fechar conteúdo e abrir o jogo de novo.
4. **(Opcional) Tipo de controle:** Menu rápido → Controles → Controles da porta 1..4 → Tipo de dispositivo
   (Standard/Analog/DualShock). Em versões antigas: Configurações → Entrada → Controles da porta N.

## Jogar

1. **Host:** abre o jogo → Menu principal → Netplay → Hospedar.
2. **Amigos:** abrem o mesmo jogo → Netplay → Conectar ao hospedeiro → IP do host no Tailscale
   (aparece no app do Tailscale; começa com `100.`), porta `55435`.
3. No jogo, entrar no modo **Battle**.

Testar primeiro com um amigo só e depois chamar os outros.

## Problemas comuns

- **Não conecta:** liberar o RetroArch no Firewall do Windows (redes privadas e públicas) no PC do host.
- **"Conteúdo diferente" ou desconecta:** jogo, núcleo ou versão do RetroArch diferente entre os PCs.
- **Lag:** Configurações → Rede → aumentar os quadros de atraso de entrada do netplay.
- Os nomes dos menus mudam um pouco entre versões e idiomas do RetroArch.
