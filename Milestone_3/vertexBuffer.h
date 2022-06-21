#pragma once


class VertexBuffer {
public:
  unsigned int ID;
  VertexBuffer(const void* vertexData, unsigned int size);
  ~VertexBuffer();
  void Bind() const;
  void Unbind() const;
};