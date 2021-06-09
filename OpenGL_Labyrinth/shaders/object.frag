#version 150 core
//#extension GL_ARB_explicit_attrib_location: enable
//in vec2 UV;

in vec2 Flag_uv;
in float Al;
in vec3 color_frag;
out vec4 fragment;
uniform sampler2D Texture;

//uniform sampler2D myTextureSampler;

void main()
{
    if(texture(Texture, Flag_uv).a == 0.0){
        fragment = vec4(color_frag, Al);// + vec4(0.0,0.0,0.0,Al);
    }
    else {
        fragment = texture(Texture, Flag_uv).rgba;
//        fragment = texture(Texture, Flag_uv).rgba + vec4(color_frag, 0.0) - Al;
    }
}
