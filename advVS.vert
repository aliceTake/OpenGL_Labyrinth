<<<<<<< HEAD
﻿#version 150 core
=======
#version 150 core
>>>>>>> origin/testBranch
#extension GL_ARB_explicit_attrib_location: enable
uniform float aspect;
uniform vec2 location;
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 vuv;
out vec2 Flag_uv;
//layout(location = 2) in vec2 vertexUV;

//out vec2 UV;

//uniform mat4 MVP;

void main()
{
    Flag_uv = vuv;
//    vec2 a = 2.0 * scale / size;
//    gl_Position = vec4(2.0 * scale / size, 1.0, 1.0) * position;
//    gl_Position = vec4(((2.0 * scale / size) * position.xy) +  posi.xy , position.z + posi.z, 1.0) + vec4(location, 0.0, 0.0);
//    gl_Position =  vec4(a, 1.0, 1.0) * (position + vec4(posi, 1.0)) + vec4(location, 0.0, 0.0);
//    gl_Position =  vec4(position.xyz + posi, 1.0f);
//    position = vec4(1.0 / aspect, 1.0, 1.0, 1.0) * position;
    
    gl_Position = vec4(1.0 / aspect / 2.0 ,1.0 / 2.0, 1.0, 1.0) * position + vec4(location, 0.0, 0.0);//vec4(1.0 / aspect,1.0, 1.0, 1.0) *
    

}
