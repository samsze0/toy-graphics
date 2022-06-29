#include "renderer.h"
#include "error.h"
#include <iostream>


void Renderer::Clear() const {
  this->Clear(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::Clear(float r, float g, float b, float a) const {
  GLCheckError(glClearColor(r, g, b, a));
  GLCheckError(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));  // Clear both Color buffer &  Depth buffer
}

void Renderer::Draw(const VertexArray& vertexArray, const Shader& shader) const {
  shader.use();
  vertexArray.bind();

  if (vertexArray.GetIndexBuffer() != nullptr) {
    GLCheckError(glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBuffer()->count, GL_UNSIGNED_INT, 0));
  } else {
    GLCheckError(glDrawArrays(GL_TRIANGLES, 0, vertexArray.GetVertexBuffer().size / vertexArray.GetStride()));
  }
}