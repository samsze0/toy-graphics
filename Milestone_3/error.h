# pragma once

#include <cassert>

#define GLCheckError(x) \
  GLClearError(); \
  x; \
  assert(GLGetError(#x, __FILE__, __LINE__))

// #define GLCheckError(x)\
//   x


void GLClearError();

bool GLGetError(const char* function, const char* file, int line);