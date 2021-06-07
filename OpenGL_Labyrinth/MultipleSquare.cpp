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
    createpositionArrayVbo(conf.squareArrayHeight, conf.squareArrayWidth);
    glDeleteProgram(this->program);
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
void MultipleSquare::createpositionArrayVbo(const int height, const int width) {
    bindVao();
    stateInit();
    mapLoad(height, width);
    positionArrayInit();
    
    Position* array = new Position[height * width * 2];
    
    for(int i = 0; i < conf.squareArrayHeight; i++) {
        for(int j = 0; j < conf.squareArrayWidth; j++) {
            array[i * width + j].x = positionArray[i][j].x;
            array[i * width + j].y = positionArray[i][j].y;
        }
    }
    
    GLfloat* stateArray = new GLfloat[height * width * 2];
    
    for(int i = 0; i < conf.squareArrayHeight; i++) {
        for(int j = 0; j < conf.squareArrayWidth; j++) {
            stateArray[i * width + j] = state[i][j];
            stateArray[i * width + j] = state[i][j];
        }
    }
    
    glEnableVertexAttribArray(2);
    glGenBuffers(1, &positionArrayVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionArrayVbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(positionArray),  &positionArray, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Position) * conf.squareArrayHeight * conf.squareArrayWidth,  array, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(3);
    glGenBuffers(1, &statusVbo);
    glBindBuffer(GL_ARRAY_BUFFER, statusVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * conf.squareArrayHeight * conf.squareArrayWidth, stateArray, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 0, 0);
    
    glVertexAttribDivisor(0,0);
    glVertexAttribDivisor(1,0);
    glVertexAttribDivisor(2,1);
    glVertexAttribDivisor(3,1);
    
    glBindVertexArray(0);

    delete[] array;
    delete[] stateArray;
}

void MultipleSquare::positionArrayInit() {
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

// MARK: mapLoad()
int MultipleSquare::mapLoad(const int height, const int width) {
    std::string file;
    if(height == 20){
        file = "easyMap.txt";
    }
    else if(height == 30) {
        file = "nomalMap.txt";
    }
    else if(height == 40) {
        file = "hardMap.txt";
    }
    else file = "easyMap.txt";
    
    std::ifstream ifs(file, std::ios::in);
    if(!ifs){
        std::cout << "ファイルを開けませんでした" << std::endl;
        return -1;
    }
    
    ifs.seekg(0,std::ios_base::beg);
    
    char* data = new char[height * (width + 1) * 2];
    
    for(int h = 0; h < this->conf.squareArrayHeight; h++){
        for(int w = 0; w < this->conf.squareArrayWidth + 1; w++){
            ifs.get(data[h * width + w]);
        }
    }
    
    for(int h = 0; h < this->conf.squareArrayHeight; h++){
        for(int w = 0; w < this->conf.squareArrayWidth; w++){
            if(data[abs(h - (conf.squareArrayHeight - 1)) * conf.squareArrayWidth + w] == '1') {
                this->state[h][w] = 0.0;
            }
            else if(data[abs(h - (conf.squareArrayHeight - 1)) * conf.squareArrayWidth + w] == '0') {
                this->state[h][w] = 1.0;
            }
        }
    }
    
    ifs.close();
    delete[] data;
    
    return 0;
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
    this->loadTexture("floor.bmp", 32, 32, false);
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
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

Position* MultipleSquare::getPositionArray(int h, int w) {
    return &positionArray[h][w];
}

// MARK: デストラクタ
MultipleSquare::~MultipleSquare() {
    glBindVertexArray(0);
    glDeleteBuffers(1, &positionArrayVbo);
    glDeleteBuffers(1, &statusVbo);
    for(int i = 0; i < conf.squareArrayHeight; i++) {
        delete[] this->positionArray[i];
        delete[] this->state[i];
    }
    delete[] this->positionArray;
    delete[] this->state;
}
