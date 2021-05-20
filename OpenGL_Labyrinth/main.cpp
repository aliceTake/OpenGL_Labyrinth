#include "ShaderLoadFuncs.hpp"
#include "WindowClass.hpp"
#include "GameScemeClass.hpp"
#include "Object.hpp"

int main()
{
    if(!myGLFWInit()) {
        return 1;
    }
    
    WindowClass window;
    
    // プログラムオブジェクトを作成する
    const GLuint program(loadProgram("point.vert", "point.frag"));
    const GLuint advProgram(loadProgram("advVS.vert", "advFS.frag"));
    
    ConfigureDefine conf(GAME_MODE_EASY, WINDOW_WIDTH, WINDOW_HEIGHT);
    conf.configSetting();
    
    Adv* player = new Adv(Frame(0.2f, 0.2f, -1.0f, -1.0f),conf);
    MultipleSquare* floor = new MultipleSquare(Frame(0.2f, 0.2f, -1.0f, -1.0f),conf);
    
    floor->loadTexture("floor.bmp", false);
    floor->setTextureLocation(program);
    floor->bindTexture(0);
    
    // uniform変数の場所を取得する
    const GLint aspectLoc(glGetUniformLocation(program, "aspect"));
    const GLint aspectLoc1(glGetUniformLocation(advProgram, "aspect"));
    const GLint locationLoc(glGetUniformLocation(advProgram, "location"));
    
    player->loadTexture("adv.bmp", true);
    player->loadTexture("adv1.bmp", true);
    player->loadTexture("adv2.bmp", true);
    player->loadTexture("adv3.bmp", true);
    player->loadTexture("adv4.bmp", true);
    player->loadTexture("adv5.bmp", true);
    player->loadTexture("adv6.bmp", true);
    player->loadTexture("adv7.bmp", true);
    player->loadTexture("adv8.bmp", true);
    player->setTextureLocation(advProgram);
    
    
    player->bindTexture(0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    unsigned int count = 0;
    
    GameScene gameScene(player, floor);
    
    
    // MARK: メインループ
    // 背景色を指定する
    glClearColor(0.5f, 0.7f, 0.5f, 0.0f);
    // ウィンドウが開いている間繰り返す
    while (window.shouldClose() == GL_FALSE)
    {
        count++;
        count = (11 + count) % 11;
        
        // ウィンドウを消去する
        glClear(GL_COLOR_BUFFER_BIT);
        
        // シェーダプログラムの使用開始
        glUseProgram(program);
        
        // uniform変数に値を設定する
        glUniform1f(aspectLoc, window.getAspect());
        
        floor->bindVao();
        floor->bindTexture(0);
        glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, SQUARE_ARRAY_WIDTH * SQUARE_ARRAY_HEIGHT);
        glBindVertexArray(0);
        glUseProgram(0);
        
        glUseProgram(advProgram);
        glUniform1f(aspectLoc1, window.getAspect());
        glUniform2fv(locationLoc, 1, player->getLocation());
        player->bindVao();
        
        gameScene.keyJudgment(window.getWindowInstance());
        gameScene.textureChangeByKey(window.getWindowInstance(), count);
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(0);
        glUseProgram(0);

        std::cout << player->arrayPosition[0] << player->arrayPosition[1] << std::endl;
        // カラーバッファを入れ替える
        window.swapBuffers();
    }
}

