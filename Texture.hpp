//
//  TextureClass.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#ifndef Texture_hpp
#define Texture_hpp


#include "ShaderLoadFuncs.hpp"

class Texture {
private:
    std::vector<GLuint> textureID;
public:
    
    const GLuint getTexID(int texNum) const;
    
    void loadTexture(std::string filename, bool isAlpha);
    
    void setTextureLocation(GLuint program);
    
    void bindTexture(int texNum);
};

#endif /* Texture_hpp */
