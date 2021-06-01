//
//  MultipleSquare.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/06/01.
//

#ifndef MultipleSquare_hpp
#define MultipleSquare_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Frame.hpp"
#include "defineStruct.h"
#include "Texture.hpp"
#include "SquareShape.hpp"

class MultipleSquare : public SquareShape {
private:
    GLuint positionArrayVbo;
    GLfloat aspectedWidth;
    GLuint statusVbo;
    GLint aspectLoc;
    
    void createVbo();
    void vertexInit();
    
public:
    MultipleSquare(Frame f, ConfigureDefine conf);
    ConfigureDefine conf;
    Position positionArray[SQUARE_ARRAY_HEIGHT][SQUARE_ARRAY_WIDTH]; // ここを動的確保にしたい
    GLint state[SQUARE_ARRAY_HEIGHT][SQUARE_ARRAY_WIDTH];
    
    virtual ~MultipleSquare();

    void floorLoadTexture();
    
    void multipleVertexInit();
    
    void createpositionArrayVbo();
    
    void positionArrayInit();
    
    void stateInit();
    
    void createStateData();
    
    void draw();
    
    Position* getPositionArray(int h, int w);
};


#endif /* MultipleSquare_hpp */
