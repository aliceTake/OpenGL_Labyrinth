
#include "WindowClass.hpp"

// コンストラクタ
WindowClass::WindowClass(int width, int height , const char *title)
: window(glfwCreateWindow(width, height, title, NULL, NULL))
, keyStatus(GLFW_RELEASE)
{
    if (window == NULL)
    {
        // ウィンドウが作成できなかった
        std::cerr << "Can't create GLFW window." << std::endl;
        exit(1);
    }
    
    glfwMakeContextCurrent(window);
    
    // GLEWの初期化
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        // GLEW初期化失敗
        std::cerr << "Can't initialize GLEW" << std::endl;
        exit(1);
    }
    
    // 垂直同期のタイミングを待つ
    glfwSwapInterval(1);
    
    this->aspect = GLfloat(WINDOW_WIDTH) / GLfloat(WINDOW_HEIGHT);
    this->haspect = GLfloat(WINDOW_HEIGHT) / GLfloat(WINDOW_WIDTH);
    
    // キーボード操作時に呼び出す処理の登録
    glfwSetKeyCallback(window, keyboard);
    
    // このインスタンスのthisポインタを記録しておく
    glfwSetWindowUserPointer(window, this);
    
    
    glViewport(0, 0, width, height);
    // 図形の正規化デバイス座標系上での位置の初期化
}

// デストラクタ
WindowClass::~WindowClass()
{
    glfwDestroyWindow(window);
}

// ウィンドウを閉じるか判定する
int WindowClass::shouldClose() const
{
    return glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE);
}

// カラー・バッファを入れ替えてイベントを取り出す
void WindowClass::swapBuffers()
{
    // カラーバッファを入れ替える
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void WindowClass::keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    
    WindowClass *const instance(static_cast<WindowClass *>(glfwGetWindowUserPointer(window)));
    
    if (instance != NULL) {
        // キーの状態を保存する
        instance->keyStatus = action;
    }
}

// 縦横比を取り出す
GLfloat WindowClass::getAspect() const { return aspect; }
GLfloat WindowClass::gethAspect() const { return haspect; }
GLFWwindow* WindowClass::getWindowInstance() const { return window; }
int WindowClass::getKeyStatus(){ return keyStatus; }
