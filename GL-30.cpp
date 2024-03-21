#include"stdafx.h"
#include"readTriangleObj.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
char v_path[64] = "Shader/VertexTextureShader.glsl";
char f_path[64] = "Shader/FragmentTextureShader.glsl";

//shader func
void InitBuffer();
void initTexture();

//call_back
void timer(int value);
void DrawSceneCall();
void keyboardCall(unsigned char key, int x, int y);


//func
void makeObj();
void drawtexture();

GLuint ShaderID;

int Wwidth;
int Wheight;

GLuint VAO[4];
GLuint VBO[12];

vector<glm::vec4> Vertex[3];
vector<glm::vec4> Nomal[3];
vector<glm::vec2> Texture[3];

unsigned int texture[4];
unsigned int pyramidtexture;
float angle = 0.0f;
float cameraRevolu = 0.0f;
float lightRevoluAngle = 0.0f;
bool change = false;
bool Rotate = true;
bool checkjpg = false;

glm::vec3 cameraPos = glm::vec3(3.0f, 3.0f, 8.0f);
glm::vec3 lightPos = glm::vec3(0, 3.0f, 2.5f);
glm::vec3 lightColor = glm::vec3(0.7f, 0.7f, 0.7f);

glm::vec3 lightColorKind[4] = {
	glm::vec3(0.7f, 0.7f, 0.7f),
	glm::vec3(1,0,0),
	glm::vec3(0,1,0),
	glm::vec3(0,0,1)
};
int selectLightColor = 0;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(FRMAE_WIDTH, FRMAE_HEIGHT);
	glutCreateWindow("texture example");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cerr << "fail Initialize" << endl;
	else cout << "Initialize" << endl;

	::makeShader(v_path,f_path,ShaderID);
	makeObj();
	InitBuffer();
	initTexture();
	glutDisplayFunc(DrawSceneCall);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(keyboardCall);
	glutTimerFunc(1, timer, 1);
	glutMainLoop();
}

void timer(int value)
{
	if (Rotate == true)
	{
		angle += 3.0f;
	}

	glutPostRedisplay();
	glutTimerFunc(17, timer, value);
}

void DrawSceneCall()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	{
		glBindVertexArray(VAO[2]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glUniform1i(glGetUniformLocation(ShaderID, "textureC"),0);
		glm::mat4 backgroundMatrix = glm::mat4(1.0f);
		unsigned int backgroundNormalMatrixLocation = glGetUniformLocation(ShaderID, "normalTransform");
		glUniformMatrix4fv(backgroundNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(backgroundMatrix));
		unsigned int cameraViewLocation = glGetUniformLocation(ShaderID, "viewTransform");
		glUniformMatrix4fv(cameraViewLocation, 1, GL_FALSE, glm::value_ptr(backgroundMatrix));
		unsigned int cameraPosLocation = glGetUniformLocation(ShaderID, "cameraPos");
		glUniform3fv(cameraPosLocation, 1, glm::value_ptr(glm::vec3(0, 0, 1)));
		unsigned int projectionLocation = glGetUniformLocation(ShaderID, "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(backgroundMatrix));
		backgroundMatrix = glm::translate(backgroundMatrix, glm::vec3(0, 0, -1));
		backgroundMatrix = glm::rotate(backgroundMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
		backgroundMatrix = glm::scale(backgroundMatrix, glm::vec3(2, 2, 2));
		unsigned int backgroundMatrixLocation = glGetUniformLocation(ShaderID, "modelTransform");
		glUniformMatrix4fv(backgroundMatrixLocation, 1, GL_FALSE, glm::value_ptr(backgroundMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[2].size());
	}
	/// ////////////////////////////////////////////////////////////

	glm::mat4 cameraRevoluMatrix = glm::mat4(1.0f);
	cameraRevoluMatrix = glm::rotate(cameraRevoluMatrix, glm::radians(cameraRevolu), glm::vec3(0, 1, 0));
	glm::vec3 newCameraPos = glm::vec3(cameraRevoluMatrix * glm::vec4(cameraPos, 1));
	glm::vec3 objCenter = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDir = glm::normalize(newCameraPos - objCenter);//n
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::cross(up, cameraDir);//v
	glm::vec3 cameraUp = glm::cross(cameraDir, cameraRight);
	glm::mat4 cameraView = glm::mat4(1.0f);
	cameraView = glm::lookAt(newCameraPos, -cameraDir, cameraUp);
	unsigned int cameraViewLocation = glGetUniformLocation(ShaderID, "viewTransform");
	glUniformMatrix4fv(cameraViewLocation, 1, GL_FALSE, glm::value_ptr(cameraView));
	unsigned int cameraPosLocation = glGetUniformLocation(ShaderID, "cameraPos");
	glUniform3fv(cameraPosLocation, 1, glm::value_ptr(newCameraPos));

	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), (float)Wheight / (float)Wwidth, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0, 0, -5.0f));
	unsigned int projectionLocation = glGetUniformLocation(ShaderID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));


	unsigned int lightColorLocation = glGetUniformLocation(ShaderID, "LightColor");
	glUniform3fv(lightColorLocation, 1, glm::value_ptr(lightColor));
	unsigned int lightPosLocation = glGetUniformLocation(ShaderID, "LightPos");
	glUniform3fv(lightPosLocation, 1, glm::value_ptr(lightPos));

	glm::mat4 lightTransMatrix = glm::mat4(1.0f);
	lightTransMatrix = glm::rotate(lightTransMatrix, glm::radians(lightRevoluAngle), glm::vec3(0, 1, 0));
	unsigned int lightTransLocation = glGetUniformLocation(ShaderID, "LightTransform");
	glUniformMatrix4fv(lightTransLocation, 1, GL_FALSE, glm::value_ptr(lightTransMatrix));

	drawtexture();
	glutSwapBuffers();
}


void keyboardCall(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'w':
		cameraPos.z -= 0.1f;
		break;
	case's':
		cameraPos.z += 0.1f;
		break;
	case'a':
		cameraPos.x -= 0.1f;
		break;
	case'd':
		cameraPos.x += 0.1f;
		break;
	case'z':
		cameraPos.y += 0.1f;
		break;
	case'Z':
		cameraPos.y -= 0.1f;
		break;
	case'c':
		selectLightColor++;
		lightColor = lightColorKind[selectLightColor % 4];
		break;
	case'r':
		lightRevoluAngle += 1.0f;
		break;
	case'R':
		lightRevoluAngle -= 1.0f;
		break;
	case'k':
		lightPos.z += 0.2f;
		break;
	case'l':
		lightPos.z -= 0.2f;
		break;
	case 'y':
		cameraRevolu -= 2.0f;
		break;
	case'q':
		glutLeaveMainLoop();
		break;
	case 't':
		checkjpg = !checkjpg;
		break;
	case 'p':
		change = !change;
		break;
	}
	glutPostRedisplay();
}


void InitBuffer()
{
	glGenVertexArrays(2, VAO);

	glBindVertexArray(VAO[0]);
	glGenBuffers(3, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Vertex[0].size(), &Vertex[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Nomal[0].size(), &Nomal[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * Texture[0].size(), &Texture[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(2);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	glBindVertexArray(VAO[1]);
	glGenBuffers(3, &VBO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Vertex[1].size(), &Vertex[1][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Nomal[1].size(), &Nomal[1][0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * Texture[1].size(), &Texture[1][0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(2);


	glBindVertexArray(VAO[2]);
	glGenBuffers(3, &VBO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Vertex[2].size(), &Vertex[2][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Nomal[2].size(), &Nomal[2][0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * Texture[2].size(), &Texture[2][0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(2);

}

void makeObj()
{
	readTriangleObj("Model/28-30/cube3_.obj", Vertex[0], Texture[0], Nomal[0]);
	readTriangleObj("Model/28-30/pyramiduv.obj", Vertex[1], Texture[1], Nomal[1]);
	readTriangleObj("Model/28-30/plane3.obj", Vertex[2], Texture[2], Nomal[2]);
}

void drawtexture()
{
	glUseProgram(ShaderID);
	if (change == 0)
	{

		glBindVertexArray(VAO[0]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glUniform1i(glGetUniformLocation(ShaderID, "textureC"), 0);
		glm::mat4 cubeTrasMatrix = glm::mat4(1.0f);
		cubeTrasMatrix = glm::rotate(cubeTrasMatrix, glm::radians(angle), glm::vec3(0, 1, 0));
		cubeTrasMatrix = glm::translate(cubeTrasMatrix, glm::vec3(0, 0, 0));
		cubeTrasMatrix = glm::scale(cubeTrasMatrix, glm::vec3(1.5, 2.5, 1.5));
		unsigned int cubeTransMatrixLocation = glGetUniformLocation(ShaderID, "modelTransform");
		glUniformMatrix4fv(cubeTransMatrixLocation, 1, GL_FALSE, glm::value_ptr(cubeTrasMatrix));
		glm::mat4 cubeNormalMatrix = glm::mat4(1.0f);
		cubeNormalMatrix = glm::rotate(cubeNormalMatrix, glm::radians(angle), glm::vec3(0, 1, 0));
		unsigned int cubeNormalMatrixLocation = glGetUniformLocation(ShaderID, "normalTransform");
		glUniformMatrix4fv(cubeNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(cubeNormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[0].size());
	}

	if (change == 1)
	{
		glBindVertexArray(VAO[1]);
		glActiveTexture(GL_TEXTURE0); // °°Àº°Å¶û ¸ÂÃçÁÖ±â
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glUniform1i(glGetUniformLocation(ShaderID, "textureC"), 0);
		glm::mat4 PyramidTrasMatrix = glm::mat4(1.0f);
		PyramidTrasMatrix = glm::rotate(PyramidTrasMatrix, glm::radians(angle), glm::vec3(0, 1, 0));
		PyramidTrasMatrix = glm::translate(PyramidTrasMatrix, glm::vec3(0, 0, 0));
		PyramidTrasMatrix = glm::scale(PyramidTrasMatrix, glm::vec3(1.5, 1.5, 1.5));
		unsigned int PyramidTransMatrixLocation = glGetUniformLocation(ShaderID, "modelTransform");
		glUniformMatrix4fv(PyramidTransMatrixLocation, 1, GL_FALSE, glm::value_ptr(PyramidTrasMatrix));
		glm::mat4 PyramidNormalMatrix = glm::mat4(1.0f);
		PyramidNormalMatrix = glm::rotate(PyramidNormalMatrix, glm::radians(angle), glm::vec3(0, 1, 0));
		unsigned int PyramidNormalMatrixLocation = glGetUniformLocation(ShaderID, "normalTransform");
		glUniformMatrix4fv(PyramidNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(PyramidNormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[1].size());
	}

}

void initTexture()
{

	glGenTextures(2, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int widthImage, heightImage, numberOfChannel;
	unsigned char* data = stbi_load("Resource/28-30/Cubepicture.bmp", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int pwidthImage, pheightImage, pnumberOfChannel;
	unsigned char* pdata = stbi_load("Resource/28-30/pyramidpicture.bmp", &pwidthImage, &pheightImage, &pnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pwidthImage, pheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, pdata);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pdata);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int BackwidthImage, BackheightImage, BacknumberOfChannel;
	unsigned char* Backdata = stbi_load("Resource/28-30/sky_texture.jpg", &BackwidthImage, &BackheightImage, &BacknumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BackwidthImage, BackheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, Backdata);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(Backdata);
}
