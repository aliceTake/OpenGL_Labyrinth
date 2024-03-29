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
    
    void vertexInit();
    void createVbo();
    void bindVbo();
    
public:
    Vertex vertex;
    Frame frame;
    
    SquareShape(Frame f);
    
    SquareShape(GLdouble width, GLdouble height, GLdouble x, GLdouble y);
    
    SquareShape(Size s, Position p);
    
    SquareShape(Size s, GLdouble x, GLdouble y);
    
    SquareShape(GLdouble width, GLdouble height, Position p);
    
    virtual ~SquareShape();
    
    void setShaderProgram(GLuint program);
    
    void bindVao();
    
    void createSquare();
    
    void setBindTexture(bool set);
    
    void changePosition(GLfloat x, GLfloat y);
    void changePosition(Position p);
    
    void changeColor(GLfloat red, GLfloat green, GLfloat blue);
    
    void changeAlpha(GLfloat alpha);
    
    void draw();
    
    const GLfloat *getLocation() const;
};


#endif /* SquareShape_hpp */
