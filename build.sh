#!/bin/bash

set -e

if [ ! -d sfml_build ]; then
    mkdir sfml_build
fi

echo "Building SFML"

pushd sfml_build

cmake -G 'Unix Makefiles' \
    -DCMAKE_OSX_ARCHITECTURES='x86_64' \
    -DCMAKE_CXX_COMPILER='/usr/bin/clang++' \
    -DCMAKE_C_COMPILER='/usr/bin/clang' \
    -DSFML_BUILD_FRAMEWORKS='OFF' \
    -DCMAKE_CXX_FLAGS='-stdlib=libc++' \
    -DCMAKE_C_FLAGS='-stdlib=libc++' \
    ../sfml

make -j4

popd

echo "Generating scratchPad"

if [ ! -d build ]; then
    mkdir build
fi

pushd build 

cmake ..
make