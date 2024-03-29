//
//  Frame.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/20.
//

#ifndef Frame_hpp
#define Frame_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Size {
    GLdouble width, height;
    
public:
    
    Size();
    
    Size(GLdouble width, GLdouble height);
};

struct Position {
public:
    GLdouble x, y;
    
public:
    Position();
    Position(GLdouble xPosi, GLdouble yPosi);
    
    Position operator= (Position p);
    
    Position operator+ (Position p);
};

struct Frame {
public:
    Size size;
    Position position;
    
    Frame(Size s, Position p);
    
    Frame(Size s, GLdouble x, GLdouble y);
    
    Frame(GLdouble width, GLdouble height, Position p);
    
    Frame(GLdouble width, GLdouble height, GLdouble x, GLdouble y);
};

struct Vertex {
    Position lowerLeft, lowerRight, upperRight, upperLeft;
};

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

static const GLfloat vertex_uv1[] =
{
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
    : red(0.0), green(0.0), blue(0.0) {}
};
#endif /* Frame_hpp */
