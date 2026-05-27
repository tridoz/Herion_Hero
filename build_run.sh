rm -rf build
cmake -S . -B build
cmake --build build -j4
./bin/Herion_Hero
