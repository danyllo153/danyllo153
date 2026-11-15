# Baixa a versao web (motor em WebAssembly + pagina + servidor com relay) para %USERPROFILE%\ZeroHourWeb.
# Fonte: origami-ltd/wasm-generals, num commit fixo, com verificacao SHA-256 de cada arquivo.
# Nenhum arquivo .big do jogo e baixado: cada jogador escolhe a pasta da propria copia no navegador.
#
# Uso:  powershell -ExecutionPolicy Bypass -File .\instalar.ps1 [-Versao original|compat|rapida]
#
#   original : motor do wasm-generals como publicado (ate 1080p)
#   compat   : nosso motor com 2K/4K, mesmo mecanismo do original
#   rapida   : nosso motor com 2K/4K e JSPI + excecoes nativas (mais FPS; Chrome/Edge 137+)
#
# compat e rapida vem da release "motor-web" deste repositorio (GitHub Actions).

param(
    [ValidateSet("original", "compat", "rapida")]
    [string]$Versao = "original"
)

$ErrorActionPreference = "Stop"
$ProgressPreference = "SilentlyContinue"   # deixa o Invoke-WebRequest muito mais rapido

$Commit = "46382a383da270e16a60a28ecf342b569b998111"
$Base   = "https://raw.githubusercontent.com/origami-ltd/wasm-generals/$Commit"
$Dest   = Join-Path $env:USERPROFILE "ZeroHourWeb"
$Www    = Join-Path $Dest "www"

# caminho no repositorio -> caminho local (relativo a $Dest), hash esperado
$Files = @(
    @{ Src = "web/dist/index.html";                Dst = "www/index.html";                Sha = "c71b20092cfe1c90c42898e74b0f754612b0dbc9372839880671b1acb71de30c" },
    @{ Src = "web/dist/assets/index-BcW0hOmG.js";  Dst = "www/assets/index-BcW0hOmG.js";  Sha = "52b94bfa5ece2f149baa019fbd74bf509f9185aac36c9990823eccd0fca106eb" },
    @{ Src = "web/dist/assets/index-DaJE1AVD.css"; Dst = "www/assets/index-DaJE1AVD.css"; Sha = "a33a36948e9189949ee6a32a37b4c07b479e77956a9a6a9cb7ae59e507dee8de" },
    @{ Src = "web/dist/GeneralsXZH.js";            Dst = "www/GeneralsXZH.js";            Sha = "9ee11495751d506f8bff681f6f0673f041a57eb5c2d20f3d9a1c21892bbb3c33" },
    @{ Src = "web/dist/GeneralsXZH.wasm";          Dst = "www/GeneralsXZH.wasm";          Sha = "06298cab4354a100905d0441eb57e2c236363ef51376d6f65f0fde5bb510a714" },
    @{ Src = "web/dist/GeneralsXZH.data";          Dst = "www/GeneralsXZH.data";          Sha = "28d65aef04112086d70f2ef34bd4787a520200a4e01e6ba9191e168684623051" },
    @{ Src = "scripts/qa/smoke/serve-webgpu.py";   Dst = "serve-webgpu.py";               Sha = "4dfbcec3015e1097f2ac8678535768ec2846460bbd1a532afb1994bc09088715" }
)

New-Item -ItemType Directory -Force -Path (Join-Path $Www "assets") | Out-Null

foreach ($f in $Files) {
    $out = Join-Path $Dest $f.Dst
    Write-Host "Baixando $($f.Src) ..."
    Invoke-WebRequest -UseBasicParsing -Uri "$Base/$($f.Src)" -OutFile $out
    $hash = (Get-FileHash -Algorithm SHA256 $out).Hash.ToLower()
    if ($hash -ne $f.Sha) {
        Remove-Item $out -Force
        throw "Hash diferente em $($f.Src): esperado $($f.Sha), recebido $hash. Instalacao cancelada."
    }
}

# Remove o Google Analytics da pagina: o servidor e privado, nao ha motivo para avisar terceiros.
$index = Join-Path $Www "index.html"
$html = [IO.File]::ReadAllText($index)
$html = [regex]::Replace($html, "(?s)\s*<!-- Google Analytics.*?gtag\('config'[^<]*</script>", "")
# Esconde os botoes do topo (doacao, wasm.ltd e GitHub) e deixa no lugar uma linha discreta de
# credito. A GPL exige oferecer o codigo-fonte a quem recebe o motor, e a licenca da pagina
# (MIT-PoU) exige o credito: por isso o rodape fica.
$SourceUrl = "https://github.com/origami-ltd/wasm-generals/tree/$Commit"
$custom = @"
<style id="zh-custom">
  a.ogx-hud-button[href*="buymeacoffee"],
  a.ogx-hud-button[href*="wasm.ltd"],
  a.ogx-hud-button[aria-label="Source on GitHub"] { display: none !important; }
  #zh-credit { position: fixed; right: 8px; bottom: 4px; z-index: 5; font: 10px/1.4 system-ui, sans-serif;
               color: rgba(255,255,255,.35); pointer-events: auto; }
  #zh-credit a { color: inherit; }
</style>
"@
$credit = "<div id=""zh-credit"">Motor GPL-3.0: <a href=""$SourceUrl"" target=""_blank"" rel=""noopener"">c&oacute;digo-fonte</a> &middot; Includes material from origami-ltd/wasm-generals &mdash; https://generals.wasm.ltd</div>"
if ($html -notmatch 'id="zh-custom"') {
    # A pagina nao tem </head>: estilo e credito entram logo depois da tag <body>.
    $html = ([regex]'(<body[^>]*>)').Replace($html, "`$1`n$custom`n$credit", 1)
}
[IO.File]::WriteAllText($index, $html)

# Troca o motor pela nossa build, se pedida. O .data continua o original (nossa build le o mesmo pacote).
if ($Versao -ne "original") {
    $Rel = "https://github.com/danyllo153/danyllo153/releases/download/motor-web"
    $tmp = Join-Path $Dest "motor-$Versao"
    New-Item -ItemType Directory -Force -Path $tmp | Out-Null
    $sums = Join-Path $tmp "SHA256SUMS.txt"
    Write-Host "Baixando motor '$Versao' da release motor-web ..."
    Invoke-WebRequest -UseBasicParsing -Uri "$Rel/SHA256SUMS-$Versao.txt" -OutFile $sums
    $expected = @{}
    foreach ($line in Get-Content $sums) {
        $parts = $line -split "\s+\*?", 2
        if ($parts.Count -eq 2) { $expected[$parts[1].Trim()] = $parts[0].ToLower() }
    }
    foreach ($ext in @("js", "wasm")) {
        $name = "GeneralsXZH-$Versao.$ext"
        if (-not $expected.ContainsKey($name)) { throw "SHA256SUMS da release nao lista $name." }
        $out = Join-Path $tmp $name
        Invoke-WebRequest -UseBasicParsing -Uri "$Rel/$name" -OutFile $out
        $hash = (Get-FileHash -Algorithm SHA256 $out).Hash.ToLower()
        if ($hash -ne $expected[$name]) { throw "Hash diferente em $name. Instalacao cancelada." }
        Copy-Item $out (Join-Path $Www "GeneralsXZH.$ext") -Force
    }
    Remove-Item $tmp -Recurse -Force
    Write-Host "Motor '$Versao' instalado (com 2K/4K)."
}
Set-Content -Path (Join-Path $Dest "versao.txt") -Value $Versao

Write-Host ""
Write-Host "Pronto. Arquivos em $Dest"
Write-Host "Proximo passo: powershell -ExecutionPolicy Bypass -File .\iniciar.ps1"
