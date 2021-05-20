//#version 150 core
////#extension GL_ARB_explicit_attrib_location: enable
//
//out vec4 fragment;
//
//void main()
//{
//  fragment = vec4(1.0, 0.0, 1.0, 1.0);
//}


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
//    if (Al == 1){
//        fragment = vec4(texture(Texture, Flag_uv).rgb, 0.0);
//    }
//    else if (Al == 0) {
//        fragment = vec4(texture(Texture, Flag_uv).rgb, 1.0);
//    }
//  fragment = vec4(1.0, 0.0, 1.0, 1.0);
//    fragment = texture( myTexturesampler, UV).rgb;
}
