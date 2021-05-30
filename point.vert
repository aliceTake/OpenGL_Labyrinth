#version 150 core
#extension GL_ARB_explicit_attrib_location: enable
uniform float aspect;
layout (location = 0) in vec4 position;
layout (location = 2) in vec3 posi;
layout (location = 1) in vec2 vuv;
layout (location = 3) in float isAlpha;
out vec2 Flag_uv;
out vec4 Al;


void main()
{
    Flag_uv = vuv;
    Al = vec4(0.0, 0.0, 0.0, isAlpha);

//    gl_Position = vec4(1.0 / aspect,1.0, 1.0, 1.0) * position + vec4(posi.x - aspect, posi.y, posi.z, 1.0); //+ vec4(location, 0.0, 0.0);//vec4(1.0 / aspect,1.0, 1.0, 1.0) *
//    gl_Position = vec4(1.0 / aspect,1.0, 1.0, 1.0) * position + vec4(vec3(posi.x * 2.0 - (1.0 / aspect), posi.y, posi.z), 1.0);
    gl_Position = vec4(1.0 / aspect ,1.0, 1.0, 1.0) * vec4(position.x, position.y, position.z, position.w) + vec4(vec3(posi.x * 2.0, posi.y * 2.0, posi.z), 1.0);
}
