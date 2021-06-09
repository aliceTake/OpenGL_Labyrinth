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
    int goalPosition[2];
    GLfloat windowAspect;
    GLfloat reverseWindowAspect;
    Size objectSize;
    GLfloat glObjectSize;
    
public:
    ConfigureDefine()
    : mode(0),squareArrayWidth(0),squareArrayHeight(0),windowWidth(0),windowHeight(0),windowAspect(0),reverseWindowAspect(0),objectSize(0,0),glObjectSize(0.0),goalPosition{0,0}{}
    
    ConfigureDefine(int mode, int winWidth, int winHeight)
    : windowWidth(winWidth),windowHeight(winHeight),mode(mode)
    {
        
        switch(this->mode){
            case GAME_MODE_EASY:
                this->squareArrayWidth = 36;
                this->squareArrayHeight = 20;
                this->glObjectSize = 0.2;
                this->goalPosition[0] = 35;
                this->goalPosition[1] = 17;
                break;
            case GAME_MODE_NORMAL:
                this->squareArrayWidth = 54;
                this->squareArrayHeight = 30;
                this->glObjectSize = 0.132;
                this->goalPosition[0] = 53;
                this->goalPosition[1] = 26;
                break;
            case GAME_MODE_HARD:
                this->squareArrayWidth = 72;
                this->squareArrayHeight = 40;
                this->glObjectSize = 0.1;
                this->goalPosition[0] = 71;
                this->goalPosition[1] = 35;
                break;
            default:
                this->squareArrayWidth = 36;
                this->squareArrayHeight = 20;
                this->glObjectSize = 0.2;
                this->goalPosition[0] = 35;
                this->goalPosition[1] = 17;
                break;
        }
    }
    
    void configSetting(){
        sizeCalculateSet();
        setWindowAspect();
    }
    
private:
    void sizeCalculateSet(){
        this->objectSize.width = 2.0 / GLdouble(this->squareArrayWidth);
        this->objectSize.height = 2.0 / GLdouble(this->squareArrayHeight);
    }
    void setWindowAspect(){
        this->windowAspect = GLfloat(this->windowWidth) / GLfloat(this->windowHeight);
        this->reverseWindowAspect = GLfloat(this->windowHeight) / GLfloat(this->windowWidth);
    }
    
};

#endif /* defineStruct_h */
