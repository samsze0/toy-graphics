#pragma once

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexAttrib.h"
#include "vertexAttribVector.h"
#include "pch.pch"


class VertexArray {
private:
  unsigned int stride = 0;
  unsigned int offset = 0;
  VertexBuffer vertexBuffer;
  IndexBuffer* indexBuffer = nullptr;
public:
  unsigned int ID;
  VertexArray(const void* vertexData, unsigned int size, const VertexAttribVector& vertexAttribs);
  // For EBO
  VertexArray(const void* vertexData, unsigned int size, const void* indices, unsigned int count, const VertexAttribVector& vertexAttribVector);
  ~VertexArray();
  void bind() const;
  void unbind() const;
  const VertexBuffer& GetVertexBuffer() const;
  const IndexBuffer* GetIndexBuffer() const;
  unsigned int GetStride() const;
};