#version 410 core

in vec3 vertexColor;
in vec2 texCoord;

out vec4 fragColor;

uniform float blueColor;
uniform sampler2D Texture;

void main() {
  // fragColor.rg = vertexColor.rg;
  // fragColor.b = blueColor;
  // // Need to enable blending to support transparency effects
  // fragColor.a = 1.0f;

  fragColor = texture(Texture, texCoord);
  fragColor.rg *= vertexColor.rg;
  fragColor.b *= blueColor;
}