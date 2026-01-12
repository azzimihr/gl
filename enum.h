#pragma once

#define GLEAB GL_ELEMENT_ARRAY_BUFFER
#define GLAB GL_ARRAY_BUFFER

#define HALF GL_HALF_FLOAT
#define BYTE GL_UNSIGNED_BYTE

#include <vector>
#include <cstdint>
#include <cstdlib>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/packing.hpp>

using namespace std;


typedef float f32;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef size_t sz;
template<typename T> using v = vector<T>;
constexpr auto f16conv = glm::packHalf1x16;
