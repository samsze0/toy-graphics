#include <glad/glad.h>
#include <iostream>
#include "error.h"


void GLClearError() {
  while (glGetError());
}

bool GLGetError(const char* function, const char* file, int line) {
  bool no_error = true;

  while (GLenum error = glGetError()) {
    no_error = false;
    std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << ":" << line << std::endl;
  }
  return no_error;
}