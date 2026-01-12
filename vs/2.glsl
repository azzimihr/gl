R"(
#version 330 core

layout(location = 0) in vec2 aPos;   // positions
layout(location = 1) in vec4 aColor; // colors

out vec3 fragColor;  // pass to fragment shader

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);  // raw clip-space positions
    fragColor = aColor.xyz;
}
)"