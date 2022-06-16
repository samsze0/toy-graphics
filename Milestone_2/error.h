# pragma once

#include <cassert>

#define GLCheckError(x) \
  GLClearError(); \
  x; \
  assert(GLGetError())

// #define GLCheckError(x)\
//   x


void GLClearError();

bool GLGetError();