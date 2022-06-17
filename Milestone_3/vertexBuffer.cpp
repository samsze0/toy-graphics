#include "vertexBuffer.h"
#include "error.h"
#include <glad/glad.h>


VertexBuffer::VertexBuffer(const void* vertexData, unsigned int size) {
  GLCheckError(glGenBuffers(1, &(this->ID)));

  GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, this->ID));
  // GLCheckError(glBufferData(GL_ARRAY_BUFFER, 4 * (2 + 3) * sizeof(float), vertexData, GL_STATIC_DRAW));
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