#version 410 core

in vec3 vertexColor;
in vec2 texCoord;

out vec4 fragColor;

uniform float mixRatio;
uniform float opacity;

uniform sampler2D Texture1;  // texture sampler data type
uniform sampler2D Texture2;  // texture sampler data type

void main() {
  fragColor = mix(
    texture(Texture1, texCoord),
    texture(Texture2, texCoord),
    1
    // mixRatio
  );  // 80% of first color & 20% of second
  fragColor.a = opacity;
}