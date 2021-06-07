#include "ShaderLoadFuncs.hpp"
#include "WindowClass.hpp"
#include "StartScene.hpp"
#include "GameSceneClass.hpp"
#include <cstdlib>

using namespace std;

int main()
{
    if(!myGLFWInit()) {
        return 1;
    }
    
    WindowClass window;
    
    int gameMode = 0;
    
    StartScene* startScene;
    GameScene* gameScene;
    
    // MARK: メインループ
    // 背景色を指定する
    glClearColor(0.5f, 0.7f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // ウィンドウが開いている間繰り返す
    while (window.shouldClose() == GL_FALSE)
    {
        startScene = new StartScene;
        gameMode = startScene->run(&window);
        delete startScene;
        
        gameScene = new GameScene(gameMode, WINDOW_WIDTH, WINDOW_HEIGHT);
        gameScene->run(&window);
        delete gameScene;
        
        cout << "true" << endl;
    }
}

