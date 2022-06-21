#pragma once

#include <string>


class Shader {
public:
  unsigned int ID;
  Shader(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath);
  ~Shader();
  void use();
};