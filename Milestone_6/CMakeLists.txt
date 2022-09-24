cmake_minimum_required(VERSION 3.13)

project(
  MyProject VERSION 1.0
  DESCRIPTION "Opengl playground"
  LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# See hard-coded source file vs GLOB
# https://stackoverflow.com/questions/1027247/is-it-better-to-specify-source-files-with-glob-or-each-file-individually-in-cmak

# Compile to exe, with all source files
add_executable(myexe
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
  src/logger.cpp
  src/logger.h
  src/event/appEvent.cpp
  src/event/appEvent.h
  src/event/event.cpp
  src/event/event.h
  src/event/eventDispatcher.cpp
  src/event/eventDispatcher.h
  src/event/keyEvent.cpp
  src/event/keyEvent.h
  src/event/mouseEvent.cpp
  src/event/mouseEvent.h
  src/event/windowEvent.cpp
  src/event/windowEvent.h

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
# add_subdirectory(external/spdlog)


# Link lib to main
target_link_libraries(myexe
  # PRIVATE
    # glfw
    # glad
    # stb
    # glm
    # imgui
    # spdlog
  ${CONAN_LIBS}
)

# Such that include path is independent of project structure
# target_include_directories(myexe
#   PRIVATE
#     external/glfw/include/
#     external/glad/include/
#     external/stb/include/
#     external/glm/
#     external/imgui/
#     external/imgui/backends/
#     external/spdlog/
# )

# See
# https://cmake.org/cmake/help/latest/command/target_precompile_headers.html
target_precompile_headers(myexe
  PRIVATE
    src/pch.h
)