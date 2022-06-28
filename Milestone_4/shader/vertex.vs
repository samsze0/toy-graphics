#version 410 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 MVP;  // Model-view-projection transformation matrix

out vec3 vertexColor;
out vec2 texCoord;

void main() {
  // gl_Position.xy = aPos;
  // gl_Position.z = 0.0;
  // gl_Position.w = 1;
  gl_Position = MVP * vec4(aPos, 0.0f, 1.0f);

  vertexColor = aColor;
  texCoord = aTexCoord;
}