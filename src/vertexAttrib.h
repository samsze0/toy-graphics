#pragma once

#include <glad/glad.h>


class VertexAttrib {
public:
  unsigned int count;
  unsigned int type;
  bool normalise;
  VertexAttrib(unsigned int count, unsigned int type, bool normalise);
};