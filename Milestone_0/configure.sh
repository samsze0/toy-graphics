#!/bin/sh

cmake -S . -B build/ \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cp build/compile_commands.json .