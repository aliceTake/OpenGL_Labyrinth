//
//  gameScemeClass.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#ifndef GameScemeClass_hpp
#define GameScemeClass_hpp

#include "macro.h"
#include "ObjectHeaderMacro.h"
#include "WindowClass.hpp"
#include "defineStruct.h"

class GameScene {
    Adv* advPointer;
    MultipleSquare* floorPointer;
    //    Position* positionArray;
    
public:
    GameScene();
    virtual ~GameScene();
    
    void createPlayer();
    
    BlockCollision hitCheck();
    
    void keyJudgment(GLFWwindow* window);
    
    void textureChangeByKey(GLFWwindow* window, int count);
    
    void run(WindowClass* window);
};

#endif /* GameScemeClass_hpp */
