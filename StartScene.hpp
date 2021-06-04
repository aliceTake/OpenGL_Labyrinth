//
//  StartScene.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/06/03.
//

#ifndef StartScene_hpp
#define StartScene_hpp
#include "WindowClass.hpp"
#include "SquareShape.hpp"

class StartScene {
public:
    int gameMode;
    SquareShape* screen;
    SquareShape* title;
    SquareShape* easyButton;
    SquareShape* nomalButton;
    SquareShape* hardButton;
    
    StartScene();
    
    ~StartScene();
    
    int run(WindowClass* window);
};

#endif /* StartScene_hpp */
