//
//  gameScemeClass.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#ifndef GameScemeClass_hpp
#define GameScemeClass_hpp

#include "macro.h"
#include "Object.hpp"
#include "defineStruct.h"

class GameScene {
    Adv* advPointer;
    MultipleSquare* floorPointer;
    //    Position* positionArray;
    
public:
    GameScene(Adv* adv, MultipleSquare* floor);
    
    void createPlayer();
    
    BlockCollision hitCheck();
    
    void keyJudgment(GLFWwindow* window);
    
    void textureChangeByKey(GLFWwindow* window, int count);
};

#endif /* GameScemeClass_hpp */
