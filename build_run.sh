rm -rf build
cmake -S . -B build
cmake --build build -j8
./bin/Herion_Hero
