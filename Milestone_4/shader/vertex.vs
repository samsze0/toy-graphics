#version 410 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

void main() {
  gl_Position.xy = aPos;
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;

  vertexColor = aColor;
  texCoord = aTexCoord;
}