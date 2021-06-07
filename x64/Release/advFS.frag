#version 150 core
//#extension GL_ARB_explicit_attrib_location: enable
//in vec2 UV;

in vec2 Flag_uv;
out vec4 fragment;
uniform sampler2D Texture;

//uniform sampler2D myTextureSampler;

void main()
{
    fragment = texture(Texture, Flag_uv).rgba;
//  fragment = vec4(1.0, 0.0, 1.0, 1.0);
//    fragment = texture( myTexturesampler, UV).rgb;
}
