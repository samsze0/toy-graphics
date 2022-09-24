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
  texture.cpp
  texture.h
  camera.cpp
  camera.h
  ui/demo.cpp
  ui/demo.h
  ui/menu.cpp
  ui/menu.h
  ui/stats.cpp
  ui/stats.h
  model/vertexData.cpp
  model/vertexData.h
  model/translationList.cpp
  model/translationList.h

  bindings/imgui_impl_glfw.cpp
  bindings/imgui_impl_opengl3.cpp
  bindings/imgui_impl_glfw.h
  bindings/imgui_impl_opengl3.h
  bindings/imgui_impl_opengl3_loader.h
)

# External dependencies (dynamic)
# find_package(GLEW REQUIRED)

# External dependencies (static)
# add_subdirectory(external/glfw)
# add_subdirectory(external/glad)
# add_subdirectory(external/stb)
# add_subdirectory(external/glm)
# add_subdirectory(external/imgui)

# Link lib to main
target_link_libraries(myexe
  # PRIVATE glfw
  # PRIVATE glad
  # PRIVATE stb
  # PRIVATE glm
  # PRIVATE imgui
  ${CONAN_LIBS}
)

# Such that include path is independent of project structure
# target_include_directories(myexe
#   PRIVATE external/glfw/include/
#   PRIVATE external/glad/include/
#   PRIVATE external/stb/include/
#   PRIVATE external/glm/
#   PRIVATE external/imgui/
#   PRIVATE external/imgui/backends/
# )