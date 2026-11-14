# Tira o jogo da tailnet e desliga o servidor local.
# Uso:  powershell -ExecutionPolicy Bypass -File .\parar.ps1

$Dest = Join-Path $env:USERPROFILE "ZeroHourWeb"

$Tailscale = (Get-Command tailscale -ErrorAction SilentlyContinue).Source
if (-not $Tailscale) { $Tailscale = Join-Path $env:ProgramFiles "Tailscale\tailscale.exe" }
if (Test-Path $Tailscale) {
    & $Tailscale serve --https=8765 off 2>$null
    Write-Host "Publicacao na tailnet desligada."
}

$pidFile = Join-Path $Dest "server.pid"
if (Test-Path $pidFile) {
    $serverPid = [int](Get-Content $pidFile)
    Stop-Process -Id $serverPid -Force -ErrorAction SilentlyContinue
    Remove-Item $pidFile -Force
    Write-Host "Servidor local desligado."
} else {
    Write-Host "Nenhum servidor registrado (server.pid nao existe)."
}
