#version 150 core
//#extension GL_ARB_explicit_attrib_location: enable
//in vec2 UV;

in float Al;
in vec3 color_frag;
out vec4 fragment;

//uniform sampler2D myTextureSampler;

void main()
{
    fragment = vec4(color_frag, Al);
}
