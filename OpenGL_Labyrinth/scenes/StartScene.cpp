//
//  StartScene.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/06/03.
//

#include "StartScene.hpp"

StartScene::StartScene() {
    
    program = loadProgram("shaders/object.vert", "shaders/object.frag");
    screenProgram = loadProgram("shaders/object.vert", "shaders/noTexture.frag");
    
    const GLfloat screenSize = 2.0;
    
    screen = new SquareShape(Frame(screenSize, screenSize, -1.0, -1.0));
    screen->createSquare();
    screen->setShaderProgram(screenProgram);
    screen->changeColor(0.0, 0.0, 0.0);
    screen->changeAlpha(0.0);

    const GLfloat titleHeght = (screenSize / 8.0) * 3.0;
    title = new SquareShape(Frame(screenSize, titleHeght, -1.0, 0.25));
    title->createSquare();
    title->loadTexture("texture/startSceneTexture/title.bmp", 800, 300, true);
    title->setTextureLocation(program);
    title->setBindTexture(true);
    title->changeAlpha(1.0);
    const GLfloat buttonWidth = screenSize / 2.0;
    const GLfloat buttonHeight = screenSize / 16.0;
    const GLfloat buttonX = -1.0 + screenSize / 4.0;

    GLfloat buttonY = -1.0 + screenSize - titleHeght - 0.1; // 3/4

    easyButton = new SquareShape(Frame(buttonWidth, buttonHeight, buttonX, buttonY));
    easyButton->createSquare();
    easyButton->loadTexture("texture/startSceneTexture/easy.bmp", 800, 67, true);
    easyButton->setTextureLocation(program);
    easyButton->setBindTexture(true);
    easyButton->changeAlpha(1.0);
    easyButton->changeColor(1.0, 1.0, 1.0);
    buttonY = ((buttonY + 1.0) / 3.0);

    nomalButton = new SquareShape(Frame(buttonWidth, buttonHeight, buttonX, buttonY * 2.0 - 1.0));
    nomalButton->createSquare();
    nomalButton->loadTexture("texture/startSceneTexture/nomal.bmp", 800, 67, true);
    nomalButton->setTextureLocation(program);
    nomalButton->setBindTexture(true);
    nomalButton->changeAlpha(1.0);
    nomalButton->changeColor(1.0, 1.0, 1.0);

    hardButton = new SquareShape(Frame(buttonWidth, buttonHeight, buttonX, buttonY - 1.0));
    hardButton->createSquare();
    hardButton->loadTexture("texture/startSceneTexture/hard.bmp", 800, 67, true);
    hardButton->setTextureLocation(program);
    hardButton->setBindTexture(true);
    hardButton->changeAlpha(1.0);
    hardButton->changeColor(1.0, 1.0, 1.0);

    key = new SquareShape(Frame(0.08, 0.1422, 0.1, easyButton->frame.position.y - 0.01));
    key->createSquare();
    key->loadTexture("texture/startSceneTexture/key.bmp", 32, 32, true);
    key->setTextureLocation(program);
    key->setBindTexture(true);
    key->changeAlpha(1.0);
    key->changeColor(1.0, 1.0, 1.0);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
}

int StartScene::run(WindowClass* window) {
    
    SquareShape button(Frame(1.0, 0.25, -0.5, 0.25));
    button.createSquare();
    
    int buttonFrag = -1;
    double x,y;
    Position mousePosi;
    
    while (glfwGetKey(window->getWindowInstance(), GLFW_KEY_ESCAPE) != GLFW_RELEASE || buttonFrag == -1) {
        glClear(GL_COLOR_BUFFER_BIT);
        screen->draw();
        title->draw();
        easyButton->draw();
        nomalButton->draw();
        hardButton->draw();
        key->draw();
        
        if(glfwGetMouseButton(window->getWindowInstance(), GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE) {
            glfwGetCursorPos(window->getWindowInstance(), &x, &y);
            mousePosi.x = static_cast<GLfloat>(x) * 2.0f / WINDOW_WIDTH - 1.0f;
            mousePosi.y = 1.0f - static_cast<GLfloat>(y) * 2.0f / WINDOW_HEIGHT;
            buttonFrag = GAME_MODE_EASY;
            if(mousePosi.x > easyButton->frame.position.x && mousePosi.x < easyButton->frame.position.x + easyButton->frame.size.width &&
               mousePosi.y > easyButton->frame.position.y && mousePosi.y < easyButton->frame.position.y + easyButton->frame.size.height)
            {
                buttonFrag = GAME_MODE_EASY;
            }
            else if(mousePosi.x > nomalButton->frame.position.x && mousePosi.x < nomalButton->frame.position.x + nomalButton->frame.size.width &&
                    mousePosi.y > nomalButton->frame.position.y && mousePosi.y < nomalButton->frame.position.y + nomalButton->frame.size.height)
            {
                buttonFrag = GAME_MODE_NORMAL;
            }
            else if(mousePosi.x > hardButton->frame.position.x && mousePosi.x < hardButton->frame.position.x + hardButton->frame.size.width &&
                    mousePosi.y > hardButton->frame.position.y && mousePosi.y < hardButton->frame.position.y + hardButton->frame.size.height)
            {
                buttonFrag = GAME_MODE_HARD;
            }
        }
        
        glfwSwapBuffers(window->getWindowInstance());
        glfwPollEvents();
    }
    return buttonFrag;
}

StartScene::~StartScene() {
    delete screen;
    screen = NULL;
    delete title;
    title = NULL;
    delete easyButton;
    easyButton = NULL;
    delete nomalButton;
    nomalButton = NULL;
    delete hardButton;
    hardButton = NULL;
    delete key;
    key = NULL;
    glDeleteProgram(this->program);
    this->program = NULL;
    glDeleteProgram(this->screenProgram);
    this->screen = NULL;
}
