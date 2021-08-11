//
//  TextureClass.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderLoadFuncs.hpp"
#include "Frame.hpp"

class Texture {
private:
    std::vector<GLuint> textureID;
public:
    
    ~Texture();
    
    const GLuint getTexID(int texNum) const;
    
    void loadTexture(std::string filename, GLfloat width, GLfloat height, bool isAlpha);
    
    void setTextureLocation(GLuint program);
    
    void bindTexture(int texNum);
};

#endif /* Texture_hpp */
