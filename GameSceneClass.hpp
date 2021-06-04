//
//  gameScemeClass.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#ifndef GameSceneClass_hpp
#define GameSceneClass_hpp

#include "macro.h"
#include "ObjectHeaderMacro.h"
#include "WindowClass.hpp"
#include "defineStruct.h"

class GameScene {
    Adv* advPointer;
    MultipleSquare* floorPointer;
    //    Position* positionArray;
    
public:
    GameScene(int mode, int windowWidth, int windowHeight);
    virtual ~GameScene();
    
    void createPlayer();
    
    BlockCollision hitCheck();
    
    void keyJudgment(GLFWwindow* window);
    
    void textureChangeByKey(GLFWwindow* window, int count);
    
    void run(WindowClass* window);
};

#endif /* GameSceneClass_hpp */
