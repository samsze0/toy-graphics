#version 410 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec3 vertexColor;

void main() {
  gl_Position.xy = position;
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;

  vertexColor = color;
}