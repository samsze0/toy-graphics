#pragma once

#include <string>


class Shader {
public:
  unsigned int ID;
  Shader(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath);
  ~Shader();
private:
  unsigned int GetUniformLocation(const std::string& name) const;
public:
  void use();
  void SetUniform1f(const std::string& name, float v0);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};