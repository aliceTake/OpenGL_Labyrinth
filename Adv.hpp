//
//  Adv.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/06/01.
//

#ifndef Adv_hpp
#define Adv_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Frame.hpp"
#include "defineStruct.h"
#include "Texture.hpp"
#include "SquareShape.hpp"

class Adv : public SquareShape {
    
    GLint aspectLoc;
    GLint locationLoc;
    
    void vertexInit();
    void createVbo();
    
public:
    Adv(Frame f, ConfigureDefine conf);
    virtual ~Adv();
    
    ConfigureDefine conf;
    
    int arrayPosition[2] = {0, 0};
    Position advPosi;
    Position** positionArray;
    
    
    void advLoadTexture();
    
    void reloadPosition();
    
    Position* getAdvPosition();
    
    int* getArrayPosition();
    
    // 左右のテクスチャを反転させて使うための関数
    void flipHorizontal(bool flip);
    
    // テクスチャの変更、texでテクスチャの番号を入れる
    void changeTexture(unsigned int count, int tex);
    
    // advを動かす関数
    void move (int direction);
    
    void useProgram();
    
    void set_fLocation();
};


#endif /* Adv_hpp */
