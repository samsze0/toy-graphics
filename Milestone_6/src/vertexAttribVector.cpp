#include "vertexAttribVector.h"


VertexAttribVector::VertexAttribVector() {}

const std::vector<VertexAttrib>& VertexAttribVector::GetElements() const {
  return this->elements;
}

unsigned int VertexAttribVector::GetStride() const {
  return this->stride;
}

// See enforcing template type through static assert
// https://stackoverflow.com/questions/17679268/enforce-template-type-through-static-assert
template<typename T>
void VertexAttribVector::Push(unsigned int count, bool normalise) {
  // static_assert(false);  // !!throw exception at compile time
  static_assert(sizeof(T) == 0, "Template type is enforced");
}

template<>
void VertexAttribVector::Push<float>(unsigned int count, bool normalise) {
  this->elements.push_back({count, GL_FLOAT, normalise});
  this->stride += count * sizeof(GLfloat);
}

template<>
void VertexAttribVector::Push<unsigned int>(unsigned int count, bool normalise) {
  this->elements.push_back({count, GL_UNSIGNED_INT, normalise});
  this->stride += count * sizeof(GLuint); 
}