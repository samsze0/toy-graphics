cmake_minimum_required(VERSION 3.13.4)

project(MyProject VERSION 1.0
  DESCRIPTION "Very nice project"
  LANGUAGES CXX)

# Compile to exe
add_executable(myexe main.cpp adder.cpp)

# Trigger CMakeLists.txt of subdirectory
add_subdirectory(Mult)

# Link lib to main
target_link_libraries(myexe mult)

# Such that include path is independent of project structure
target_include_directories(myexe PRIVATE Mult)