#!/bin/bash
# File txt con i percorsi dei PNG
input_file="assets/all_textures.txt"
while IFS= read -r f; do
    # Salta righe vuote
    [[ -z "$f" ]] && continue

    # Converte PNG in BMP nella stessa cartella
    ffmpeg -y -i "$f" "${f%.png}.bmp" 
done < "$input_file"
