#pragma once

#include "shorthands.h"

const char *vs1 =
#include "vs/1.glsl"
;const char *vs2 =
#include "vs/2.glsl"
;const char *fs1 =
#include "fs/1.glsl"
;const char *fs2 =
#include "fs/2.glsl"
;const char *fs3 =
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
    {0.5f, -0.5f,   255, 0, 0,255},      // bottom right - red
    {-0.5f,-0.5f,   0, 255, 0,255},     // bottom left - green
    {0.0f,  0.5f,   0, 0, 255,255}        // top - blue
};

u32 indices[] = {
  0, 1, 3,
  1, 2, 3
};
