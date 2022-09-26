#pragma once

#include "pch.h"


class Shader {
private:
  std::unordered_map<std::string, int> UniformLocationCache;
public:
  unsigned int ID;
  Shader(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath);
  ~Shader();
private:
  int GetUniformLocation(const std::string& name);
public:
  void use() const;
  void SetUniform1f(const std::string& name, float v0);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  void SetUniform1i(const std::string& name, int v0);
  void SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat);
};