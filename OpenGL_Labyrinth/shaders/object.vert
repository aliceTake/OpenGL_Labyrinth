#version 150 core
#extension GL_ARB_explicit_attrib_location: enable
uniform float aspect;
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 vuv;
layout (location = 2) in vec3 color;
layout (location = 3) in float isAlpha;
out vec2 Flag_uv;
out float Al;
out vec3 color_frag;


void main()
{
    Flag_uv = vuv;
    Al = isAlpha;
    color_frag = color;
    
    gl_Position = position;
}
