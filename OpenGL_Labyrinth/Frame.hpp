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

struct Vertex {
    Position lowerLeft, lowerRight, upperRight, upperLeft;
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

#endif /* Frame_hpp */
