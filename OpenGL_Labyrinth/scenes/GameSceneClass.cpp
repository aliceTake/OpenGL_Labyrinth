//
//  gameScemeClass.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#include "GameSceneClass.hpp"

GameScene::GameScene(int mode, int windowWidth, int windowHeight)
{
    
    ConfigureDefine conf(mode, windowWidth, windowHeight);
    conf.configSetting();
    
    floorPointer = new MultipleSquare(Frame(conf.glObjectSize, conf.glObjectSize, -1.0, -1.0),conf);
    
    const GLfloat advFirstPosition = GLfloat(floorPointer->positionArray[1][0].y);
    advPointer = new Adv(Frame(conf.glObjectSize, conf.glObjectSize, -1.0, advFirstPosition),conf);
    
    floorPointer->floorLoadTexture();
    
    advPointer->advLoadTexture();
    
    advPointer->bindTexture(0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    advPointer->positionArray = floorPointer->positionArray;
}

BlockCollision GameScene::hitCheck(){
    advPointer->reloadPosition();
    BlockCollision bc;
//
//    std::cout << advPointer->arrayPosition[1] << " " << advPointer->arrayPosition[0] << std::endl;
    
    // 上判定
    if(advPointer->arrayPosition[1] == floorPointer->conf.squareArrayHeight - 1){
        if(1.0 <= GLfloat(advPointer->advPosi.y) + advPointer->conf.objectSize.height + ERROR_RANGE) {
            bc.up = 1;
        }
    }
    else if(floorPointer->state[advPointer->arrayPosition[1] + 1][advPointer->arrayPosition[0]] == 0.0){
        if(GLfloat(floorPointer->positionArray[advPointer->arrayPosition[1] + 1][advPointer->arrayPosition[0]].y) < GLfloat(advPointer->advPosi.y + advPointer->conf.objectSize.height) + ERROR_RANGE) // 0.01
        {
            bc.up = 1;
        }
    }
    // 右上に頭がつっかえてたら上に行けない
    else {
        if((floorPointer->positionArray[advPointer->arrayPosition[1] + 1][advPointer->arrayPosition[0] + 1].x) < advPointer->advPosi.x + advPointer->conf.objectSize.width - ERROR_RANGE) {
            bc.down_left = 1;
        }
    }
    // 下判定
    // 画面外にはみ出さないようにする
    if(advPointer->arrayPosition[1] == 0){
        if(-1.0 >= GLfloat(advPointer->advPosi.y) - ERROR_RANGE) {
            bc.down = 1;
        }
    }
    // 下にブロックがあったら行けない
    else if(floorPointer->state[advPointer->arrayPosition[1] - 1][advPointer->arrayPosition[0]] == 0.0){
        if((floorPointer->positionArray[advPointer->arrayPosition[1] - 1][advPointer->arrayPosition[0]].y + floorPointer->conf.objectSize.height + ERROR_RANGE)
           > advPointer->advPosi.y)
        {
            bc.down= 1;
        }
    }
    // 左上のブロックに頭がつっかえてたら行けない
    else {
        if((floorPointer->positionArray[advPointer->arrayPosition[1] - 1][advPointer->arrayPosition[0] + 1].x) < advPointer->advPosi.x + advPointer->conf.objectSize.width - ERROR_RANGE) { // 0.001
            bc.down_right = 1;
        }
    }
    // 右判定
    if(advPointer->arrayPosition[0] == floorPointer->conf.squareArrayWidth - 1){
        if(1.0 <= GLfloat(advPointer->advPosi.x) + advPointer->conf.objectSize.width + ERROR_RANGE) {
            bc.right = 1;
        }
    }
    else if(floorPointer->state[advPointer->arrayPosition[1]][advPointer->arrayPosition[0] + 1] == 0.0){
        if(GLfloat(floorPointer->positionArray[advPointer->arrayPosition[1]][advPointer->arrayPosition[0] + 1].x) < GLfloat(advPointer->advPosi.x + advPointer->conf.objectSize.width) + ERROR_RANGE)
        {
            bc.right = 1;
        }
    }
    // 右上のブロックに頭がつっかえてたら右に行けない
    else {
        if((floorPointer->positionArray[advPointer->arrayPosition[1] + 1][advPointer->arrayPosition[0] + 1].y) < advPointer->advPosi.y + advPointer->conf.objectSize.height - ERROR_RANGE) {
            bc.up_right = 1;
        }
    }
    // 左判定
    // 左の画面外に行けないように
    if(advPointer->arrayPosition[0] == 0){
        if(-1.0 >= GLfloat(advPointer->advPosi.x) - ERROR_RANGE) {
            bc.left = 1;
        }
    }
    // 左判定
    else if(floorPointer->state[advPointer->arrayPosition[1]][advPointer->arrayPosition[0] - 1] == 0.0){
        if((floorPointer->positionArray[advPointer->arrayPosition[1]][advPointer->arrayPosition[0] - 1].x + floorPointer->conf.objectSize.width) > GLfloat(advPointer->advPosi.x) - ERROR_RANGE)
        {
            bc.left = 1;
        }
    }
    // 左上のブロックに頭がつっかえてたら左に行けない
    else {
        if((floorPointer->positionArray[advPointer->arrayPosition[1] + 1][advPointer->arrayPosition[0] - 1].y) < GLfloat(advPointer->advPosi.y + advPointer->conf.objectSize.height) - ERROR_RANGE) { // 0.099
            bc.up_left = 1;
        }
    }


    return bc;
}

void GameScene::keyJudgment(GLFWwindow* window) {
    BlockCollision bc = hitCheck();
    advPointer->set_fLocation();
    // キーボードの状態を調べる
    // WとAキー同時押し,左上移動
    if(glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE) {
        if(bc.up == 0 && bc.down_left == 0) advPointer->move(0);
        bc = hitCheck();
        if(bc.left == 0 && bc.up_left == 0) advPointer->move(2);
    }
    // WとDキー同時押し,右上移動
    else if(glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE) {
        if(bc.up == 0 && bc.down_left == 0) advPointer->move(0);
        bc = hitCheck();
        if(bc.right == 0 && bc.up_right == 0) advPointer->move(3);
    }
    // SとAキー同時押し,左下移動
    else if(glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE) {
        if(bc.down == 0 && bc.down_right == 0) advPointer->move(1);
        bc = hitCheck();
        if(bc.left == 0 && bc.up_left == 0) advPointer->move(2);
    }
    // SとDキー同時押し,右下移動
    else if(glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE) {
        if(bc.down == 0 && bc.down_right == 0) advPointer->move(1);
        bc = hitCheck();
        if(bc.right == 0 && bc.up_right == 0) advPointer->move(3);
    }
    // WとSキー同時押しで何もしない
    else if(glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE) {
    }
    // AとDキー同時押しで何もしない
    else if(glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE) {
    }
    // Wキー、上移動
    else if(glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE) {
        if(bc.up == 0 && bc.down_left == 0) advPointer->move(0);
    }
    // Sキー、下移動
    else if(glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE) {
        if(bc.down == 0 && bc.down_right == 0) advPointer->move(1);
    }
    // Aキー、左移動
    else if(glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE) {
        if(bc.left == 0 && bc.up_left == 0) advPointer->move(2);
    }
    // Dキー、右移動
    else if(glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE) {
        if(bc.right == 0 && bc.up_right == 0) advPointer->move(3);
        
    }
}

// ボタンを押したときにテクスチャの変更
void GameScene::textureChangeByKey(GLFWwindow* window, int count){
    if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE) {
        advPointer->changeTexture(count, ADV_BACK_TEXTURE);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE) {
        advPointer->changeTexture(count, ADV_FRONT_TEXTURE);
    }
    else if(glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE) {
        advPointer->flipHorizontal(false);
        advPointer->changeTexture(count, ADV_SIDE_TEXTURE);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE) {
        advPointer->flipHorizontal(true);
        advPointer->changeTexture(count, ADV_SIDE_TEXTURE);
    }
    else {
        advPointer->bindTexture(0);
    }
}

void GameScene::goalChack() {
    if(floorPointer->conf.goalPosition[0] == advPointer->arrayPosition[0] && floorPointer->conf.goalPosition[1] == advPointer->arrayPosition[1])
    {
        goalFrag = true;
    }
}

int GameScene::run(WindowClass* window) {
    unsigned int count = 0;
    
    while (glfwGetKey(window->getWindowInstance(), GLFW_KEY_X) == GLFW_RELEASE && glfwGetKey(window->getWindowInstance(), GLFW_KEY_ESCAPE) == GLFW_RELEASE && this->goalFrag == false) {
        count++;
        count = (11 + count) % 11;
        glClear(GL_COLOR_BUFFER_BIT);
        
        floorPointer->draw();
        
        advPointer->useProgram();
        advPointer->bindVao();
        this->keyJudgment(window->getWindowInstance());
        this->textureChangeByKey(window->getWindowInstance(), count);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
        glUseProgram(0);
        
        window->swapBuffers();
        
        goalChack();
        std::cout << this->goalFrag << std::endl;
    }
    if(this->goalFrag == true){
        return GAME_MODE_START_SCENE;
    }
    return GAME_MODE_START_SCENE;
}

GameScene::~GameScene(){
    delete floorPointer;
    delete advPointer;
    floorPointer = NULL;
    advPointer = NULL;
}
