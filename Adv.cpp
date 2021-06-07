//
//  Adv.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/06/01.
//

#include "Adv.hpp"

Adv::Adv(Frame f, ConfigureDefine conf) : SquareShape(f) ,conf(conf)
{
    vertexInit();
    createVbo();
    advPosi.x = 0.0;
    advPosi.y = 0.0;
    this->program = loadProgram("advVS.vert", "advFS.frag");
    this->aspectLoc = glGetUniformLocation(this->program, "aspect");
    this->locationLoc = glGetUniformLocation(this->program, "location");
};



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

void Adv::advLoadTexture() {
    this->loadTexture("advTexture/adv.bmp", 32, 32, true);
    this->loadTexture("advTexture/adv1.bmp", 32, 32, true);
    this->loadTexture("advTexture/adv2.bmp", 32, 32, true);
    this->loadTexture("advTexture/adv3.bmp", 32, 32, true);
    this->loadTexture("advTexture/adv4.bmp", 32, 32, true);
    this->loadTexture("advTexture/adv5.bmp", 32, 32, true);
    this->loadTexture("advTexture/adv6.bmp", 32, 32, true);
    this->loadTexture("advTexture/adv7.bmp", 32, 32, true);
    this->loadTexture("advTexture/adv8.bmp", 32, 32, true);
    this->setTextureLocation(this->program);
}

void Adv::reloadPosition() {
    advPosi.x = (this->frame.position.x + location[0]);
    
    for(int j = 0; j < conf.squareArrayWidth; j++) {
        if(j == conf.squareArrayWidth - 1){
            arrayPosition[0] = j;
            break;
        }
        else if(GLfloat(this->positionArray[0][j].x) - ERROR_RANGE <= GLfloat(advPosi.x) && GLfloat(this->positionArray[0][j + 1].x) > GLfloat(advPosi.x) + ERROR_RANGE){ // 0.001
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
        else if(GLfloat(this->positionArray[i][0].y) <= GLfloat(advPosi.y) + ERROR_RANGE && (GLfloat(this->positionArray[i + 1][0].y) > GLfloat(advPosi.y) + ERROR_RANGE)){ // 0.01
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

void Adv::useProgram() {
    glUseProgram(this->program);
    glUniform1f(this->aspectLoc, conf.windowAspect);
    glUniform2fv(this->locationLoc, 1, this->getLocation());
}

void Adv::set_fLocation(){
    this->fLocation[0] = this->location[0];
    this->fLocation[1] = this->location[1];
}

Adv::~Adv() {
    
}
