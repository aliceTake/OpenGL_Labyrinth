//
//  ObjectClass.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#ifndef Object_hpp
#define Object_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Frame.hpp"
#include "defineStruct.h"
#include "Texture.hpp"

static const GLfloat vertex_uv[] =
{
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
    
};

struct BlockCollision {
    int right = 0, left = 0, up = 0, down = 0;
    int up_right = 0, up_left = 0, down_right = 0, down_left = 0;
};

struct Color {
    GLfloat red, green, blue;
    
    Color()
    : red(1.0), green(1.0), blue(1.0) {}
};

class SquareShape : public Texture {
protected:
    GLuint vao;
    GLuint vbo;
    GLuint uv_vbo;
    GLuint colorVbo;
    GLuint alphaVbo;
    GLdouble location[2];
    GLfloat fLocation[2];
    Color color[4];
    
public:
    Vertex vertex; // publicなのでゲッターセッターを作る、作ったらこのコメント消す
    Frame frame;   // publicなのでゲッターセッターを作る、作ったらこのコメント消す
    
    GLfloat alpha;
    
    SquareShape(Frame f);
    
    SquareShape(GLdouble width, GLdouble height, GLdouble x, GLdouble y);
    
    SquareShape(Size s, Position p);
    
    SquareShape(Size s, GLdouble x, GLdouble y);
    
    SquareShape(GLdouble width, GLdouble height, Position p);
    
    void createSquare();
    
    void bindVao();
    
    void bindVbo();
    
    void createVbo();
    
    void vertexInit();
    
    void changeColor(GLfloat red, GLfloat green, GLfloat blue);
    
    void changeAlpha(GLfloat alpha);
    
    const GLfloat *getLocation() const;
};

class MultipleSquare : public SquareShape {
private:
    GLuint positionArrayVbo;
    GLfloat aspectedWidth;
    GLuint statusVbo;
    
    void createVbo();
    void vertexInit();
    
public:
    MultipleSquare(Frame f, ConfigureDefine conf);
    ConfigureDefine conf;
    Position positionArray[SQUARE_ARRAY_HEIGHT][SQUARE_ARRAY_WIDTH]; // ここを動的確保にしたい
    GLint state[SQUARE_ARRAY_HEIGHT][SQUARE_ARRAY_WIDTH];

    
    void multipleVertexInit();
    
    void createpositionArrayVbo();
    
    void positionArrayInit();
    
    void stateInit();
    
    void createStateData();
    
    Position* getPositionArray(int h, int w);
};


class Adv : public SquareShape {
    
    void vertexInit();
    
    void createVbo();
    
public:
    Adv(Frame f, ConfigureDefine conf);
    
    ConfigureDefine conf;
    
    int arrayPosition[2] = {0, 0};
    Position advPosi;
    Position* positionArray;
    
    void reloadPosition();
    
    Position* getAdvPosition();
    
    int* getArrayPosition();
    
    // 左右のテクスチャを反転させて使うための関数
    void flipHorizontal(bool flip);
    
    // テクスチャの変更、texでテクスチャの番号を入れる
    void changeTexture(unsigned int count, int tex);
    
    // advを動かす関数
    void move (int direction);
    
    void set_fLocation();
};


#endif /* Object_hpp */
