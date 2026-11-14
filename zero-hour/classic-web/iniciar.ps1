# Liga o servidor do jogo (pagina + relay de multiplayer) e publica na sua rede Tailscale com HTTPS.
#
#   Servidor Python : http://127.0.0.1:8766  (so este PC enxerga)
#   Tailscale serve : https://<seu-pc>.<sua-tailnet>.ts.net:8765  (so quem esta na sua tailnet enxerga)
#
# A porta publica tem de ser 8765: o jogo procura o relay em wss://<host>:8765/GeneralsXLan.
#
# Uso:  powershell -ExecutionPolicy Bypass -File .\iniciar.ps1

$ErrorActionPreference = "Stop"

$Dest      = Join-Path $env:USERPROFILE "ZeroHourWeb"
$Www       = Join-Path $Dest "www"
$Server    = Join-Path $Dest "serve-webgpu.py"
$LocalPort = 8766
$PublicPort = 8765

if (-not (Test-Path (Join-Path $Www "GeneralsXZH.wasm"))) {
    throw "Arquivos nao encontrados em $Dest. Rode primeiro o instalar.ps1."
}

# --- Python 3.10+ ---------------------------------------------------------------------------
$Python = $null
$candidates = @(
    @{ Exe = "py";     Pre = @("-3") },
    @{ Exe = "python"; Pre = @() }
)
foreach ($c in $candidates) {
    try {
        $pre = $c.Pre
        $ver = & $c.Exe @pre -c "import sys; print('%d.%d' % sys.version_info[:2])" 2>$null
        if ($LASTEXITCODE -eq 0 -and [version]("$ver".Trim()) -ge [version]"3.10") { $Python = $c; break }
    } catch { }
}
if (-not $Python) { throw "Python 3.10 ou mais novo nao encontrado. Instale em python.org (marque 'Add to PATH')." }

# --- Tailscale ------------------------------------------------------------------------------
$Tailscale = (Get-Command tailscale -ErrorAction SilentlyContinue).Source
if (-not $Tailscale) {
    $fallback = Join-Path $env:ProgramFiles "Tailscale\tailscale.exe"
    if (Test-Path $fallback) { $Tailscale = $fallback } else { throw "Tailscale nao encontrado. Instale em tailscale.com/download." }
}
$status = & $Tailscale status --json | ConvertFrom-Json
if ($status.BackendState -ne "Running") { throw "O Tailscale nao esta conectado. Abra o app do Tailscale e faca login." }
$DnsName = $status.Self.DNSName.TrimEnd(".")
if (-not $DnsName) { throw "MagicDNS desligado. Ligue em login.tailscale.com/admin/dns (MagicDNS e HTTPS Certificates)." }

# --- Servidor do jogo -----------------------------------------------------------------------
$busy = Get-NetTCPConnection -LocalPort $LocalPort -State Listen -ErrorAction SilentlyContinue
if ($busy) {
    Write-Host "Ja existe algo escutando na porta $LocalPort (servidor ja ligado?). Seguindo."
} else {
    $exe = $Python.Exe
    $pyArgs = @($Python.Pre) + @("-I", "`"$Server`"", "`"$Www`"", "--bind", "127.0.0.1", "--port", "$LocalPort")
    $proc = Start-Process -FilePath $exe -ArgumentList $pyArgs -WindowStyle Minimized -PassThru
    Set-Content -Path (Join-Path $Dest "server.pid") -Value $proc.Id
    Start-Sleep -Seconds 2
    if ($proc.HasExited) { throw "O servidor Python fechou ao iniciar. Rode manualmente para ver o erro: $exe $($pyArgs -join ' ')" }
}

# --- Publica na tailnet com HTTPS -----------------------------------------------------------
& $Tailscale serve --bg --https=$PublicPort "http://127.0.0.1:$LocalPort"
if ($LASTEXITCODE -ne 0) {
    throw "O 'tailscale serve' falhou. Confira se HTTPS Certificates esta ligado em login.tailscale.com/admin/dns."
}

$Url = "https://$($DnsName):$PublicPort/"
Write-Host ""
Write-Host "=============================================================="
Write-Host " Jogo no ar (so para a sua rede Tailscale):"
Write-Host "   $Url"
Write-Host ""
Write-Host " Voce e seu amigo abrem ESSE endereco no Chrome ou Edge."
Write-Host " Cada um escolhe a pasta do PROPRIO Zero Hour quando a pagina pedir."
Write-Host " Para desligar: powershell -ExecutionPolicy Bypass -File .\parar.ps1"
Write-Host "=============================================================="
try { Set-Clipboard -Value $Url; Write-Host " (link copiado para a area de transferencia)" } catch { }
