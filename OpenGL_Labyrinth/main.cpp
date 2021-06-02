#include "ShaderLoadFuncs.hpp"
#include "WindowClass.hpp"
#include "GameSceneClass.hpp"

using namespace std;

int main()
{
    if(!myGLFWInit()) {
        return 1;
    }
    
    WindowClass window;
    
    GameScene gameScene(GAME_MODE_EASY, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // MARK: メインループ
    // 背景色を指定する
    glClearColor(0.5f, 0.7f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // ウィンドウが開いている間繰り返す
    while (window.shouldClose() == GL_FALSE)
    {
        gameScene.run(&window);
    }
}

