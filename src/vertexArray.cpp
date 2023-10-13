#include "vertexArray.h"
#include <glad/glad.h>
#include "error.h"
#include "vertexBuffer.h"
#include <iostream>
#include <memory>
#include <glad/glad.h>


VertexArray::VertexArray(const void* vertexData, unsigned int size, const VertexAttribVector& vertexAttribVector)
  : vertexBuffer(vertexData, size) {
  GLCheckError(glGenVertexArrays(1, &(this->ID)));
  GLCheckError(glBindVertexArray(this->ID));

  // Vertex Attribute Pointers

  // Stride: shared
  // Offset: individual

  // For calculating stride
  this->stride = vertexAttribVector.GetStride();
  std::cout << "Stride: " << this->stride << std::endl;

  // For calculuating offset
  std::vector<VertexAttrib> elements = vertexAttribVector.GetElements();
  for (unsigned int i = 0; i < elements.size(); i++) {
    VertexAttrib vertexAttrib = elements[i];

    std::cout << "Vertex Attrib " << i << " Offset: " << this->offset << std::endl;

    GLCheckError(glVertexAttribPointer(i, vertexAttrib.count, GL_FLOAT, GL_FALSE, vertexAttribVector.GetStride(), (void*)(size_t)(this->offset)));
    GLCheckError(glEnableVertexAttribArray(i));

    unsigned int sizeOfType;
    switch(vertexAttrib.type) {
      case GL_FLOAT: sizeOfType = sizeof(GLfloat);
      case GL_UNSIGNED_INT: sizeOfType = sizeof(GLuint);
    }

    this->offset += vertexAttrib.count * sizeOfType;
  }
}

// Delegating constructor
VertexArray::VertexArray(const void* vertexData, unsigned int size, const void* indices, unsigned int count, const VertexAttribVector& vertexAttribVector)
  : VertexArray(vertexData, size, vertexAttribVector) {
  // EBO
  this->indexBuffer = new IndexBuffer(indices, count);
}

VertexArray::~VertexArray() {
  GLCheckError(glDeleteVertexArrays(1, &(this->ID)));
  if (this->indexBuffer != nullptr)
    delete this->indexBuffer;
}

void VertexArray::bind() const {
  GLCheckError(glBindVertexArray(this->ID)); 
}

void VertexArray::unbind() const {
  GLCheckError(glBindVertexArray(0));
}

const VertexBuffer& VertexArray::GetVertexBuffer() const {
  return this->vertexBuffer;
}

const IndexBuffer* VertexArray::GetIndexBuffer() const {
  return this->indexBuffer;
}

unsigned int VertexArray::GetStride() const {
  return this->stride;
}