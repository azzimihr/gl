#pragma once

#include "glad/glad.h"

#include "enum.h"

template<typename... Args>
void genBuffers(GLuint& VAO, Args&... args) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    (glGenBuffers(1, &args), ...);
}

void tri(ui offset, ui count, ui prog){
  glUseProgram(prog);
  glDrawArrays(GL_TRIANGLES, offset,count);
}


void bindData(ui BO, ui type, const void* data, long len){
  glBindBuffer(type, BO);
  glBufferData(type, len, data, GL_STATIC_DRAW);
}

void instruct(ui vec, const void * offset){
  glVertexAttribPointer(0, vec, GL_FLOAT, GL_FALSE, vec * sizeof(f), offset);
}

void uniform4(ui prog, const char* str, f x, f y, f z, f w){
  glUseProgram(prog);
  glUniform4f(glGetUniformLocation(prog, str), x, y, z, w);
}

void color(f x, f y, f z, f w){
  glClearColor(x, y, z, w);
  glClear(GL_COLOR_BUFFER_BIT);
}