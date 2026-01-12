#pragma once

#include "returns.h"

#include <cstddef>
#include <initializer_list>

u32 VAO[2], VBO[2];

struct Vertex {
  u16 x, y;     // half-floats
  u8 r, g, b, a;    // RGBA
      
  Vertex(f32 px, f32 py, u8 pr, u8 pg, u8 pb, u8 pa)
    : x(f16conv(px)), y(f16conv(py)), r(pr), g(pg), b(pb), a(pa) {}
};

template<sz N>
constexpr v<u16> f16pack(const float (&src)[N]) {
    v<u16> result(N);
    for (sz i = 0; i < N; ++i) {
        result[i] = f16conv(src[i]);
    }
    return result;
}

constexpr v<u16> f16pack(initializer_list<float> src) {
    v<u16> result(src.size());
    for (sz i = 0; i < src.size(); ++i) {
        result[i] = f16conv(*(src.begin() + i));
    }
    return result;
}

template<sz M, sz... Ns>
void gen(u32 (&vao)[M], u32 (&...buffers)[Ns]) {
  glGenVertexArrays(M, vao);
  (glGenBuffers(Ns, buffers), ...);
}

struct vap {
  u32 count;
  u32 type;
  
  constexpr u32 byteSize() const {
    return count * (type == HALF ? 2 : 
                    type == BYTE ? 1 :
                    4);
  }
  
  constexpr u32 isNormalized() const {
    return type == BYTE ? 1 : 0;
  }
};

template<vap... spec, typename T>
void setup(const v<T>& data, u32 vao, u32 vbo) {
  glBindVertexArray(VAO[vao]);
  glBindBuffer(GLAB, VBO[vbo]);
  glBufferData(GLAB, data.size()*sizeof(T), data.data(), GL_STATIC_DRAW);

  constexpr auto stride = (spec.byteSize() + ...);
  u32 i = 0;
  u64 offset = 0;
  ((glVertexAttribPointer(i, spec.count, spec.type, spec.isNormalized(), stride, (void*)(offset)),
    glEnableVertexAttribArray(i++),
    offset += spec.byteSize()),
    ...);
  println("{}",offset);
}

void uni4(u32 prog, const char* str, f32 x, f32 y, f32 z, f32 w){
  glUseProgram(prog);
  glUniform4f(glGetUniformLocation(prog, str), x, y, z, w);
}

void tri(u32 offset, u32 count){
  glDrawArrays(GL_TRIANGLES, offset,count);
}

void color(f32 x, f32 y, f32 z){
  glClearColor(x, y, z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
