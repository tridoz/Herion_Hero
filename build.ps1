#Requires -Version 5.1

$ErrorActionPreference = "Stop"

# ============================================================
# Configuration
# ============================================================

$BuildDir = "build"
$CMakeLog = Join-Path $env:TEMP "herion_hero_cmake.log"

# ANSI colors
$ESC    = [char]27
$RED    = "$ESC[1;31m"
$GREEN  = "$ESC[1;32m"
$YELLOW = "$ESC[1;33m"
$BLUE   = "$ESC[1;34m"
$CYAN   = "$ESC[1;36m"
$WHITE  = "$ESC[1;37m"
$GRAY   = "$ESC[90m"
$RESET  = "$ESC[0m"

# ============================================================
# Initialization
# ============================================================

try {
    $Host.UI.RawUI.WindowTitle = "Herion Hero - Build"
}
catch {
    # Ignore terminals that do not support WindowTitle
}

# ============================================================
# Helpers
# ============================================================

function Write-Color {
    param(
        [string]$Text,
        [string]$Color = $RESET
    )

    Write-Host "$Color$Text$RESET"
}

function Write-Centered {
    param(
        [string]$Text,
        [string]$Color = $RESET
    )

    $width = try {
        $Host.UI.RawUI.WindowSize.Width
    }
    catch {
        80
    }

    $padding = [Math]::Max(
        0,
        [int](($width - $Text.Length) / 2)
    )

    Write-Host (" " * $padding) -NoNewline
    Write-Host "$Color$Text$RESET"
}

function Write-Section {
    param(
        [string]$Title
    )

    Write-Host ""
    Write-Host "$BLUE━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"
    Write-Host "$WHITE  $Title$RESET"
    Write-Host "$BLUE━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$RESET"
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

    Write-Centered "BUILD SYSTEM" $WHITE

    Write-Host ""
}

function Get-ElapsedSeconds {
    param(
        [DateTime]$Start
    )

    return [Math]::Round(
        ((Get-Date) - $Start).TotalSeconds,
        1
    )
}

function Show-Spinner {
    param(
        [int]$ProcessId,
        [string]$Message
    )

    $frames = @(
        "⠋",
        "⠙",
        "⠹",
        "⠸",
        "⠼",
        "⠴",
        "⠦",
        "⠧",
        "⠇",
        "⠏"
    )

    $i = 0

    while (Get-Process -Id $ProcessId -ErrorAction SilentlyContinue) {

        $frame = $frames[$i]

        Write-Host "`r$YELLOW$frame$RESET $Message" -NoNewline

        $i = ($i + 1) % $frames.Count

        Start-Sleep -Milliseconds 80
    }

    Write-Host "`r" -NoNewline
    Write-Host (" " * ($Message.Length + 4)) -NoNewline
    Write-Host "`r" -NoNewline
}

function Show-Progress {
    param(
        [string]$Message
    )

    Write-Host ""
    Write-Host "$BLUE$Message$RESET"

    $width = 40

    for ($i = 0; $i -le $width; $i++) {

        $filled = "█" * $i
        $empty = "░" * ($width - $i)

        $percent = [int](($i / $width) * 100)

        Write-Host "`r  $CYAN[$filled$GRAY$empty$RESET] $WHITE$percent%$RESET" -NoNewline

        Start-Sleep -Milliseconds 12
    }

    Write-Host ""
}

# ============================================================
# Main
# ============================================================

try {

    Show-Banner

    $StartTime = Get-Date

    # --------------------------------------------------------
    # Check dependencies
    # --------------------------------------------------------

    Write-Section "Checking build environment"

    Write-Host "  $GRAY> Checking CMake...$RESET"

    if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
        throw "CMake was not found in PATH."
    }

    $cmakeVersion = cmake --version | Select-Object -First 1

    Write-Host "  $GREEN✓$RESET $cmakeVersion"

    Write-Host "  $GRAY> Checking Ninja...$RESET"

    if (-not (Get-Command ninja -ErrorAction SilentlyContinue)) {
        throw "Ninja was not found in PATH."
    }

    $ninjaVersion = ninja --version

    Write-Host "  $GREEN✓$RESET Ninja $ninjaVersion"

    # --------------------------------------------------------
    # CMake configuration
    # --------------------------------------------------------

    Write-Section "Configuring CMake"

    Write-Host "  $GRAY> Generator : $RESET Ninja"
    Write-Host "  $GRAY> Build type: $RESET Debug"
    Write-Host "  $GRAY> Directory : $RESET $BuildDir"
    Write-Host ""

    cmake `
        -S . `
        -B $BuildDir `
        -G Ninja `
        -DCMAKE_BUILD_TYPE=Debug `
        *> $CMakeLog

    if ($LASTEXITCODE -ne 0) {

        Write-Host ""

        Write-Color "  ✘ CMake configuration failed!" $RED

        Write-Host ""

        Write-Color "  ── CMake output ─────────────────────────────────────" $RED

        if (Test-Path $CMakeLog) {
            Get-Content $CMakeLog
        }

        Write-Host ""

        exit 1
    }

    Write-Host ""

    Write-Color "  ✓ CMake configuration complete" $GREEN

    # --------------------------------------------------------
    # Build
    # --------------------------------------------------------

    Write-Section "Building project"

    $cores = [Environment]::ProcessorCount

    Write-Host "  $GRAY> CPU threads: $RESET$cores"
    Write-Host "  $GRAY> Build dir  : $RESET$BuildDir"
    Write-Host ""

    # Start build process
    $process = Start-Process `
        -FilePath "cmake" `
        -ArgumentList @(
            "--build",
            $BuildDir,
            "--parallel",
            $cores
        ) `
        -NoNewWindow `
        -PassThru

    # Spinner while compiling
    Show-Spinner `
        -ProcessId $process.Id `
        -Message "Compiling Herion Hero..."

    $process.WaitForExit()

    if ($process.ExitCode -ne 0) {

        Write-Host ""

        Write-Color "  ✘ Build failed!" $RED

        Write-Host ""

        Write-Color "  Exit code: $($process.ExitCode)" $RED

        Write-Host ""

        exit $process.ExitCode
    }

    # --------------------------------------------------------
    # Success
    # --------------------------------------------------------

    $Elapsed = Get-ElapsedSeconds $StartTime

    Write-Section "Build complete"

    Write-Host ""

    Write-Centered "╔══════════════════════════════════════════╗" $GREEN
    Write-Centered "║                                          ║" $GREEN
    Write-Centered "║       ✓ BUILD COMPLETED SUCCESSFULLY     ║" $GREEN
    Write-Centered "║                                          ║" $GREEN
    Write-Centered "╚══════════════════════════════════════════╝" $GREEN

    Write-Host ""

    Write-Host "  $WHITEElapsed time:$RESET $CYAN$Elapsed seconds$RESET"
    Write-Host "  $WHITEBuild directory:$RESET $CYAN$BuildDir$RESET"

    Write-Host ""
}
catch {

    Write-Host ""

    Write-Color "  ✘ ERROR" $RED

    Write-Host ""

    Write-Host "  $WHITE$($_.Exception.Message)$RESET"

    Write-Host ""

    exit 1
}

