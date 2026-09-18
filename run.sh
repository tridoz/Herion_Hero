#!/bin/bash

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

              H E R I O N   H E R O

EOF
echo -e "${RESET}"


# ==========================
# Loading animation
# ==========================


# ==========================
# Check executable
# ==========================

if [ ! -f "./bin/Herion_Hero" ]; then
    echo -e "${RED}✘ Executable not found!${RESET}"
    echo -e "${WHITE}Run:${RESET} ./build.sh"
    exit 1
fi



echo -e "${GREEN}✔ Launching game...${RESET}"
echo


# ==========================
# Run game
# ==========================

clear

./bin/Herion_Hero

EXIT_CODE=$?


echo

if [ $EXIT_CODE -eq 0 ]; then
    echo -e "${GREEN}✔ Game closed normally.${RESET}"
else
    echo -e "${RED}✘ Game crashed with code ${EXIT_CODE}${RESET}"
fi