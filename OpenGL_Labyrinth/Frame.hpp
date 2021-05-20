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
    GLfloat width, height;
    
public:
    Size();
    
    Size(GLfloat width, GLfloat height);
};

struct Position {
public:
    GLfloat x, y;
    
public:
    Position();
    Position(GLfloat xPosi, GLfloat yPosi);
    
    Position operator= (Position p);
    
    Position operator+ (Position p);
};

struct Vertex {
    Position lowerLeft, lowerRight, upperRight, upperLeft;
    
    Vertex operator= (Vertex v);
    
    Vertex operator+ (Vertex v);
};

struct Frame {
public:
    Size size;
    Position position;
    
    Frame(Size s, Position p);
    
    Frame(Size s, GLfloat x, GLfloat y);
    
    Frame(GLfloat width, GLfloat height, Position p);
    
    Frame(GLfloat width, GLfloat height, GLfloat x, GLfloat y);
};

#endif /* Frame_hpp */
