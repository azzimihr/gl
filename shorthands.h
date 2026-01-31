#pragma once

#include "pch/returns.h"

u32 VAO[2], VBO[2];

struct Vertex {
  i16 x, y;     // half-floats
  u8 r, g, b, a;    // RGBA
      
  Vertex(i16 px, i16 py, u8 pr, u8 pg, u8 pb, u8 pa)
    : x(px), y(py), r(pr), g(pg), b(pb), a(pa) {}
};

template<sz N>
constexpr v<u16> f16pack(const float (&src)[N]) {
    v<u16> result(N);
    for (sz i = 0; i < N; ++i) {
        result[i] = f16(src[i]);
    }
    return result;
}

constexpr v<u16> f16pack(initializer_list<float> src) {
    v<u16> result(src.size());
    for (sz i = 0; i < src.size(); ++i) {
        result[i] = f16(*(src.begin() + i));
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
    return count * [this] {
      switch (type) {
        case SHORT: return 2;
        case HALF: return 2;
        case BYTE: return 1;
        default:   return 4;
      }
    }();
  }
  constexpr u32 normalized() const {
    return (type == BYTE || type == SHORT) ? 1 : 0;
  }
};

template<vap... spec, typename T>
void setup(const v<T>& data, u32 vao, u32 vbo) {
  glBindVertexArray(VAO[vao]);
  glBindBuffer(_VBO, VBO[vbo]);
  glBufferData(_VBO, data.size()*sizeof(T), data.data(), GL_STATIC_DRAW);

  constexpr auto stride = (spec.byteSize() + ...);
  u32 i = 0;
  u64 offset = 0;
  ((glVertexAttribPointer(i, spec.count, spec.type, spec.normalized(), stride, (void*)(offset)),
    glEnableVertexAttribArray(i++),
    offset += spec.byteSize()),
    ...);
  println("{}",offset);
}

static unordered_map<u64, int> loc_cache;
int ul(u32 prog, string_view name) {
    u64 key = (static_cast<u64>(prog) << 32) | hash<string_view>{}(name);
    auto it = loc_cache.find(key);
    if (it != loc_cache.end()) return it->second;
    int loc = glGetUniformLocation(prog, name.data());
    loc_cache[key] = loc;
    return loc;
}

void uni(u32 prog, S s, f32 x)                      { glUniform1f(ul(prog, s), x);          }
void uni(u32 prog, S s, f32 x, f32 y)               { glUniform2f(ul(prog, s), x, y);       }
void uni(u32 prog, S s, f32 x, f32 y, f32 z)        { glUniform3f(ul(prog, s), x, y, z);    }
void uni(u32 prog, S s, f32 x, f32 y, f32 z, f32 w) { glUniform4f(ul(prog, s), x, y, z, w); }
void uni(u32 prog, S s, int x)                      { glUniform1i(ul(prog, s), x);          }
void uni(u32 prog, S s, int x, int y)               { glUniform2i(ul(prog, s), x, y);       }
void uni(u32 prog, S s, int x, int y, int z)        { glUniform3i(ul(prog, s), x, y, z);    }
void uni(u32 prog, S s, int x, int y, int z, int w) { glUniform4i(ul(prog, s), x, y, z, w); }
void uni(u32 prog, S s, u32 x)                      { glUniform1ui(ul(prog, s), x);         }
void uni(u32 prog, S s, u32 x, u32 y)               { glUniform2ui(ul(prog, s), x, y);      }
void uni(u32 prog, S s, u32 x, u32 y, u32 z)        { glUniform3ui(ul(prog, s), x, y, z);   }
void uni(u32 prog, S s, u32 x, u32 y, u32 z, u32 w) { glUniform4ui(ul(prog, s), x, y, z, w);}

void tri(u32 offset, u32 count){
  glDrawArrays(GL_TRIANGLES, offset,count);
}

void color(f32 x, f32 y, f32 z){
  glClearColor(x, y, z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
