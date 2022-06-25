#include "vertexBuffer.h"
#include "error.h"
#include <glad/glad.h>


VertexBuffer::VertexBuffer(const void* vertexData, unsigned int size)
  : size(size) {
  GLCheckError(glGenBuffers(1, &(this->ID)));

  GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, this->ID));
  GLCheckError(glBufferData(GL_ARRAY_BUFFER, size, vertexData, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
  GLCheckError(glDeleteBuffers(1, &(this->ID)));
}

void VertexBuffer::Bind() const {
  GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, this->ID));
}

void VertexBuffer::Unbind() const {
  GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, 0));
}