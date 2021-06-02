//
//  StartScene.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/06/03.
//

#include "StartScene.hpp"

StartScene::StartScene() {
    
}

void StartScene::run(WindowClass* window) {
    
    SquareShape screen(Frame(2.0, 2.0, -1.0, -1.0));
    screen.createSquare();
    screen.changeColor(0.8, 0.7, 0.8);
    
    SquareShape button(Frame(1.0, 0.2, -0.5, 0.0));
    button.createSquare();
    
    int buttonFrag = 0;
    double x,y;
    Position mousePosi;
    
    while (glfwGetKey(window->getWindowInstance(), GLFW_KEY_ESCAPE) != GLFW_RELEASE || buttonFrag == 0) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        screen.draw();
        button.draw();
        
        if(glfwGetMouseButton(window->getWindowInstance(), GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE) {
            glfwGetCursorPos(window->getWindowInstance(), &x, &y);
            mousePosi.x = static_cast<GLfloat>(x) * 2.0f / WINDOW_WIDTH - 1.0f;
            mousePosi.y = 1.0f - static_cast<GLfloat>(y) * 2.0f / WINDOW_HEIGHT;
            if(mousePosi.x > -0.5 && mousePosi.x < 0.5 && mousePosi.y > 0.0 && mousePosi.y < 0.2){
                buttonFrag = 1;
            }
        }
        
        glfwSwapBuffers(window->getWindowInstance());
        glfwPollEvents();
    }
}
