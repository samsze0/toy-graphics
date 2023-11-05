cmake_minimum_required(VERSION 3.27)

project(
  MyProject VERSION 1.0
  DESCRIPTION "App"
  LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 11)

find_package(glfw 3.3.8 REQUIRED)
find_package(glew 2.2.0 REQUIRED)
find_package(glm 0.9.9.8 REQUIRED)
find_package(stb 2021-09-10 REQUIRED)
find_package(imgui 1.89.5 REQUIRED)

add_executable(app
  src/main.cpp
  src/shader.cpp
  src/shader.h
  src/error.cpp
  src/error.h
  src/vertexBuffer.cpp
  src/vertexBuffer.h
  src/indexBuffer.cpp
  src/indexBuffer.h
  src/vertexArray.cpp
  src/vertexArray.h
  src/vertexAttrib.cpp
  src/vertexAttrib.h
  src/vertexAttribVector.cpp
  src/vertexAttribVector.h
  src/renderer.cpp
  src/renderer.h
  src/texture.cpp
  src/texture.h
  src/camera.cpp
  src/camera.h
  src/ui/demo.cpp
  src/ui/demo.h
  src/ui/menu.cpp
  src/ui/menu.h
  src/ui/stats.cpp
  src/ui/stats.h
  src/model/vertexData.cpp
  src/model/vertexData.h
  src/model/translationList.cpp
  src/model/translationList.h
)

target_link_libraries(app
  PRIVATE glfw
  PRIVATE glad
  PRIVATE stb
  PRIVATE glm
  PRIVATE imgui
)
