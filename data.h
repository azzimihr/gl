#pragma once

#include "shorthands.h"

S vs1 =
#include "vs/1.glsl"
;S vs2 =
#include "vs/2.glsl"
;S fs1 =
#include "fs/1.glsl"
;S fs2 =
#include "fs/2.glsl"
;S fs3 =
#include "fs/3.glsl"
;

auto vertices = f16pack({
  // first triangle
  -0.9f, -0.5f,  //color not here...
  -0.0f, -0.5f, 
  -0.45f, 0.5f, 
   0.5f, -0.5f, 
   -0.5f, -1.0f,
   0.0f,  0.5f, 
});

const v<Vertex> vertices2 = {
    {16384, -16384,   255, 0, 0,255},      // bottom right - red
    {-16384,-16384,   0, 255, 0,255},     // bottom left - green
    {0,      16384,   0, 0, 255,255}        // top - blue
};

u32 indices[] = {
  0, 1, 3,
  1, 2, 3
};
