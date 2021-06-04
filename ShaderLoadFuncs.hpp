//
//  ShaderLoadFuncs.hpp
//  OpenGL_Labyrinth
//
//  Created by take on 2021/05/19.
//

#ifndef ShaderLoadFuncs_hpp
#define ShaderLoadFuncs_hpp


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "macro.h"

// MARK: GLFWInit
bool myGLFWInit();


// MARK: log関連
// シェーダオブジェクトのコンパイル結果を表示する
//   shader: シェーダオブジェクト名
//   str: コンパイルエラーが発生した場所を示す文字列
GLboolean printShaderInfoLog(GLuint shader, const char *str);

// プログラムオブジェクトのリンク結果を表示する
//   program: プログラムオブジェクト名
GLboolean printProgramInfoLog(GLuint program);

// MARK: プログラムオブジェクト生成
// プログラムオブジェクトを作成する
//   vsrc: バーテックスシェーダのソースプログラムの文字列
//   fsrc: フラグメントシェーダのソースプログラムの文字列
GLuint createProgram(const char *vsrc, const char *fsrc);

// MARK: シェーダー読み込み関連
// シェーダのソースファイルを読み込む
//   name: シェーダのソースファイル名
//   buffer: 読み込んだソースファイルのテキスト
bool readShaderSource(const char *name, std::vector<GLchar> &buffer);

// シェーダのソースファイルを読み込んでプログラムオブジェクトを作成する
//   vert: バーテックスシェーダのソースファイル名
//   frag: フラグメントシェーダのソースファイル名
GLuint loadProgram(const char *vert, const char *frag);

#endif /* ShaderLoadFuncs_hpp */
