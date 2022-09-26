# pragma once

#include "pch.pch"

#define GLCheckError(x) \
  GLClearError(); \
  x; \
  assert(GLGetError(#x, __FILE__, __LINE__))


void GLClearError();

bool GLGetError(const char* function, const char* file, int line);