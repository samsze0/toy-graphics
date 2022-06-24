#pragma once

#include <vector>
#include "vertexBuffer.h"
#include "indexBuffer.h"


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
  IndexBuffer* indexBuffer = nullptr;
public:
  unsigned int ID;
  // std::vector will allocate memory on heap behind the scene. Hence performance is worse
  // However std::array require size to be known at compile time, which requires chain of templated classes & functions
  VertexArray(const void* vertexData, unsigned int size, std::vector<VertexAttrib>& vertexAttribs);
  // For EBO
  // Possibly separate out into own class?
  VertexArray(const void* vertexData, unsigned int size, const void* indices, unsigned int count, std::vector<VertexAttrib>& vertexAttribs);
  ~VertexArray();
  void bind() const;
  void unbind() const;
};