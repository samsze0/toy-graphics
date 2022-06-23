#pragma once

#include <vector>
#include "vertexBuffer.h"


class VertexAttrib {
public:
  unsigned int count;
  VertexAttrib(unsigned int count);
};


class VertexArray {
private:
  unsigned int stride = 0;  // can also be initialised in constructor initialiser list instead
  unsigned int offset = 0;
  VertexBuffer vertexBuffer;  // has the same lifetime as the VertexArray obj itself
  // VertexBuffer* vertexBuffer;
  // std::unique_ptr<VertexBuffer> vertexBuffer;
public:
  unsigned int ID;
  // std::vector will allocate memory on heap behind the scene. Hence performance is worse
  // However std::array require size to be known at compile time, which requires chain of templated classes & functions
  VertexArray(void* vertexData, unsigned int size, std::vector<VertexAttrib>& vertexAttribs);
  ~VertexArray();
  void bind() const;
  void unbind() const;
};