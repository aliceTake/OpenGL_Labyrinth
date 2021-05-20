//
//  ObjectClass.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#include "Object.hpp"

SquareShape::SquareShape(Frame f, ConfigureDefine conf)
: location { 0.0f, 0.0f }, frame(f.size, f.position), conf{conf}  { vertexInit(); createVbo(); }

SquareShape::SquareShape(GLfloat width, GLfloat height, GLfloat x, GLfloat y)
: location { 0.0f, 0.0f }, frame(width, height, x, y) { vertexInit(); createVbo(); }

SquareShape::SquareShape(Size s, Position p)
: location { 0.0f, 0.0f }, frame(s ,p) { vertexInit(); createVbo(); }

SquareShape::SquareShape(Size s, GLfloat x, GLfloat y)
: location { 0.0f, 0.0f }, frame(s, x, y) { vertexInit(); createVbo(); }

SquareShape::SquareShape(GLfloat width, GLfloat height, Position p)
: location { 0.0f, 0.0f }, frame(width, height, p) { vertexInit(); createVbo(); }


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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    // テクスチャのvbo
    //追加：テクスチャのUV座標を格納するためのVBOを作成
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &uv_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uv), &vertex_uv, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindVertexArray(0);
}

void SquareShape::vertexInit()
{
    vertex.lowerLeft.x  = this->frame.position.x * WINDOW_ASPECT - WINDOW_ASPECT;// 1.78f;
    vertex.lowerLeft.y  = this->frame.position.y;
    
    vertex.lowerRight.x = vertex.lowerLeft.x + this->frame.size.width;
    vertex.lowerRight.y = vertex.lowerLeft.y;
    
    vertex.upperRight.x = vertex.lowerRight.x;
    vertex.upperRight.y = vertex.lowerRight.y + this->frame.size.height;
    
    vertex.upperLeft.x  = vertex.lowerLeft.x;
    vertex.upperLeft.y  = vertex.upperRight.y;
}

const GLfloat* SquareShape::getLocation() const { return location; }




MultipleSquare::MultipleSquare(Frame f, ConfigureDefine conf)
: aspectedWidth( f.size.width * REVERSE_WINDOW_ASPECT), SquareShape(f, conf) {  multipleVertexInit(); createpositionArrayVbo();}

void MultipleSquare::multipleVertexInit()
{
    this->vertex.lowerLeft.x  = 0.0f;
    this->vertex.lowerLeft.y  = this->frame.position.y;
    
    this->vertex.lowerRight.x = vertex.lowerLeft.x + this->frame.size.width;
    this->vertex.lowerRight.y = vertex.lowerLeft.y;
    
    this->vertex.upperRight.x = vertex.lowerRight.x;
    this->vertex.upperRight.y = vertex.lowerRight.y + this->frame.size.height;
    
    this->vertex.upperLeft.x  = vertex.lowerLeft.x;
    this->vertex.upperLeft.y  = vertex.upperRight.y;
    
    this->bindVao();
    this->bindVbo();
    glBufferData(GL_ARRAY_BUFFER, sizeof (Vertex), &vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
}

void MultipleSquare::createpositionArrayVbo() {
    bindVao();
    positionArrayInit();
    
    glEnableVertexAttribArray(2);
    glGenBuffers(1, &positionArrayVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionArrayVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionArray),  &positionArray, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
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
    for (int h = 0; h < SQUARE_ARRAY_HEIGHT; h++){
        for (int w = 0; w < SQUARE_ARRAY_WIDTH; w++){
            this->positionArray[h][w].x = ((2.0f / (WINDOW_HEIGHT / (100 * this->frame.size.width))) * w + this->frame.position.x);
            this->positionArray[h][w].y = (-1.0 + this->frame.size.height / 2 * h);
        }
    }
}
void MultipleSquare::stateInit() {
    for (int h = 0; h < SQUARE_ARRAY_HEIGHT; h++){
        for (int w = 0; w < SQUARE_ARRAY_WIDTH; w++){
            this->state[h][w] = 0.0;
        }
    }
}

void MultipleSquare::createStateData() {
    stateInit();
    for (int h = 0; h < SQUARE_ARRAY_HEIGHT; h++){
        for (int w = 0; w < SQUARE_ARRAY_WIDTH; w++){
            if(h == 5 || h == 8 || w == 16 || (h == 9 && w == 3) || (h == 10 && (w == 0 || w == 1 || w == 2 || w == 3))) {
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


Adv::Adv(Frame f, ConfigureDefine conf) : SquareShape(f,conf) {advPosi.x = 0.0f; advPosi.y = 0.0f;};

void Adv::reloadPosition() {
    const GLfloat width = 2.0f / SQUARE_ARRAY_WIDTH;
    
    advPosi.x = (this->frame.position.x + location[0]);
    for(int j = 0; j < SQUARE_ARRAY_WIDTH; j++) {
        if((width * j) - 1.0f <= advPosi.x && (width * j) - 1.0f + 0.0001f > advPosi.x){
            arrayPosition[0] = j;
            break;
        }
        else if((width * j) - 1.0f + 0.0001f <=  advPosi.x && (width * (j + 1.0f)) - 1.0f > advPosi.x) {
            arrayPosition[0] = -j;
            break;
        }
    }
    
    const GLfloat height = 2.0f / SQUARE_ARRAY_HEIGHT;
    
    advPosi.y = (this->frame.position.y + location[1]) + 0.5f;
    for(int i = 0; i < SQUARE_ARRAY_HEIGHT; i++) {
        if(height * i - 1.0005f <= advPosi.y && height * i - 1.0f >= advPosi.y){
            arrayPosition[1] = i;
            break;
        }
        else if(height * i - 1.0f < advPosi.y && height * (i + 1) - 1.0005f > advPosi.y) {
            arrayPosition[1] = -i;
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
            location[1] += 0.0125f; // 上
            printf("location = %f\n",location[1]);
            break;
        case 1:
            location[1] -= 0.0125f; // 下
            printf("location = %f\n",location[1]);
            break;
        case 2:                        // 左
            location[0] -= 0.0555556f / 8.0f; // location[0] -= 0.1f * REVERSE_WINDOW_ASPECT / 8;
            //                    std::cout << 2.0f / 36.0f << std::endl;
            break;
        case 3:                        // 右
            location[0] += 0.0555556f / 8.0f;
            //                std::cout << location[0] << std::endl;
            break;
        default:
            break;
    }
}

