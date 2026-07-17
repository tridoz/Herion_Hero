#!/bin/bash

set -e

# Colori
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
CYAN="\033[1;36m"
WHITE="\033[1;37m"
RESET="\033[0m"

clear

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


spinner()
{
    local pid=$1
    local delay=0.08
    local spin='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'

    while kill -0 "$pid" 2>/dev/null; do
        for ((i=0; i<${#spin}; i++)); do
            printf "\r${YELLOW}%c${RESET} Building project..." "${spin:$i:1}"
            sleep $delay
        done
    done

    printf "\r"
}


progress()
{
    local msg="$1"

    echo -e "${BLUE}${msg}${RESET}"

    for i in {1..35}; do
        printf "█"
        sleep 0.015
    done

    echo #!/bin/bash

set -e

# ==========================
# Colors
# ==========================

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
    local delay=0.08
    local spin='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'

    while kill -0 "$pid" 2>/dev/null; do
        for ((i=0; i<${#spin}; i++)); do
            printf "\r${YELLOW}%c${RESET} Building project..." "${spin:$i:1}"
            sleep $delay
        done
    done

    printf "\r"
}


# ==========================
# Progress bar
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
# Nuclear clean
# ==========================

progress "Removing old build..."

rm -rf build


# ==========================
# CMake configure
# ==========================

progress "Configuring CMake..."

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug > /dev/null


echo
echo -e "${BLUE}Starting fresh compilation...${RESET}"


# ==========================
# Build
# ==========================

cmake --build build -j8 > /tmp/build.log 2>&1 &

PID=$!


spinner $PID


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
    echo -e "${YELLOW}Compiler output:${RESET}"
    echo

    tail -n 60 /tmp/build.log

    exit 1

fi
}


START=$(date +%s)


progress "Configuring CMake..."

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug > /dev/null


echo
echo -e "${BLUE}Starting compilation...${RESET}"


cmake --build build -j8 > /tmp/build.log 2>&1 &
PID=$!


spinner $PID


wait $PID


END=$(date +%s)
TIME=$((END-START))


echo
echo -e "${GREEN}✔ Build completed successfully!${RESET}"
echo -e "${WHITE}Elapsed time:${RESET} ${CYAN}${TIME}s${RESET}"