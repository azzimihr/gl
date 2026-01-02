#pragma once

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

f vertices[18] = {
  // first triangle
  -0.9f, -0.5f, 0.0f, //color not here...
  -0.0f, -0.5f, 0.0f,
  -0.45f, 0.5f, 0.0f,

   0.0f, -0.5f, 0.0f,
   0.9f, -0.5f, 0.0f,
   0.45f, 0.5f, 0.0f
};

f vertices2[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};  

ui indices[] = {
  0, 1, 3,
  1, 2, 3
};