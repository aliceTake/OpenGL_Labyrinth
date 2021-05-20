//
//  gameScemeClass.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#include "GameScemeClass.hpp"


GameScene::GameScene(Adv* adv, MultipleSquare* floor)
: advPointer(adv), floorPointer(floor) {}



BlockCollision GameScene::hitCheck(){
    advPointer->reloadPosition();
    BlockCollision bc;
    // 上判定
    if(floorPointer->state[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0])] == 0.0){
        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0])].y - 0.11f) <= advPointer->advPosi.y)
        {
            bc.up = 1;
        }
    }
    else {
        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0]) + 1].x) < advPointer->advPosi.x + advPointer->conf.objectSize.width) {
            bc.down_left = 1;
        }
    }
    // 下判定
    if(floorPointer->state[abs(advPointer->arrayPosition[1]) - 1][abs(advPointer->arrayPosition[0])] == 0.0){
        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) - 1 <= 0 ? 0 : abs(advPointer->arrayPosition[1]) - 1][abs(advPointer->arrayPosition[0])].y + 0.11)
           > advPointer->advPosi.y)
        {
            bc.down= 1;
        }
    }
    else {
        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) - 1][abs(advPointer->arrayPosition[0]) + 1].x + 0.04f) < advPointer->advPosi.x + WIDTH_OBJECT) {
            bc.down_right = 1;
            printf("true");
        }
    }
    // 右判定
    if(floorPointer->state[abs(advPointer->arrayPosition[1])][abs(advPointer->arrayPosition[0]) + 1] == 0.0){
        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1])][abs(advPointer->arrayPosition[0]) + 1].x)
           > advPointer->advPosi.x)
        {
            bc.right = 1;
        }
    }
    // 右上のブロックに頭がつっかえてたら右に行けない
    else {
        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0]) + 1].y) < advPointer->advPosi.y + 0.099f) {
            bc.up_right = 1;
        }
    }
    // 左判定
    if(floorPointer->state[abs(advPointer->arrayPosition[1])][abs(advPointer->arrayPosition[0]) - 1] == 0.0){
        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1])][abs(advPointer->arrayPosition[0]) - 1].x + WIDTH_OBJECT)
           < advPointer->advPosi.x)
        {
            bc.left = 1;
        }
    }
    // 左上のブロックに頭がつっかえてたら左に行けない
    else {
        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0]) - 1].y) < advPointer->advPosi.y + 0.099f) {
            bc.up_left = 1;
        }
    }


    return bc;
}

//
//BlockCollision GameScene::hitCheck(){
//    advPointer->reloadPosition();
//    BlockCollision bc;
//    // 上判定
//    if(floorPointer->state[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0])] == 0.0){
//        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0])].y - 0.11f) <= advPointer->advPosi.y)
//        {
//            bc.up = 1;
//        }
//    }
//    else {
//        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0]) + 1].x + 0.000004f) < advPointer->advPosi.x + WIDTH_OBJECT) {
//            bc.down_left = 1;
//        }
//    }
//    // 下判定
//    if(floorPointer->state[abs(advPointer->arrayPosition[1]) - 1][abs(advPointer->arrayPosition[0])] == 0.0){
//        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) - 1 <= 0 ? 0 : abs(advPointer->arrayPosition[1]) - 1][abs(advPointer->arrayPosition[0])].y + 0.11)
//           > advPointer->advPosi.y)
//        {
//            bc.down= 1;
//        }
//    }
//    else {
//        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) - 1][abs(advPointer->arrayPosition[0]) + 1].x + 0.000004f) < advPointer->advPosi.x + WIDTH_OBJECT) {
//            bc.down_right = 1;
//            printf("true");
//        }
//    }
//    // 右判定
//    if(floorPointer->state[abs(advPointer->arrayPosition[1])][abs(advPointer->arrayPosition[0]) + 1] == 0.0){
//        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1])][abs(advPointer->arrayPosition[0]) + 1].x)
//           > advPointer->advPosi.x)
//        {
//            bc.right = 1;
//        }
//    }
//    // 右上のブロックに頭がつっかえてたら右に行けない
//    else {
//        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0]) + 1].y) < advPointer->advPosi.y + 0.099f) {
//            bc.up_right = 1;
//        }
//    }
//    // 左判定
//    if(floorPointer->state[abs(advPointer->arrayPosition[1])][abs(advPointer->arrayPosition[0]) - 1] == 0.0){
//        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1])][abs(advPointer->arrayPosition[0]) - 1].x + WIDTH_OBJECT)
//           < advPointer->advPosi.x)
//        {
//            bc.left = 1;
//        }
//    }
//    // 左上のブロックに頭がつっかえてたら左に行けない
//    else {
//        if((floorPointer->positionArray[abs(advPointer->arrayPosition[1]) + 1][abs(advPointer->arrayPosition[0]) - 1].y) < advPointer->advPosi.y + 0.099f) {
//            bc.up_left = 1;
//        }
//    }
//
//
//    return bc;
//}

void GameScene::keyJudgment(GLFWwindow* window) {
    BlockCollision bc = hitCheck();
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
