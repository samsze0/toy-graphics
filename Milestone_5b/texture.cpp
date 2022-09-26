#include "texture.h"
#include "error.h"
#include <stb_image.h>
#include <stdexcept>
#include <glad/glad.h>


Texture::Texture(const std::string& filepath, unsigned int slot) {
  int width, height, BPP;
  unsigned char* data;

  // LoadImage

  stbi_set_flip_vertically_on_load(true);
  // Fill width, height, & bit-per-pixel. No. color channels
  data = stbi_load(filepath.c_str(), &width, &height, &BPP, 3);
  if (data == nullptr)
    throw std::runtime_error("Fail to load image file " + filepath);

  // GenAndBindTexture

  GLCheckError(glGenTextures(1, &(this->ID)));
  GLCheckError(glActiveTexture(GL_TEXTURE0 + slot));  // implicit ; GL_TEXTURE0 is activated by default
                                                      // texture unit - "slot" of texture
                                                      // "slots" enum are consecutive
  GLCheckError(glBindTexture(GL_TEXTURE_2D, this->ID));     // bind to the active texture unit

  // set the texture wrapping/filtering options (on currently bound texture)
  GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  // With mipmap
  // GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
  // GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
  // GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
  // GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
  GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  // LoadImageToTexture

  // Texture target ; Mipmap level ; Storage format of texture ; width & height of texture ; border width ; Source image format ; Image data
  GLCheckError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
  GLCheckError(glGenerateMipmap(GL_TEXTURE_2D));  // Optional. Automatically generate all mipmaps
  stbi_image_free(data);  // Ownership problem: not a good idea to free memory in somewhere different from where it is allocated
}

Texture::~Texture() {
  GLCheckError(glDeleteTextures(1, &(this->ID)));
}

void Texture::bind(unsigned int slot) const {
  GLCheckError(glActiveTexture(GL_TEXTURE0 + slot));
  GLCheckError(glBindTexture(GL_TEXTURE_2D, this->ID));     // bind to the active texture unit 
}