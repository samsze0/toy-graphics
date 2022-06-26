#pragma once

#include <string>
#include <unordered_map>


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
};