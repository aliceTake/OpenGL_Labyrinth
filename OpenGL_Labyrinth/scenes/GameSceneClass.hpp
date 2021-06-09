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
    bool goalFrag = false;
    
public:
    GameScene(int mode, int windowWidth, int windowHeight);
    virtual ~GameScene();
    
    void createPlayer();
    
    BlockCollision hitCheck();
    
    void keyJudgment(GLFWwindow* window);
    
    void textureChangeByKey(GLFWwindow* window, int count);
    
    void goalChack();
    
    int run(WindowClass* window);
};

#endif /* GameSceneClass_hpp */
