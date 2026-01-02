#pragma once

#include "glad/glad.h"

#include "enum.h"

template<size_t M, size_t... Ns>
void gen(ui (&vao)[M], ui (&...buffers)[Ns]) {
  glGenVertexArrays(M, vao);
  (glGenBuffers(Ns, buffers), ...);
}

template<ui... attrs, size_t N>
void setup(ui vao, ui vbo, float (&data)[N]) {
  glBindVertexArray(VAO[vao]);
  glBindBuffer(VERTEX, VBO[vbo]);
  glBufferData(VERTEX, sizeof(data), data, GL_STATIC_DRAW);

  constexpr auto stride = (attrs + ...) * sizeof(f);
  ui i=0
  ui offset = 0;
  ((glVertexAttribPointer(i, attrs, GL_FLOAT, 0, stride, (void*)(offset * sizeof(f))),
    glEnableVertexAttribArray(i++),
    offset += attrs),
    ...);
}

void uniform4(ui prog, const char* str, f x, f y, f z, f w){
  glUseProgram(prog);
  glUniform4f(glGetUniformLocation(prog, str), x, y, z, w);
}

void tri(ui offset, ui count, ui prog){
  glUseProgram(prog);
  glDrawArrays(GL_TRIANGLES, offset,count);
}

void color(f x, f y, f z){
  glClearColor(x, y, z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
