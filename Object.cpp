//
//  ObjectClass.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#include "Object.hpp"

SquareShape::SquareShape(Frame f)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, frame(f.size, f.position)  {}

SquareShape::SquareShape(GLdouble width, GLdouble height, GLdouble x, GLdouble y)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, frame(width, height, x, y) {}

SquareShape::SquareShape(Size s, Position p)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, frame(s ,p) {}

SquareShape::SquareShape(Size s, GLdouble x, GLdouble y)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, frame(s, x, y) {}

SquareShape::SquareShape(GLdouble width, GLdouble height, Position p)
: location { 0.0, 0.0 }, fLocation { 0.0, 0.0 }, alpha{0.0, 0.0, 0.0, 0.0}, frame(width, height, p) {}

void SquareShape::createSquare(){
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uv), &vertex_uv, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
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
        
        bindVao();
        
        glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
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

const GLfloat* SquareShape::getLocation() const
{
    return fLocation;
}

MultipleSquare::MultipleSquare(Frame f, ConfigureDefine conf)
: aspectedWidth( f.size.width * conf.reverseWindowAspect), conf(conf), SquareShape(f) { vertexInit(); createVbo(); multipleVertexInit(); createpositionArrayVbo();}

void MultipleSquare::vertexInit()
{
    
    vertex.lowerLeft.x  = this->frame.position.x * conf.windowAspect - conf.windowAspect; // WINDOW_ASPECT
    vertex.lowerLeft.y  = this->frame.position.y * 2;
    
    vertex.lowerRight.x = vertex.lowerLeft.x + this->frame.size.width;
    vertex.lowerRight.y = vertex.lowerLeft.y;
    
    vertex.upperRight.x = vertex.lowerRight.x;
    vertex.upperRight.y = vertex.lowerRight.y + this->frame.size.height;
    
    vertex.upperLeft.x  = vertex.lowerLeft.x;
    vertex.upperLeft.y  = vertex.upperRight.y;
}

void MultipleSquare::createVbo() {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uv), &vertex_uv, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindVertexArray(0);
}

void MultipleSquare::multipleVertexInit()
{
    this->vertex.lowerLeft.x  = 0.0;//this->frame.position.x;//this->frame.position.x;// 0.0;
    this->vertex.lowerLeft.y  = 0.0;//this->frame.position.y;
    
    this->vertex.lowerRight.x = vertex.lowerLeft.x + this->frame.size.width;
    this->vertex.lowerRight.y = vertex.lowerLeft.y;
    
    this->vertex.upperRight.x = vertex.lowerRight.x;
    this->vertex.upperRight.y = vertex.lowerRight.y + this->frame.size.height;
    
    this->vertex.upperLeft.x  = vertex.lowerLeft.x;
    this->vertex.upperLeft.y  = vertex.upperRight.y;
    
    this->bindVao();
    this->bindVbo();
    glBufferData(GL_ARRAY_BUFFER, sizeof (Vertex), &vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, 0);
    
}

void MultipleSquare::createpositionArrayVbo() {
    bindVao();
    positionArrayInit();
    
    glEnableVertexAttribArray(2);
    glGenBuffers(1, &positionArrayVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionArrayVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionArray),  &positionArray, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(3);
    glGenBuffers(1, &statusVbo);
    glBindBuffer(GL_ARRAY_BUFFER, statusVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(state), state[0], GL_STATIC_DRAW);
    glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 0, 0);
    
    glVertexAttribDivisor(0,0);
    glVertexAttribDivisor(1,0);
    glVertexAttribDivisor(2,1);
    glVertexAttribDivisor(3,1);
    
    glBindVertexArray(0);
}

void MultipleSquare::positionArrayInit() {
    createStateData();
    for (int h = 0; h < conf.squareArrayHeight; h++){
        for (int w = 0; w < conf.squareArrayWidth; w++){
            this->positionArray[h][w].x = this->frame.position.x + conf.objectSize.width  * w;
            this->positionArray[h][w].y = this->frame.position.y + conf.objectSize.height * h;
        }
    }
}


void MultipleSquare::stateInit() {
    for (int h = 0; h < conf.squareArrayHeight; h++){
        for (int w = 0; w < conf.squareArrayWidth; w++){
            this->state[h][w] = 0.0;
        }
    }
}

void MultipleSquare::createStateData() {
    stateInit();
    for (int h = 0; h < conf.squareArrayHeight; h++){
        for (int w = 0; w < conf.squareArrayWidth; w++){
            if(h == 5 || h == 8 || w == 16 || h == 0 || w == 32 || (h == 9 && w == 3) || (h == 10 && (w == 0 || w == 1 || w == 2 || w == 3))) {
                this->state[h][w] = 1.0;
            }
            if(h == 5 && w == 30) {
                this->state[h][w] = 0.0;
            }
        }
    }
}

Position* MultipleSquare::getPositionArray(int h, int w) {
    return &positionArray[h][w];
}


Adv::Adv(Frame f, ConfigureDefine conf) : SquareShape(f) ,conf(conf) { vertexInit(); createVbo(); advPosi.x = 0.0; advPosi.y = 0.0;};



void Adv::vertexInit()
{
    
    vertex.lowerLeft.x  = this->frame.position.x * conf.windowAspect - conf.windowAspect; // WINDOW_ASPECT
    vertex.lowerLeft.y  = this->frame.position.y * 2;
    
    vertex.lowerRight.x = vertex.lowerLeft.x + this->frame.size.width;
    vertex.lowerRight.y = vertex.lowerLeft.y;
    
    vertex.upperRight.x = vertex.lowerRight.x;
    vertex.upperRight.y = vertex.lowerRight.y + this->frame.size.height;
    
    vertex.upperLeft.x  = vertex.lowerLeft.x;
    vertex.upperLeft.y  = vertex.upperRight.y;
}

void Adv::createVbo() {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uv), &vertex_uv, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindVertexArray(0);
}

void Adv::reloadPosition() {
    advPosi.x = (this->frame.position.x + location[0]);
    
    for(int j = 0; j < conf.squareArrayWidth; j++) {
        if(j == conf.squareArrayWidth - 1){
            arrayPosition[0] = j;
            break;
        }
        else if(GLfloat(this->positionArray[j].x) - ERROR_RANGE <= GLfloat(advPosi.x) && GLfloat(this->positionArray[(j + 1)].x) > GLfloat(advPosi.x) + ERROR_RANGE){ // 0.001
            arrayPosition[0] = j;
            break;
        }
    }
    
    advPosi.y = (this->frame.position.y + GLfloat(location[1]));
    
    for(int i = 0; i < conf.squareArrayHeight; i++) {
        if(i == conf.squareArrayHeight - 1){
            arrayPosition[1] = i;
            break;
        }
        else if(GLfloat(this->positionArray[i * conf.squareArrayWidth].y) <= GLfloat(advPosi.y) + ERROR_RANGE && (GLfloat(this->positionArray[(i + 1) * conf.squareArrayWidth].y)) > GLfloat(advPosi.y) + ERROR_RANGE){ // 0.01
            arrayPosition[1] = i;
            break;
        }
    }
}

Position* Adv::getAdvPosition() {
    reloadPosition();
    return &advPosi;
}

int* Adv::getArrayPosition() {
    reloadPosition();
    return arrayPosition;
}

void Adv::flipHorizontal(bool flip) {
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    if (flip) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (char *)0 + sizeof(GLfloat) * 8);
    }
    else {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }
}

void Adv::changeTexture(unsigned int count, int tex)
{
    if(tex == ADV_SIDE_TEXTURE){
        if(count <= 4){
            bindTexture(2);
        } else if (count <= 7){
            bindTexture(1);
        } else {
            bindTexture(3);
        }
    }
    else if(tex == ADV_FRONT_TEXTURE) {
        if(count <= 4){
            bindTexture(4);
        } else if (count <= 7){
            bindTexture(5);
        } else {
            bindTexture(0);
        }
    }
    else if(tex == ADV_BACK_TEXTURE) {
        if(count <= 4){
            bindTexture(6);
        } else if (count <= 7){
            bindTexture(7);
        } else {
            bindTexture(8);
        }
    }
}

void Adv::move (int direction) {
    switch (direction) {
        case 0:
            location[1] += conf.objectSize.height / 8.0; // 上
            break;
        case 1:
            location[1] -= conf.objectSize.height / 8.0; // 下
            break;
        case 2:
            location[0] -= conf.objectSize.width / 8.0; // 左
            break;
        case 3:
            location[0] += conf.objectSize.width / 8.0; // 右
            break;
        default:
            break;
    }
}

void Adv::set_fLocation(){
    this->fLocation[0] = this->location[0];
    this->fLocation[1] = this->location[1];
}
