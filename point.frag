#version 150 core
//#extension GL_ARB_explicit_attrib_location: enable
//in vec2 UV;

in vec2 Flag_uv;
in vec4 Al;
out vec4 fragment;
uniform sampler2D Texture;

//uniform sampler2D myTextureSampler;

void main()
{
    fragment = texture(Texture, Flag_uv).rgba - Al;
}
