#pragma once
#include "Dependencies/glew.h"
#include "Dependencies/freeglut.h"
#include "Dependencies/freeglut_ext.h"
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/ext.hpp"
#include "Dependencies/glm/ext/matrix_transform.hpp"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include<mmsystem.h>    
#include<Windows.h>
#include<string>
#include<vector>
#include<random>
#include<math.h>
#include<fstream>
#include<time.h>
using namespace std;

#pragma comment(lib,"Dependencies/glew32.lib")
#pragma comment(lib,"winmm.lib")

#define FRAME_WIDTH 800
#define FRAME_HEIGHT 600

char* filetobuf(const string name);
void makeShader(const char* vertexFilePath, const char* fragmentFilePath, GLuint& shaderProgram);
void Resize(int w, int h);



#define _CRT_SECURE_NO_WARNINGS