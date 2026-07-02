#!/bin/bash

set -e

if [ ! -d build ]; then
    cmake -S . -B build
fi

cmake --build build -j8
