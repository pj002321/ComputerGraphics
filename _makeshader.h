#pragma once
#include "filetobuf.h"

void makeVertexShader();
void makeFragmentShader();
void makeShaderID();
GLuint fragmentShader;
GLuint vertexID;
GLuint shaderID;


char* vertexSource;
char* fragmentSource;


void makeVertexShader()
{
	vertexSource = filetobuf("VertexTextureShader.glsl");
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexSource, NULL);
	glCompileShader(vertexID);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexID, 512, NULL, errorLog);
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

	glAttachShader(shaderID, vertexID);
	glAttachShader(shaderID, fragmentShader);

	glLinkProgram(shaderID);
	GLint result;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	GLchar errorLog[512];
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		cerr << "ShaderID0 Program ERROR: " << errorLog << endl;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentShader);
	glUseProgram(shaderID);
}
using namespace std;



