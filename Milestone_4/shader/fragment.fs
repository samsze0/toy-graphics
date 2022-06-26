#version 410 core

in vec3 vertexColor;
in vec2 texCoord;

out vec4 fragColor;

uniform float blueColor;
uniform sampler2D Texture1;  // texture sampler data type
uniform sampler2D Texture2;  // texture sampler data type

void main() {
  // fragColor.rg = vertexColor.rg;
  // fragColor.b = blueColor;
  // // Need to enable blending to support transparency effects
  // fragColor.a = 1.0f;

  // fragColor = texture(Texture1, texCoord);  // built-in function: take texture sampler & texture coord
  fragColor = mix(
    texture(Texture1, texCoord),
    texture(Texture2, texCoord),
    0.5
  );  // 80% of first color & 20% of second
  fragColor.rg *= vertexColor.rg;
  fragColor.b *= blueColor;
}