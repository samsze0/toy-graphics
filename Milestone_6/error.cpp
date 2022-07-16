#include "error.h"


void GLClearError() {
  while (glGetError());
}

bool GLGetError(const char* function, const char* file, int line) {
  bool no_error = true;

  while (GLenum error = glGetError()) {
    no_error = false;
    ERROR("[OpenGL] ({0}){1} {2}:{3}", error, function, file, line);
  }
  return no_error;
}