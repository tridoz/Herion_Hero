```powershell
#Requires -Version 5.1

$ErrorActionPreference = "Stop"

# ============================================================
# Colors
# ============================================================

$ESC = [char]27

$RED    = "$ESC[1;31m"
$GREEN  = "$ESC[1;32m"
$YELLOW = "$ESC[1;33m"
$BLUE   = "$ESC[1;34m"
$CYAN   = "$ESC[1;36m"
$WHITE  = "$ESC[1;37m"
$GRAY   = "$ESC[90m"
$RESET  = "$ESC[0m"

try {
    $Host.UI.RawUI.WindowTitle = "Herion Hero"
} catch {}

# ============================================================
# Helpers
# ============================================================

function Write-Centered {
    param(
        [string]$Text,
        [string]$Color = $RESET
    )

    $width = try {
        $Host.UI.RawUI.WindowSize.Width
    } catch {
        80
    }

    $padding = [Math]::Max(
        0,
        [int](($width - $Text.Length) / 2)
    )

    Write-Host (" " * $padding) -NoNewline
    Write-Host "$Color$Text$RESET"
}

function Show-Banner {

    Clear-Host

    Write-Host ""
    Write-Host "$CYAN"

    Write-Centered "██╗  ██╗███████╗██████╗ ██╗ ██████╗ ███╗   ██╗"
    Write-Centered "██║  ██║██╔════╝██╔══██╗██║██╔═══██╗████╗  ██║"
    Write-Centered "███████║█████╗  ██████╔╝██║██║   ██║██╔██╗ ██║"
    Write-Centered "██╔══██║██╔══╝  ██╔══██╗██║██║   ██║██║╚██╗██║"
    Write-Centered "██║  ██║███████╗██║  ██║██║╚██████╔╝██║ ╚████║"
    Write-Centered "╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝"

    Write-Host "$RESET"

    Write-Centered "H E R I O N   H E R O" $WHITE

    Write-Host ""
}

# ============================================================
# Main
# ============================================================

Show-Banner

# ============================================================
# Check executable
# ============================================================

Write-Host "$BLUE━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"
Write-Host "$WHITE  Checking game executable$RESET"
Write-Host "$BLUE━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"
Write-Host ""

$Executable = Join-Path $PSScriptRoot "bin\Herion_Hero.exe"

if (-not (Test-Path $Executable -PathType Leaf)) {

    Write-Host "$RED  ✘ Executable not found!$RESET"
    Write-Host ""

    Write-Host "$WHITE  Run:$RESET"
    Write-Host "  $CYAN  .\build.ps1$RESET"

    Write-Host ""
    exit 1
}

Write-Host "$GREEN  ✓ Executable found$RESET"
Write-Host "$GRAY  $Executable$RESET"
Write-Host ""

Write-Host "$GREEN  ✔ Launching game...$RESET"
Write-Host ""

Start-Sleep -Milliseconds 500

# ============================================================
# Run game
# ============================================================

Clear-Host

try {

    # Start the game and wait for it to close.
    $process = Start-Process `
        -FilePath $Executable `
        -WorkingDirectory (Split-Path $Executable) `
        -Wait `
        -PassThru

    $ExitCode = $process.ExitCode

}
catch {

    Clear-Host

    Write-Host ""
    Write-Host "$RED━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"
    Write-Host "$RED  ✘ Failed to launch Herion Hero$RESET"
    Write-Host "$RED━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"
    Write-Host ""

    Write-Host "$WHITE  Error:$RESET"
    Write-Host "  $RED$($_.Exception.Message)$RESET"

    Write-Host ""

    exit 1
}

# ============================================================
# Game exit
# ============================================================

Write-Host ""

if ($ExitCode -eq 0) {

    Write-Host "$GREEN━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"
    Write-Host "$GREEN  ✔ Game closed normally.$RESET"
    Write-Host "$GREEN━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"

}
else {

    Write-Host "$RED━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"
    Write-Host "$RED  ✘ Game exited with code $ExitCode$RESET"
    Write-Host "$RED━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"

}

Write-Host ""
```
