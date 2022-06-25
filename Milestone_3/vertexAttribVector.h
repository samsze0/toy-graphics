#pragma once
#include <vector>
#include "vertexAttrib.h"


class VertexAttribVector {
private:
  std::vector<VertexAttrib> elements;
  unsigned int stride = 0;
public:
  VertexAttribVector();
  // VertexAttribVector(std::vector<VertexAttrib> elements);

  // Template specialisation
  template<typename T>
  void Push(unsigned int count, bool normalise);

  template<>
  void Push<float>(unsigned int count, bool normalise);

  template<>
  void Push<unsigned int>(unsigned int count, bool normalise);

  const std::vector<VertexAttrib>& GetElements() const;
  unsigned int GetStride() const;
};