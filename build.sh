j#!/bin/bash

set -o pipefail


RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
CYAN="\033[1;36m"
WHITE="\033[1;37m"
RESET="\033[0m"


clear


# ==========================
# Logo
# ==========================

echo -e "${CYAN}"
cat << "EOF"
██╗  ██╗███████╗██████╗ ██╗ ██████╗ ███╗   ██╗
██║  ██║██╔════╝██╔══██╗██║██╔═══██╗████╗  ██║
███████║█████╗  ██████╔╝██║██║   ██║██╔██╗ ██║
██╔══██║██╔══╝  ██╔══██╗██║██║   ██║██║╚██╗██║
██║  ██║███████╗██║  ██║██║╚██████╔╝██║ ╚████║
╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝
EOF
echo -e "${RESET}"


# ==========================
# Spinner
# ==========================

spinner()
{
    local pid=$1
    local message=$2

    local spin='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'
    local i=0

    while kill -0 "$pid" 2>/dev/null; do

        printf "\r${YELLOW}%s${RESET} %s" \
            "${spin:$i:1}" "$message"

        i=$(( (i+1) % ${#spin} ))

        sleep 0.08
    done

    printf "\r"
}


# ==========================
# Progress
# ==========================

progress()
{
    echo -e "${BLUE}$1${RESET}"

    for i in {1..35}; do
        printf "█"
        sleep 0.015
    done

    echo
}


START=$(date +%s)


# ==========================
# Configure CMake
# ==========================

progress "Configuring CMake..."


if ! cmake \
    -S . \
    -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    > /tmp/cmake.log 2>&1
then

    echo
    echo -e "${RED}✘ CMake configuration failed!${RESET}"
    echo

    cat /tmp/cmake.log

    exit 1

fi



# ==========================
# Build
# ==========================

echo
echo -e "${BLUE}Starting compilation...${RESET}"


cmake --build build \
    -j$(nproc) \
    > /tmp/build.log 2>&1 &


PID=$!


spinner $PID "Building project..."


# ==========================
# Result
# ==========================

if wait $PID; then

    END=$(date +%s)
    TIME=$((END-START))

    echo
    echo -e "${GREEN}✔ Build completed successfully!${RESET}"
    echo -e "${WHITE}Elapsed time:${RESET} ${CYAN}${TIME}s${RESET}"


else

    echo
    echo -e "${RED}✘ Build failed!${RESET}"
    echo

    echo -e "${YELLOW}Compiler errors:${RESET}"
    echo

    grep -E "error:|fatal error:" /tmp/build.log

    echo
    echo -e "${WHITE}Full log:${RESET} ${CYAN}/tmp/build.log${RESET}"

    exit 1

fi