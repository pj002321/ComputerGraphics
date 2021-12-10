#pragma once
#include<glew.h>
#include<freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<iostream>
#include<vector>
#include<random>
#include<math.h>
#include<fstream>
#include<string>
#include "filetobuf.h"

void makeVertexShader();
void makeFragmentShader();
void makeShaderID();
GLuint fragmentShader;
GLuint modelvertexShader;
GLuint shaderID;


char* vertexSource;
char* fragmentSource;


void makeVertexShader()
{
	vertexSource = filetobuf("VertexTextureShader.glsl");
	modelvertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(modelvertexShader, 1, &vertexSource, NULL);
	glCompileShader(modelvertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(modelvertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(modelvertexShader, 512, NULL, errorLog);
		cerr << "VERTEXSHADER ERROR: " << errorLog << endl;
	}
}

void makeFragmentShader()
{
	fragmentSource = filetobuf("fragmentBlendShader.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "FRAGMENT SHADER ERROR: " << errorLog << endl;
	}
}

void makeShaderID()
{
	makeVertexShader();
	makeFragmentShader();

	shaderID = glCreateProgram();

	glAttachShader(shaderID, modelvertexShader);
	glAttachShader(shaderID, fragmentShader);

	glLinkProgram(shaderID);
	GLint result;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	GLchar errorLog[512];
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		cerr << "ShaderID0 Program ERROR: " << errorLog << endl;
	}

	glDeleteShader(modelvertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(shaderID);
}
using namespace std;



