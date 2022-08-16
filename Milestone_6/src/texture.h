#pragma once

#include "pch.h"


class Texture {
public:
  unsigned int ID;
  Texture(const std::string& filepath, unsigned int slot);
  ~Texture();
  void bind(unsigned int slot) const;
};