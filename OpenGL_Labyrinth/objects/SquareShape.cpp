//
//  SquareShape.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/06/01.
//

#include "SquareShape.hpp"


SquareShape::SquareShape(Frame f)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, texureBindFrag(false) , frame(f.size, f.position)  { this->program = loadProgram("shaders/object.vert", "shaders/object.frag");}

SquareShape::SquareShape(GLdouble width, GLdouble height, GLdouble x, GLdouble y)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, texureBindFrag(false), frame(width, height, x, y) { this->program = loadProgram("shaders/object.vert", "shaders/object.frag"); }

SquareShape::SquareShape(Size s, Position p)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, texureBindFrag(false), frame(s ,p) { this->program = loadProgram("shaders/object.vert", "shaders/object.frag"); }

SquareShape::SquareShape(Size s, GLdouble x, GLdouble y)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, texureBindFrag(false), frame(s, x, y) { this->program = loadProgram("shaders/object.vert", "shaders/object.frag"); }

SquareShape::SquareShape(GLdouble width, GLdouble height, Position p)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, texureBindFrag(false), frame(width, height, p) { this->program = loadProgram("shaders/object.vert", "shaders/object.frag"); }

SquareShape::~SquareShape() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glDisableVertexAttribArray(0);
    std::cout << &vbo << std::endl;
    glDeleteBuffers(1, &vbo);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &uv_vbo);
    glDisableVertexAttribArray(2);
    glDeleteBuffers(1, &colorVbo);
    glDisableVertexAttribArray(3);
    glDeleteBuffers(1, &alphaVbo);
    glDeleteProgram(this->program);
//    glDeleteVertexArrays(1, &vao);
}

void SquareShape::setShaderProgram(GLuint program) {
    glDeleteProgram(this->program);
    this->program = NULL;
    this->program = program;
}

void SquareShape::createSquare() {
    vertexInit();
    createVbo();
}

void SquareShape::bindVao() {
    glBindVertexArray(vao);
}

void SquareShape::bindVbo() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void SquareShape::createVbo() {
    
    glGenVertexArrays(1, &vao);
    bindVao();
    
    glGenBuffers(1, &vbo);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof (Vertex), &vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, 0);
    
    // テクスチャのvbo
    //追加：テクスチャのUV座標を格納するためのVBOを作成
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &uv_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uv1), &vertex_uv1, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);//(char *)0 + sizeof(GLfloat) * 8);
    
    glEnableVertexAttribArray(2);
    glGenBuffers(1, &colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(3);
    glGenBuffers(1, &alphaVbo);
    glBindBuffer(GL_ARRAY_BUFFER, alphaVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(alpha), alpha, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindVertexArray(0);
}

void SquareShape::vertexInit()
{
    vertex.lowerLeft.x  = this->frame.position.x; // WINDOW_ASPECT
    vertex.lowerLeft.y  = this->frame.position.y;
    
    vertex.lowerRight.x = vertex.lowerLeft.x + this->frame.size.width;
    vertex.lowerRight.y = vertex.lowerLeft.y;
    
    vertex.upperRight.x = vertex.lowerRight.x;
    vertex.upperRight.y = vertex.lowerRight.y + this->frame.size.height;
    
    vertex.upperLeft.x  = vertex.lowerLeft.x;
    vertex.upperLeft.y  = vertex.upperRight.y;
}

void SquareShape::changeColor(GLfloat red, GLfloat green, GLfloat blue) {
    for(int i = 0; i < 4; i++){
        color[i].red = red;
        color[i].green = green;
        color[i].blue = blue;
    }
    bindVao();
    
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void SquareShape::changeAlpha(GLfloat alpha) {
    this->alpha[0] = 1.0 - alpha;
    this->alpha[1] = 1.0 - alpha;
    this->alpha[2] = 1.0 - alpha;
    this->alpha[3] = 1.0 - alpha;
    
    bindVao();
    
    glBindBuffer(GL_ARRAY_BUFFER, alphaVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->alpha), this->alpha, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, 0);
}

void SquareShape::setBindTexture(bool set) {
    this->texureBindFrag = set;
}

void SquareShape::draw() {
    glUseProgram(this->program);
    if(this->texureBindFrag) this->bindTexture(0);
    else glBindTexture(GL_TEXTURE_2D, 0);
//    glBindTexture(GL_TEXTURE_2D, 0);
    bindVao();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

const GLfloat* SquareShape::getLocation() const
{
    return fLocation;
}
