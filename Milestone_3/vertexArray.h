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
  unsigned int stride = 0;
  unsigned int offset = 0;
  VertexBuffer* vertexBuffer;
  // std::unique_ptr<VertexBuffer> vertexBuffer;
public:
  unsigned int ID;
  VertexArray(void* vertexData, unsigned int size, std::vector<VertexAttrib>& vertexAttribs);
  ~VertexArray();
  void bind() const;
  void unbind() const;
};