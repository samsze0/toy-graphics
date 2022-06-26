cmake_minimum_required(VERSION 3.13)

project(
  MyProject VERSION 1.0
  DESCRIPTION "Opengl playground"
  LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 11)

# Compile to exe, with all source files
add_executable(myexe
  main.cpp
  shader.cpp
  shader.h
  error.cpp
  error.h
  vertexBuffer.cpp
  vertexBuffer.h
  indexBuffer.cpp
  indexBuffer.h
  vertexArray.cpp
  vertexArray.h
  vertexAttrib.cpp
  vertexAttrib.h
  vertexAttribVector.cpp
  vertexAttribVector.h
  renderer.cpp
  renderer.h
)

# External dependencies (dynamic)
find_package(GLEW REQUIRED)

# External dependencies (static)
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/stb)


# Link lib to main
target_link_libraries(myexe
  PRIVATE glfw
  PRIVATE glad
  PRIVATE stb
)

# Such that include path is independent of project structure
target_include_directories(myexe
  PRIVATE external/glfw/include/
  PRIVATE external/glad/include/
  PRIVATE external/stb/include/
)