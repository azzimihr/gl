#pragma once

#include <random>
#include "glad/glad.h"

#include "enum.h"

f randF(){
  thread_local mt19937 gen(random_device{}());;
  static uniform_real_distribution<f> dist{0.0, 1.0};
  return dist(gen);
}

ui Shader(ui type, const char **source, ui program){
  ui shader = glCreateShader(type);
  glShaderSource(shader, 1, source, NULL);
  glCompileShader(shader);
  glAttachShader(program, shader);
  return shader;
}

ui Program(const char **vs, const char **fs){
  ui program = glCreateProgram();
  ui vert = Shader(GL_VERTEX_SHADER, vs, program);
  ui frag = Shader(GL_FRAGMENT_SHADER, fs, program);
  
  glLinkProgram(program);
  glDeleteShader(frag);
  glDeleteShader(vert);
  return program;
}