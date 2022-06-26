#include <glad/glad.h>
#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "error.h"
#include <iostream>
#include <stdexcept>


// lvalue & rvalue. Return string ref instead?
static std::string ParseShaderSourceFromFile(const std::string& shaderSourcePath) {
  std::ifstream fileStream(shaderSourcePath);
  std::stringstream stringStream;

  if (fileStream.fail())
    throw std::runtime_error("File " + shaderSourcePath + " not found");

  std::string line;
  while (getline(fileStream, line)) {
    stringStream << line << '\n';
  }
  return stringStream.str();
}

// static function here? inline?
static int CompileShader(unsigned int type, const std::string& shaderSource) {
  unsigned int shaderObj = glCreateShader(type);
  const char* shaderSource_cstr = shaderSource.c_str();

  // ID; no. strings; shader source; null
  GLCheckError(glShaderSource(shaderObj, 1, &shaderSource_cstr, nullptr));
  GLCheckError(glCompileShader(shaderObj));

  int success;
  GLCheckError(glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success));
  if (!success) {
    char infoLog[512];
    GLCheckError(glGetShaderInfoLog(shaderObj, 512, NULL, infoLog));
    GLCheckError(glDeleteShader(shaderObj));
    throw std::runtime_error("OpenGL shader compilation failed\n" + std::string(infoLog));
  }

  return shaderObj;
}

static int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
  unsigned int shaderProgram = glCreateProgram();
  unsigned int vertexShaderObj = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
  unsigned int fragmentShaderObj = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  GLCheckError(glAttachShader(shaderProgram, vertexShaderObj));
  GLCheckError(glAttachShader(shaderProgram, fragmentShaderObj));
  GLCheckError(glLinkProgram(shaderProgram));
  GLCheckError(glValidateProgram(shaderProgram));

  // Delete shader objects after link
  GLCheckError(glDeleteShader(vertexShaderObj));
  GLCheckError(glDeleteShader(fragmentShaderObj));

  return shaderProgram;
}

Shader::Shader(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath) {
  std::string vertexShaderSource = ParseShaderSourceFromFile(vertexShaderSourcePath);
  std::string fragmentShaderSource = ParseShaderSourceFromFile(fragmentShaderSourcePath);

  this->ID = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader() {
  GLCheckError(glDeleteProgram(this->ID));
}

int Shader::GetUniformLocation(const std::string& name) {
  if (this->UniformLocationCache.find(name) != UniformLocationCache.end())
    // std::cout << "Retrieve uniform " << name << " from cache" << std::endl;
    return UniformLocationCache[name];

  GLCheckError(int location = glGetUniformLocation(this->ID, (const char*)&name));
  return location;
}

void Shader::SetUniform1f(const std::string& name, float v0) {
  GLCheckError(glUniform1f(this->GetUniformLocation(name), v0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
  GLCheckError(glUniform4f(this->GetUniformLocation(name), v0, v1, v2, v3)); 
}

void Shader::SetUniform1i(const std::string& name, int v0) {
  GLCheckError(glUniform1i(this->GetUniformLocation(name), v0));
}

void Shader::use() const {
  GLCheckError(glUseProgram(this->ID));
}