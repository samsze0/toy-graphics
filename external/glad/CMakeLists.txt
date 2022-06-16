cmake_minimum_required(VERSION 3.13)
project(Glad)

add_library(glad
  src/glad.c
)
target_include_directories(glad
  PRIVATE include/
)