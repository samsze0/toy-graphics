#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

// uniform mat4 MVP;  // Model-view-projection transformation matrix
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 vertexColor;
out vec2 texCoord;

void main() {
  gl_Position = Projection * View * Model * vec4(aPos, 1.0f);

  texCoord = aTexCoord;
}