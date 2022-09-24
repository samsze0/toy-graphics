# Fail statically linking GLEW (worth a retry)
# Dynamically link GLEW instead
# Linking GLEW dynamically
# https://stackoverflow.com/questions/27472813/linking-glew-with-cmake
# GLEW? GLAD? GL3W?
# https://www.reddit.com/r/opengl/comments/3m28x1/glew_vs_glad/

# [UPDATE] 24-09-2022: Using Conan

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
)

# External dependencies (dynamic)
# find_package(GLEW REQUIRED)

# External dependencies (static)
# add_subdirectory(external/glfw)

# add_subdirectory(external/glew)

# add_subdirectory(external/glad)


# Link lib to main
target_link_libraries(myexe
  # glfw
  # glew
  # GLEW::GLEW
  # glad
  ${CONAN_LIBS}
)

# Such that include path is independent of project structure
# target_include_directories(myexe
#   # PUBLIC external/glfw/include/
#   # PUBLIC external/glew/include
#   # PUBLIC external/glad/include/
# )