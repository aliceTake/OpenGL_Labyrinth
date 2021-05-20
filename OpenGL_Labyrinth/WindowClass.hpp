//
//  Window.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#ifndef WindowClass_hpp
#define WindowClass_hpp

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "macro.h"

class WindowClass{
    // ウィンドウハンドル
    GLFWwindow *const window;
    
    // 縦横比
    GLfloat aspect;
    GLfloat haspect;
    
    // キーボードの状態
    int keyStatus;
public:
    // コンストラクタ
    WindowClass(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, const char *title = "Hello!");
    
    // デストラクタ
    virtual ~WindowClass();
    
    // ウィンドウを閉じるか判定する
    int shouldClose() const;
    
    // カラー・バッファを入れ替えてイベントを取り出す
    void swapBuffers();
    
    static void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
    
    // 縦横比を取り出す
    GLfloat getAspect() const;
    GLfloat gethAspect() const;
    GLFWwindow* getWindowInstance() const;
    int getKeyStatus();
};

#endif /* WindowClass_hpp */
