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
#include <vector>
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
    void stateInit();
    void positionArrayInit();
    // textファイルからマップデータを読み込む
    int mapLoad(const int height, const int width);
    void createpositionArrayVbo(const int height, const int width);
    void createStateData();
    void multipleVertexInit();
    
public:
    MultipleSquare(Frame f, ConfigureDefine conf);
    ConfigureDefine conf;
//    Position positionArray[SQUARE_ARRAY_HEIGHT][SQUARE_ARRAY_WIDTH]; // ここを動的確保にしたい
    Position** positionArray;
//    GLint state[SQUARE_ARRAY_HEIGHT][SQUARE_ARRAY_WIDTH];
    GLfloat** state;
    virtual ~MultipleSquare();

    void floorLoadTexture();
    
    void draw();
    
    Position* getPositionArray(int h, int w);
};


#endif /* MultipleSquare_hpp */
