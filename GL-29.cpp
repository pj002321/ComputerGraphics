#include"stdafx.h"
#include"readTriangleObj.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
char vn[32] = "Shader/VertexTextureShader.glsl";
char fn[32] = "Shader/fragmentBlendShader.glsl";
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
void LocationSnow();

GLuint fragmentID;
GLuint vertexID;
GLuint ShaderID;

char* vertexSource;
char* fragmentSource;

int Wwidth;
int Wheight;
struct Snow {
	float x;
	float y;
	float z;
};
Snow SLocation[50];
Snow SaveLocation[50];
Snow SnowSpeed[50];


GLuint VAO[4];
GLuint VBO[20];

vector<glm::vec4> Vertex[4];
vector<glm::vec4> Nomal[4];
vector<glm::vec2> Texture[4];

float snowx = 0.0f;
float snowy = 5.8f;
float snowz = 0.0f;
unsigned int texture[2];
unsigned int pyramidtexture;
float angle = 0.0f;
float cameraRevolu = 0.0f;
float lightRevoluAngle = 0.0f;
bool change = false;
bool Rotate = true;
bool ScreenRotate = false;
bool snowcheck = true;

glm::vec3 cameraPos = glm::vec3(1.0f, 3.0f, 8.0f);
glm::vec3 lightPos = glm::vec3(0, 3.0f, 2.5f);
glm::vec3 lightColor = glm::vec3(0.7f, 0.7f, 0.7f);

float Buildingx[8] = { -2.0f,2.0f,-2.0f,2.0f };
float Buildingz[8] = { -2.0f,-2.0f,2.0f,2.0f };

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
	glutInitWindowSize(Wwidth, Wheight);
	glutCreateWindow("texture example");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cerr << "fail Initialize" << endl;
	else cout << "Initialize" << endl;
	LocationSnow();


	::makeShader(vn, fn, ShaderID);
	makeObj();
	InitBuffer();
	initTexture();
	glutDisplayFunc(DrawSceneCall);
	glutReshapeFunc(::Resize);
	glutKeyboardFunc(keyboardCall);
	glutTimerFunc(1, timer, 1);
	glutMainLoop();
}

void timer(int value)
{
	if (ScreenRotate)
	{
		cameraRevolu -= 2.0f;
	}
	if (Rotate == true)
	{
		angle += 3.0f;
	}
	if (snowcheck == true)
	{
		for (int i = 0; i < 50; i++) {
			SLocation[i].y -= SnowSpeed[i].y;
			if (SLocation[i].y <= 0.0f) {
				SLocation[i].y = SaveLocation[i].y;
			}

		}
	}
	glutPostRedisplay();
	glutTimerFunc(17, timer, value);
}
void DrawSceneCall()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//카메라
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

	//카메라#

	//투영
	//원근 투영
	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), (float)Wheight / (float)Wwidth, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0, 0, -5.0f));
	unsigned int projectionLocation = glGetUniformLocation(ShaderID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	//조명
	//light Color
	unsigned int lightColorLocation = glGetUniformLocation(ShaderID, "LightColor");
	glUniform3fv(lightColorLocation, 1, glm::value_ptr(lightColor));
	unsigned int lightPosLocation = glGetUniformLocation(ShaderID, "LightPos");
	glUniform3fv(lightPosLocation, 1, glm::value_ptr(lightPos));
	//light Trans
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
		ScreenRotate = !ScreenRotate;
		break;
	case'q':
		glutLeaveMainLoop();
		break;
	case 'p':
		change = !change;
		break;
	}
	glutPostRedisplay();
}
void LocationSnow() {
	for (int i = 0; i < 50; i++) {
		random_device rd;
		default_random_engine dre(rd());
		uniform_real_distribution<>ScaleXZ(-6.0, 6.0);
		uniform_real_distribution<>LoctionY(4.0, 7.0);
		uniform_real_distribution<>Speed(0.02, 0.05);

		float Sx = ScaleXZ(dre);
		float Sz = ScaleXZ(dre);
		float Sy = LoctionY(dre);
		float SpeedY = Speed(dre);

		SLocation[i].x = Sx;
		SLocation[i].y = Sy;
		SLocation[i].z = Sz;

		SaveLocation[i].x = Sx;
		SaveLocation[i].y = Sy;
		SaveLocation[i].z = Sz;

		SnowSpeed[i].y = SpeedY;
	}
}

void InitBuffer()
{
	glGenVertexArrays(4, VAO);
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

	/////////////////////////////////////////////////////////////////////////////////////////////////

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

	glBindVertexArray(VAO[3]);
	glGenBuffers(3, &VBO[9]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Vertex[3].size(), &Vertex[3][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Nomal[3].size(), &Nomal[3][0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[11]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * Texture[3].size(), &Texture[3][0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(2);

}

void makeObj()
{
	readTriangleObj("Model/28-30/plane3.obj", Vertex[0], Texture[0], Nomal[0]);
	readTriangleObj("Model/28-30/pyramiduv.obj", Vertex[1], Texture[1], Nomal[1]);
	readTriangleObj("Model/28-30/cube3_.obj", Vertex[2], Texture[2], Nomal[2]);
	readTriangleObj("Model/28-30/Sphere2.obj", Vertex[3], Texture[3], Nomal[3]);
}

void drawtexture()
{
	glUseProgram(ShaderID);

	for (int i = 0; i < 50; i++) {
		glBindVertexArray(VAO[3]);
		unsigned int snowBlendCheck = glGetUniformLocation(ShaderID, "Blendcheck");
		glUniform1i(snowBlendCheck, 0);
		glm::mat4 Snow = glm::mat4(1.0f);
		Snow = glm::translate(Snow, glm::vec3(SLocation[i].x, SLocation[i].y, SLocation[i].z));
		Snow = glm::scale(Snow, glm::vec3(0.05f, 0.05f, 0.05f));
		unsigned int SnowLocation = glGetUniformLocation(ShaderID, "modelTransform");
		glUniformMatrix4fv(SnowLocation, 1, GL_FALSE, glm::value_ptr(Snow));
		glm::mat4 SnowNormalmodel = glm::mat4(1.0f);
		SnowNormalmodel = glm::translate(SnowNormalmodel, glm::vec3(SLocation[i].x, SLocation[i].y, SLocation[i].z));
		unsigned int SnowNormalmodelLocation = glGetUniformLocation(ShaderID, "normalTransform");
		glUniformMatrix4fv(SnowNormalmodelLocation, 1, GL_FALSE, glm::value_ptr(SnowNormalmodel));
		unsigned int SnowColorLocation = glGetUniformLocation(ShaderID, "objColor");
		glUniform3f(SnowColorLocation, 0.958f, 0.958f, 0.958f);
		glDrawArrays(GL_TRIANGLES, 0, Vertex[3].size());
	}
	glBindVertexArray(VAO[0]);
	unsigned int BlendCheck = glGetUniformLocation(ShaderID, "Blendcheck");
	glUniform1i(BlendCheck, 2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glUniform1i(glGetUniformLocation(ShaderID, "textureC"), 0);
	glm::mat4 cubeTrasMatrix = glm::mat4(1.0f);
	cubeTrasMatrix = glm::scale(cubeTrasMatrix, glm::vec3(8.0, 1.5, 8.0));
	unsigned int cubeTransMatrixLocation = glGetUniformLocation(ShaderID, "modelTransform");
	glUniformMatrix4fv(cubeTransMatrixLocation, 1, GL_FALSE, glm::value_ptr(cubeTrasMatrix));
	glm::mat4 cubeNormalMatrix = glm::mat4(1.0f);
	unsigned int cubeNormalMatrixLocation = glGetUniformLocation(ShaderID, "normalTransform");
	glUniformMatrix4fv(cubeNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(cubeNormalMatrix));
	glDrawArrays(GL_TRIANGLES, 0, Vertex[0].size());

	glBindVertexArray(VAO[1]);
	unsigned int PyramidBlendCheck = glGetUniformLocation(ShaderID, "Blendcheck");
	glUniform1i(PyramidBlendCheck, 2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glUniform1i(glGetUniformLocation(ShaderID, "textureC"), 0);
	glm::mat4 Pyramid = glm::mat4(1.0f);
	Pyramid = glm::scale(Pyramid, glm::vec3(1.5, 1.5, 1.5));
	unsigned int PyramidTransMatrixLocation = glGetUniformLocation(ShaderID, "modelTransform");
	glUniformMatrix4fv(PyramidTransMatrixLocation, 1, GL_FALSE, glm::value_ptr(Pyramid));
	glm::mat4 PyramidNormalMatrix = glm::mat4(1.0f);
	unsigned int PyramidNormalMatrixLocation = glGetUniformLocation(ShaderID, "normalTransform");
	glUniformMatrix4fv(PyramidNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(PyramidNormalMatrix));
	glDrawArrays(GL_TRIANGLES, 0, Vertex[1].size());

	glEnable(GL_BLEND);
	for (int i = 0; i < 4; i++) {
		glBindVertexArray(VAO[2]);
		unsigned int BUILDINGBlendCheck = glGetUniformLocation(ShaderID, "Blendcheck");
		glUniform1i(BUILDINGBlendCheck, 1);
		glm::mat4 BUILDING = glm::mat4(1.0f);
		BUILDING = glm::translate(BUILDING, glm::vec3(Buildingx[i], 0.6f, Buildingz[i]));
		BUILDING = glm::scale(BUILDING, glm::vec3(1.0f, 3.0f, 1.0f));
		unsigned int BUILDINGTransMatrixLocation = glGetUniformLocation(ShaderID, "modelTransform");
		glUniformMatrix4fv(BUILDINGTransMatrixLocation, 1, GL_FALSE, glm::value_ptr(BUILDING));
		glm::mat4 BUILDINGNormalMatrix = glm::mat4(1.0f);
		unsigned int BUILDINGNormalMatrixLocation = glGetUniformLocation(ShaderID, "normalTransform");
		glUniformMatrix4fv(BUILDINGNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(BUILDINGNormalMatrix));
		unsigned int BUILDINGfragLocation = glGetUniformLocation(ShaderID, "objColor");
		glUniform3f(BUILDINGfragLocation, 0.6f, 0.6f, 0.5f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_TRIANGLES, 0, Vertex[2].size());

	}
	glDisable(GL_BLEND);



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
	unsigned char* data = stbi_load("Resource/28-30/sky_texture.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int PYwidthImage, PYheightImage, PYnumberOfChannel;
	unsigned char* PYdata = stbi_load("Resource/28-30/123.jpg", &PYwidthImage, &PYheightImage, &PYnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, PYwidthImage, PYheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, PYdata);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(PYdata);



}
