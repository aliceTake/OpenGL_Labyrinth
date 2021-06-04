//
//  SquareShape.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/06/01.
//

#ifndef SquareShape_hpp
#define SquareShape_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Frame.hpp"
#include "defineStruct.h"
#include "Texture.hpp"

class SquareShape : public Texture {
protected:
    GLuint vao;
    GLuint vbo;
    GLuint uv_vbo;
    GLuint colorVbo;
    GLuint alphaVbo;
    bool texureBindFrag = false;
    GLdouble location[2];
    GLfloat fLocation[2];
    Color color[4];
    GLfloat alpha[4];
    GLuint program;
    
public:
    Vertex vertex; // publicなのでゲッターセッターを作る、作ったらこのコメント消す
    Frame frame;   // publicなのでゲッターセッターを作る、作ったらこのコメント消す
    
    SquareShape(Frame f);
    
    SquareShape(GLdouble width, GLdouble height, GLdouble x, GLdouble y);
    
    SquareShape(Size s, Position p);
    
    SquareShape(Size s, GLdouble x, GLdouble y);
    
    SquareShape(GLdouble width, GLdouble height, Position p);
    
    virtual ~SquareShape();
    
    void setShaderProgram(GLuint program);
    
    void createSquare();
    
    void bindVao();
    
    void bindVbo();
    
    void createVbo();
    
    void vertexInit();
    
    void setBindTexture(bool set);
    
    void changeColor(GLfloat red, GLfloat green, GLfloat blue);
    
    void changeAlpha(GLfloat alpha);
    
    void draw();
    
    const GLfloat *getLocation() const;
};


#endif /* SquareShape_hpp */
