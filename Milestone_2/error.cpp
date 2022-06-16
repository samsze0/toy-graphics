#include <glad/glad.h>
#include <iostream>
#include "error.h"


void GLClearError() {
  while (glGetError());
}

bool GLGetError() {
  bool no_error = true;

  while (GLenum error = glGetError()) {
    no_error = false;
    std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
  }
  return no_error;
}