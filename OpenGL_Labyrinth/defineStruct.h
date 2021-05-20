//
//  defineStruct.h
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#ifndef defineStruct_h
#define defineStruct_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "macro.h"
#include "Frame.hpp"

struct ConfigureDefine{
    int mode;
    int squareArrayWidth;
    int squareArrayHeight;
    int windowWidth;
    int windowHeight;
    GLfloat windowAspect;
    GLfloat reverseWindowAspect;
    Size objectSize;
    
public:
    ConfigureDefine()
    : mode(0),squareArrayWidth(0),squareArrayHeight(0),windowWidth(0),windowHeight(0),windowAspect(0),reverseWindowAspect(0),objectSize(0,0){}
    
    ConfigureDefine(int mode, int winWidth, int winHeight)
    : windowWidth(winWidth),windowHeight(winHeight),mode(mode)
    {
        if(this->mode == GAME_MODE_EASY)
        {
            this->squareArrayHeight = 20;
            this->squareArrayWidth = 36;
        }
    }
    
    void configSetting(){
        sizeCalculateSet();
        setWindowAspect();
    }
    
private:
    void sizeCalculateSet(){
        this->objectSize.width = 2.0f / GLfloat(this->squareArrayWidth);
        this->objectSize.height = 2.0f / GLfloat(this->squareArrayHeight);
    }
    void setWindowAspect(){
        this->windowAspect = GLfloat(this->windowWidth) / GLfloat(this->windowHeight);
        this->reverseWindowAspect = GLfloat(this->windowHeight) / GLfloat(this->windowWidth);
    }
    
};

#endif /* defineStruct_h */
