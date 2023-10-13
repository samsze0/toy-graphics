# Configure & Generate (i.e. project file generation) (CMake)
# -> Build (e.g. make, VS, Ninja, XCode)
# -> Test (e.g. CTest)
# -> Package (e.g. CPack)

cmake_minimum_required(VERSION 3.21)

# Responsibilities:
# - Check if the enabled lanaguages' compilers are able to compile and link
# - Once that's done, setup number of variables and properties
project(
  MyProject VERSION 1.0
  DESCRIPTION "App"
  LANGUAGES CXX
)

# Variables:

# All variables are string
# Variables are block-scoped (e.g. if() endif() or block() endblock()) and directory-scoped (e.g. add_subdirectory()), but
# `include()` isn't variable-scoped.

# Space-separated strings e.g. "A" "B" are equivalent to "A;B", which
# is how list is represented in CMake.
# String can be surrounded by " " or [[ ]], or [=[ ]=], or [==[ ]==] (inspired by Lua), variable
# substitution or escaping is not allowed in the latter.

# Environment variables:
# Can be read using $ENV{}
# Can be writen using set(ENV{}, )
# Environment will be reset when current CMake instance exits.

# Cached variables: more advanced

# Variables can be logged using `message()`

# String operations (e.g. uppercase) can be performed using `string()`.
# List operations (e.g. append) can be performed using `list()`.
# Math operations with `math()`.

# CMake internal variables:
# https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html

# Properties:
# Commands for read/write properties: `set_property()` and `get_property()`.
# Properties must be attached to some entity(s). These entity(s) can be DIRECTORY, TARGET, SOURCE (source file),
# TEST (test case), CACHE (cache variable), or even GLOBAL (the whole build process itself). This distinguishes property from variable.

set (CMAKE_CXX_STANDARD 11)

# Flow control:
# `if() endif()`, `foreach() endforeach()`, and `while() endwhile()`
# continue() and break()
# Boolean true = "ON" / "YES" / "TRUE" / "Y" (case insensitive)
# Logic operators: AND / OR / NOT
# Comparision operators:
# - for numeric: LESS, ...
# - for string: STRLESS, ...
# - for version: VRESION_LESS, ..
# - for path: PATH_EQUAL, ...
# File system tests operators: EXISTS / IS_DIRECTORY / ...
# Existence tests operators: DEFINED / COMMAND (test whether a command or function or macro exists) / ...

find_package(glfw 3.3.8 REQUIRED)
find_package(glew 2.2.0 REQUIRED)
find_package(glm 0.9.9.8 REQUIRED)
find_package(stb 2021-09-10 REQUIRED)
find_package(imgui 1.89.5 REQUIRED)

# add_executable
# Notable options:
# WIN32: for building Windows GUI app
# MACOSX_BUNDLE: for building OSX or IOS .bundle

# Target is library? use the `add_library` command
# `add_library` comes with option STATIC | SHARED | MODULE, but
# it is better to leave flexibility to the person building the library.
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

# Notable options:
# - PRIVATE: when A completely hide its dep B
# - PUBLIC: A exposes B. Having A as direct dep will require B as direct dep as well
# - INTERFACE: similar to PUBLIC except that A doesn't use B internally
# This command can also take these items as arguments (besides CMake targets):
# - Path to existing library
# - Name of existing library (e.g. `foo` becomes `-lfoo` or `foo.lib`)
# - Link flag (strings begin with `-l` or `-framework`)
# target_link_libraries(app
#   PRIVATE glfw
#   PRIVATE glad
#   PRIVATE stb
#   PRIVATE glm
#   PRIVATE imgui
# )

# Subdirectories:
# Commands: `add_subdirectory()` and `include()`

# `add_subdirectory`
# Evaluate a subdirectory's (specified by path) CMakeLists.txt.
# The following CMake internal variables help track the location of source dir and binary dir:
# `CMAKE_SOURCE_DIR` and `CMAKE_BINARY_DIR`: dirs locations of the root directory. These two variables should be avoided for best practices
# `CMAKE_CURRENT_SOURCE_DIR` and `CMAKE_CURRENT_BINARY_DIR`
# Project-specific variables also exist: (referring to the directory that most recently called `project()`)
# `PROJECT_SOURCE_DIR`, `PROJECT_BINARY_DIR`
# `projectName_SOURCE_DIR`, `projectName_BINARY_DIR`
# target_include_directories(app
#   PRIVATE glfw
#   PRIVATE glad
#   PRIVATE stb
#   PRIVATE glm
#   PRIVATE imgui
# )

# `include()`
# Doesn't introduce new variable scope. Doesn't introduce new policy scope.
# Doesn't introduce new value for CMAKE_CURRENT_SOURCE_DIR and CMAKE_CURRENT_BINARY_DIR.
# Because `include()` behaves in a weird way, new internal variables are added to CMake:
# e.g. `CMAKE_CURRENT_LIST_DIR` (analogous to `CMAKE_CURRENT_SOURCE_DIR`) except that `include()` will update this.

# Returning early (for current file):
# with `return()`. However, the better practice is to use `include_guard()`.
# `return()` can optionally take a keyword argument `PROPAGATE` which causes
# any preceding variables' value to be propagated to the calling scope.

# Functions & macros:

# Similar to each other. Except that the arguments of function are defined and treated as variables, so
# DEFINED argName eval to TRUE.

# Arguments to macro are string substituted into the body of the macro. Pitfall: only `${argName}` is substituted, `argName` alone is not.
# Both function and macros come with set of internal variables: ARGC, ARGV, ARGN. These variables allow
# function/macro to access the unnamed arguments that were given.

# Individual argument (named/unnamed) can be accessed by ARGx where x in [0, ARGC-1] inclusive.

# To turn the unnamed/optional positional arguments into "keyword" arguments (e.g. ARG1 arg2 arg3), there is the built-in command
# `cmake_parse_arguments()`. But this mechanisms still cannot replicate built-in commands like `target_link_libraries()` because
# PRIVATE | PUBLIC | INTERFACE might get repeated more than once.
# Generally it is good practice to use `cmake_parse_arguments()`, but be careful when empty arguments are supplied to the function/macro,
# as the list of arguments might get flattened implicitly.

# `return()` command in function behaves similarly to top-level `return()`.

# Defined function or macro `func` can be overriden by defining a new one. The old one will be available as `_func`, but
# generally it is bad practice to use the old one.

# The following internal variables are  available inside a function (not macro):
# `CMAKE_CURRENT_FUNCTION`: name of the function
# `CMAKE_CURRENT_FUNCTION_LIST_FILE`, `CMAKE_CURRENT_FUNCTION_LIST_DIR`: name of the file/directory holding the function

# The built-in command `cmake_language()` can be used to evaluate arbitrary CMake code or execute a variable as command (like a function object).
# `cmake_language(EVAL)` paired well with `[=[ ]=]`