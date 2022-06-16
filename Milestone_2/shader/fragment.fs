#version 410 core

in vec3 vertexColor;

out vec4 fragColor;

uniform float blueColor;

void main() {
  fragColor.rg = vertexColor.rg;
  fragColor.b = blueColor;
  // Need to enable blending to support transparency effects
  fragColor.a = 1.0f;
}