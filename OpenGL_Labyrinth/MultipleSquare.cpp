//
//  MultipleSquare.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/06/01.
//

#include "MultipleSquare.hpp"

MultipleSquare::MultipleSquare(Frame f, ConfigureDefine conf)
: aspectedWidth( f.size.width * conf.reverseWindowAspect), conf(conf), SquareShape(f)
{
    vertexInit();
    createVbo();
    
    this->positionArray = new Position*[conf.squareArrayHeight];
    for (int i = 0; i < conf.squareArrayHeight; i++) {
        this->positionArray[i] = new Position[conf.squareArrayWidth];
    }
    
    this->state = new GLfloat*[conf.squareArrayHeight];
    for (int i = 0; i < conf.squareArrayHeight; i++) {
        this->state[i] = new GLfloat[conf.squareArrayWidth];
    }
    
    multipleVertexInit();
    createpositionArrayVbo();
    this->program = loadProgram("point.vert", "point.frag");
    this->aspectLoc = glGetUniformLocation(this->program, "aspect");
}

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
    
    Position array[conf.squareArrayHeight][conf.squareArrayWidth];
    
    for(int i = 0; i < conf.squareArrayHeight; i++) {
        for(int j = 0; j < conf.squareArrayWidth; j++) {
            array[i][j].x = positionArray[i][j].x;
            array[i][j].y = positionArray[i][j].y;
        }
    }
    
    GLfloat stateArray[conf.squareArrayHeight][conf.squareArrayWidth];
    
    for(int i = 0; i < conf.squareArrayHeight; i++) {
        for(int j = 0; j < conf.squareArrayWidth; j++) {
            stateArray[i][j] = state[i][j];
            stateArray[i][j] = state[i][j];
        }
    }
    
    glEnableVertexAttribArray(2);
    glGenBuffers(1, &positionArrayVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionArrayVbo);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(positionArray),  &positionArray, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Position) * conf.squareArrayHeight * conf.squareArrayWidth,  &array[0][0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(3);
    glGenBuffers(1, &statusVbo);
    glBindBuffer(GL_ARRAY_BUFFER, statusVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * conf.squareArrayHeight * conf.squareArrayWidth, &stateArray[0][0], GL_STATIC_DRAW);
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

void MultipleSquare::floorLoadTexture() {
    this->loadTexture("floor.bmp", false);
    this->setTextureLocation(this->program);
    this->bindTexture(0);
}

void MultipleSquare::draw() {
    glUseProgram(this->program);
    // uniform変数に値を設定する
    glUniform1f(this->aspectLoc, conf.windowAspect);
    bindVao();
    bindTexture(0);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, conf.squareArrayWidth * conf.squareArrayHeight);
    glBindVertexArray(0);
    glUseProgram(0);
}

MultipleSquare::~MultipleSquare() {
    glDeleteBuffers(1, &positionArrayVbo);
    glDeleteBuffers(1, &statusVbo);
}

Position* MultipleSquare::getPositionArray(int h, int w) {
    return &positionArray[h][w];
}
