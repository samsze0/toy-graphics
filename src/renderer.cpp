#include "renderer.h"
#include "error.h"
#include <iostream>
#include <glad/glad.h>


void Renderer::Init() const {
  // For texture
  // Padding/alignment issue: OpenGL expects row of pixels to be padded to a multiple of 4 bytes
  // https://stackoverflow.com/questions/15983607/opengl-texture-tilted
  GLCheckError(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

  // For blending
  // glBlendFunc(src, dest)
  // src: default is GL_ONE
  // dest: default is GL_ZERO
  // Apply blend func to all color channels (all of RGBA)
  GLCheckError(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  // Set blend mode: default is GL_FUNC_ADD
  GLCheckError(glBlendEquation(GL_FUNC_ADD));
}

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

void Renderer::EnableDepthTest() const {
  // Enable Z-buffer depth-test
  // To be disabled if need to render transparent objects
  GLCheckError(glEnable(GL_DEPTH_TEST));
}

void Renderer::DisableDepthTest() const {
  GLCheckError(glDisable(GL_DEPTH_TEST));
}

void Renderer::EnableFaceCulling() const {
  GLCheckError(glEnable(GL_CULL_FACE));
}

void Renderer::DisableFaceCulling() const {
  GLCheckError(glDisable(GL_CULL_FACE));
}

void Renderer::EnableBlending() const {
  GLCheckError(glEnable(GL_BLEND));
}

void Renderer::DisableBlending() const {
  GLCheckError(glDisable(GL_BLEND));
}