#include "vertexAttribVector.h"
#include <glad/glad.h>
#include <iostream>


VertexAttribVector::VertexAttribVector() {}

// VertexAttribVector::VertexAttribVector(std::vector<VertexAttrib> elements)
//   : elements(elements) {}

const std::vector<VertexAttrib>& VertexAttribVector::GetElements() const {
  return this->elements;
}

unsigned int VertexAttribVector::GetStride() const {
  return this->stride;
}

template<typename T>
void VertexAttribVector::Push(unsigned int count, bool normalise) {
  // static_assert(false);  // throw exception at compile time
  std::cout << "static_assert(false);" << std::endl;
}

template<>
void VertexAttribVector::Push<float>(unsigned int count, bool normalise) {
  this->elements.push_back({count, GL_FLOAT, normalise}); // implicit conversion to VertexAttrib
  // this.stride += 4;
  this->stride += count * sizeof(GLfloat);
}

template<>
void VertexAttribVector::Push<unsigned int>(unsigned int count, bool normalise) {
  this->elements.push_back({count, GL_UNSIGNED_INT, normalise});
  this->stride += count * sizeof(GLuint); 
}