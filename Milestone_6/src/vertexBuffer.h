#pragma once

#include "pch.h"


class VertexBuffer {
public:
  unsigned int ID;
  unsigned int size;
  VertexBuffer(const void* vertexData, unsigned int size);
  ~VertexBuffer();
  void Bind() const;
  void Unbind() const;
};