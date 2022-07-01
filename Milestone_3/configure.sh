#!/bin/sh

cmake -S . -B build/ \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DBUILD_SHARED_LIBS=OFF

# https://lsp.sublimetext.io/guides/cplusplus/

# GLFW options
# option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
# option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" ${GLFW_STANDALONE})
# option(GLFW_BUILD_TESTS "Build the GLFW test programs" ${GLFW_STANDALONE})
# option(GLFW_BUILD_DOCS "Build the GLFW documentation" ON)
# option(GLFW_INSTALL "Generate installation target" ON)

# cp build/compile_commands.json .

# Header files are not passed to compiler, hence no autocompletion
# See:
# https://lsp.sublimetext.io/guides/cplusplus/
# https://github.com/Sarcasm/compdb#introduction
compdb -p build/ list > compile_commands.json