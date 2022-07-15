#include "indexBuffer.h"
#include "error.h"


IndexBuffer::IndexBuffer(const void* indices, unsigned int count)
  : count(count) {
  GLCheckError(glGenBuffers(1, &(this->ID)));

  GLCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID));
  GLCheckError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
  GLCheckError(glDeleteBuffers(1, &(this->ID)));
}

void IndexBuffer::Bind() const {
  GLCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID));
}

void IndexBuffer::Unbind() const {
  GLCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}