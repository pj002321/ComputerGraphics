#include "stdafx.h"

void Resize(int w, int h)
{
    glViewport(0, 0, FRAME_WIDTH, FRAME_HEIGHT);
    w = FRAME_WIDTH;
    w = FRAME_HEIGHT;
}

char* filetobuf(const string name)
{
	vector<char> tempFile;
	ifstream in(name, ios::binary);
	char temp;
	while (true) {
		noskipws(in);
		in >> temp;
		if (in.eof()) {
			tempFile.push_back(0);
			break;
		}
		else
			tempFile.push_back(temp);
	}
	char* addr = new char[tempFile.size()];
	for (int i = 0; i < tempFile.size(); i++) {
		addr[i] = tempFile[i];
	}
	return addr;
}

void makeShader(const char* vertexFilePath, const char* fragmentFilePath, GLuint& shaderProgram) {
    // ���ؽ� ���̴� �ε�, ������, ��ũ
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = filetobuf(vertexFilePath);
    glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(vertexShaderID);

    GLint vResult;
    GLchar vErrorLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vResult);
    if (!vResult) {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, vErrorLog);
        cerr << "VERTEXSHADER ERROR: " << vErrorLog << endl;
    }

    // �����׸�Ʈ ���̴� �ε�, ������, ��ũ
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = filetobuf(fragmentFilePath);
    glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShaderID);

    GLint fResult;
    GLchar fErrorLog[512];
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fResult);
    if (!fResult) {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, fErrorLog);
        cerr << "FRAGMENT SHADER ERROR: " << fErrorLog << endl;
    }

    // ���̴� ���α׷� ����
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderID);
    glAttachShader(shaderProgram, fragmentShaderID);
    glLinkProgram(shaderProgram);

    // ���̴� ���α׷� ��ũ Ȯ��
    GLint linkResult;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkResult);
    GLchar linkErrorLog[512];
    if (!linkResult) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, linkErrorLog);
        cerr << "Shader Program Link ERROR: " << linkErrorLog << endl;
    }

    // ���� ���̴� ��ü ����
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    // ������ ���̴� ���α׷� ���
    glUseProgram(shaderProgram);
}
