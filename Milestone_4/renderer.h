#pragma once

#include "vertexArray.h"
#include "shader.h"


class Renderer {
public:
  void Clear() const;
  void Clear(float r, float g, float b, float a) const;
  void Draw(const VertexArray& vertexArray, const Shader& shader) const;
  void EnableDepthTest() const;
  void DisableDepthTest() const;
  void EnableFaceCulling() const;
  void DisableFaceCulling() const;
};