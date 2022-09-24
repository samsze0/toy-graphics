cmake_minimum_required(VERSION 3.13)

project(
  MyProject VERSION 1.0
  DESCRIPTION "Opengl playground"
  LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Compile to exe, with all source files
add_executable(myexe
  main.cpp
  adder.cpp
  adder.h
)

# Trigger CMakeLists.txt of subdirectory
add_subdirectory(
  Mult/
)

# Link lib to main
target_link_libraries(myexe
  mult
  ${CONAN_LIBS}
)

# Such that include path is independent of project structure
target_include_directories(myexe
  PUBLIC Mult/
)