#!/bin/bash

set -e

if [ ! -d build ]; then
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
fi

cmake --build build -j8
