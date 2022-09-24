#!/bin/sh

mkdir -p build

cd build

conan install ../

cd ../

cmake -S . -B build/ \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON  # generate makefiles

cp build/compile_commands.json .