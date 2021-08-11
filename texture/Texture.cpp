//
//  TextureClass.cpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#include "Texture.hpp"

const GLuint Texture::getTexID(int texNum) const { return textureID[texNum]; }
    
void Texture::loadTexture(std::string filename, GLfloat width, GLfloat height, bool isAlpha){
        GLuint texID;
        // テクスチャIDの生成
        glGenTextures(1, &texID);

        // ファイルの読み込み
        std::ifstream fstr(filename, std::ios::binary);
        const size_t fileSize = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
        fstr.seekg(138, fstr.beg); // 138
        char* textureBuffer = new char[fileSize];
        fstr.read(textureBuffer, fileSize);

        // テクスチャをGPUに転送
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glBindTexture(GL_TEXTURE_2D, texID);
        //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 32, 32, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
        if(isAlpha == true) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureBuffer);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, textureBuffer);
        }


        // テクスチャを拡大縮小する時のフィルタリング方法を指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        //ラッピング方法を指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // テクスチャのアンバインド
        delete[] textureBuffer;
        glBindTexture(GL_TEXTURE_2D, 0);
        
        textureID.push_back(texID);
}
    
void Texture::setTextureLocation(GLuint program) {
        int textureLocation = glGetUniformLocation(program, "texture");
        glUniform1i(textureLocation, 0);
    }
    
void Texture::bindTexture(int texNum) {
    glBindTexture(GL_TEXTURE_2D, textureID[texNum]);
}

Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    for(int i = 0; i < textureID.size(); i++){
//        bindTexture(i);
        glDeleteTextures(1, &textureID[i]);
    }
}
