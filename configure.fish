#!/bin/sh
# https://lsp.sublimetext.io/guides/cplusplus/
cmake -S . -B build/ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cp build/compile_commands.json .