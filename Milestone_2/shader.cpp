#include <glad/glad.h>
#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>


// lvalue & rvalue. Return string ref instead?
static std::string ParseShaderSourceFromFile(const std::string& shaderSourcePath) {
  std::ifstream fileStream(shaderSourcePath);
  std::stringstream stringStream;

  std::string line;
  while (getline(fileStream, line)) {
    stringStream << line << '\n';
  }
  return stringStream.str();
}

// static function here? inline?
static unsigned int CompileShader(unsigned int type, const std::string& shaderSource) {
  unsigned int shaderObj = glCreateShader(type);
  const char* shaderSource_cstr = shaderSource.c_str();

  // ID; no. strings; shader source; null
  glShaderSource(shaderObj, 1, &shaderSource_cstr, nullptr);
  glCompileShader(shaderObj);

  int success;
  glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shaderObj, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    glDeleteShader(shaderObj);
    return -1;
  }

  return shaderObj;
}

static unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
  unsigned int shaderProgram = glCreateProgram();
  unsigned int vertexShaderObj = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
  unsigned int fragmentShaderObj = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  glAttachShader(shaderProgram, vertexShaderObj);
  glAttachShader(shaderProgram, fragmentShaderObj);
  glLinkProgram(shaderProgram);
  glValidateProgram(shaderProgram);

  // Delete shader objects after link
  glDeleteShader(vertexShaderObj);
  glDeleteShader(fragmentShaderObj);

  return shaderProgram;
}

Shader::Shader(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath) {
  std::string vertexShaderSource = ParseShaderSourceFromFile(vertexShaderSourcePath);
  std::string fragmentShaderSource = ParseShaderSourceFromFile(fragmentShaderSourcePath);

  this->ID = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}