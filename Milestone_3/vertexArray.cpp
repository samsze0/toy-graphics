#include "vertexArray.h"
#include <glad/glad.h>
#include "error.h"
#include "vertexBuffer.h"
#include <iostream>
#include <memory>


VertexAttrib::VertexAttrib(unsigned int count)
  : count(count) {}


VertexArray::VertexArray(void* vertexData, unsigned int size, std::vector<VertexAttrib>& vertexAttribs) {
  GLCheckError(glGenVertexArrays(1, &(this->ID)));
  GLCheckError(glBindVertexArray(this->ID));

  // VBO

  this->vertexBuffer = new VertexBuffer(vertexData, size);  // and require heap allocation & manual de-allocation

  // Vertex Attribute Pointers

  // Stride: shared
  // Offset: individual

  // For calculating stride
  for (unsigned int i = 0; i < vertexAttribs.size(); i++) {
    VertexAttrib vertexAttrib = vertexAttribs[i];

    this->stride += vertexAttrib.count * sizeof(float);
  }
  std::cout << "Stride: " << this->stride << std::endl;

  // For calculuating offset
  for (unsigned int i = 0; i < vertexAttribs.size(); i++) {
    VertexAttrib vertexAttrib = vertexAttribs[i];

    std::cout << "Vertex Attrib " << i << " Offset: " << this->offset << std::endl;

    GLCheckError(glVertexAttribPointer(i, vertexAttrib.count, GL_FLOAT, GL_FALSE, this->stride, (void*)(size_t)(this->offset)));
    GLCheckError(glEnableVertexAttribArray(i));

    this->offset += vertexAttrib.count * sizeof(float);
  }
}

VertexArray::~VertexArray() {
  GLCheckError(glDeleteVertexArrays(1, &(this->ID)));
  delete this->vertexBuffer;
}

void VertexArray::bind() const {
  GLCheckError(glBindVertexArray(this->ID)); 
}

void VertexArray::unbind() const {
  GLCheckError(glBindVertexArray(0));
}