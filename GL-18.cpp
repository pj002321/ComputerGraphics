#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <math.h>
#include <vector>
#include <random>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

using namespace std;

void timer(int value);
void make_vertexShaders();
void make_fragmentShader();
GLvoid InitBuffer();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char Key, int x, int y);


GLUquadricObj* qobj;
GLuint VAO[6], VBO[12];
GLuint s_program[2];
GLint width, height;
GLuint vertexShader;
GLuint fragmentShader;
GLuint qobjShader;

//new
bool rotchk = false;
int check = 0;
bool ycheck = false;
bool xcheck = false;
bool solidchk= false;

int RotateStatex = 0;
int RotateStatey = 0;
float cx, cy, cz;
float r = 0.8;
float sub_r = 0.4;
int theta = 180;

int mainrotate = 0;
int mainrotate2 = 0;
int mainrotate3 = 0;
int subrotate1= 0;
int subrotate2 = 0;
int subrotate3 = 0;


float MainA_y = 0.0f;
float MainA_x = 30.0f;
float MainA_z = 0.0f;
float MainT_x = 0.0f;
float MainT_y = 0.0f;
float MainT_z = 0.0f;

float subAngle1_x = 0.0f;
float subAngle1_y = 0.0f;
float subAngle1_z = 0.0f;
float subAngle2_x = 0.0f;
float subAngle2_y = 0.0f;
float subAngle2_z = 0.0f;
float subAngle3_x = 0.0f;
float subAngle3_y = 0.0f;
float subAngle3_z = 0.0f;

float subTrans1_x = 1.2f;
float subTrans1_y = 0.0f;
float subTrans1_z = 0.0f;
float subTrans2_x = 1.0f;
float subTrans2_y = 0.8f;
float subTrans2_z = 0.0f;
float subTrans3_x = -1.2f;
float subTrans3_y = 0.8f;
float subTrans3_z = 0.0f;

float mainAngle_x = 0.0f;
float mainAngle_y = 0.0f;
float mainAngle_z = 0.0f;

float mainTrans1_x = 0.8f;
float mainTrans1_y = 0.0f;
float mainTrans1_z = 0.0f;
float mainTrans2_x = -0.8f;
float mainTrans2_y = -0.8f;
float mainTrans2_z = 0.0f;
float mainTrans3_x = -0.8f;
float mainTrans3_y = 0.8f;
float mainTrans3_z = 0.0f;

float C_viewX = -1.0f;
float C_viewY = -0.7f;
float C_viewZ = 2.0f;

vector<float>maincircle1;
vector<float>maincircle2;
vector<float>maincircle3;
vector<float>subcircle1;
vector<float>subcircle2;
vector<float>subcircle3;
GLUquadricObj* Qobj;
GLUquadricObj* mainQobj1;
GLUquadricObj* mainQobj2;
GLUquadricObj* mainQobj3;
GLUquadricObj* subQobj1;
GLUquadricObj* subQobj2;
GLUquadricObj* subQobj3;

void Make_spinprogram()
{

	float r_color, g_color, b_color;
	r_color = 0.5, g_color = 1.0, b_color = 0.3;
	for (int i = 0;  i < theta*2;  i++)
	{
			cx = r * cos(3.14 * i / theta);
			cz = r * sin(3.14 * i / theta);
		
		maincircle1.push_back(cx);
		maincircle1.push_back(0);
		maincircle1.push_back(cz);
		maincircle1.push_back(0);
		maincircle1.push_back(0);
		maincircle1.push_back(0);

	}

	for (int i = 0; i < theta * 2; i++)
	{
		cx = r * cos(3.14 * i / theta);
		cy = (-r)* cos(3.14 * i / theta);
		cz = r * sin(3.14 * i / theta);

		maincircle2.push_back(cx);
		maincircle2.push_back(cy);
		maincircle2.push_back(cz);
		maincircle2.push_back(0);
		maincircle2.push_back(0);
		maincircle2.push_back(0);

	}
	for (int i = 0; i < theta * 2; i++)
	{
		cx = r * cos(3.14 * i / theta);
		cy = r * cos(3.14 * i / theta);
		cz = r * sin(3.14 * i / theta);

		maincircle3.push_back(cx);
		maincircle3.push_back(cy);
		maincircle3.push_back(cz);
		maincircle3.push_back(0);
		maincircle3.push_back(0);
		maincircle3.push_back(0);

	}

	for (int i = 0; i < theta * 2; i++)
	{
		
		cx = sub_r * cos(3.14 * i / theta);
		cz = sub_r * sin(3.14 * i / theta);

		subcircle1.push_back(cx);
		subcircle1.push_back(0);
		subcircle1.push_back(cz);
		subcircle1.push_back(0);
		subcircle1.push_back(0);
		subcircle1.push_back(0);

	}

	for (int i = 0; i < theta * 2; i++)
	{

		cx = sub_r * cos(3.14 * i / theta);
		cz = sub_r * sin(3.14 * i / theta);

		subcircle2.push_back(cx);
		subcircle2.push_back(0);
		subcircle2.push_back(cz);
		subcircle2.push_back(0);
		subcircle2.push_back(0);
		subcircle2.push_back(0);

	}

	for (int i = 0; i < theta * 2; i++)
	{

		cx = sub_r * cos(3.14 * i / theta);
		cz = sub_r * sin(3.14 * i / theta);

		subcircle3.push_back(cx);
		subcircle3.push_back(0);
		subcircle3.push_back(cz);
		subcircle3.push_back(0);
		subcircle3.push_back(0);
		subcircle3.push_back(0);

	}

}

GLchar* filetobuf(const GLchar* file)
{
	FILE* fptr;
	long length;
	GLchar* buf;

	fopen_s(&fptr, file, "rb");
	if (!fptr)
		return NULL;

	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (GLchar*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;

	return buf;
}


void make_vertexShaders()
{
	GLchar* vertexSource;
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLchar* qobjSource;
	qobjSource = filetobuf("qobjvertex.glsl");
	qobjShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(qobjShader, 1, &qobjSource, NULL);
	glCompileShader(qobjShader);

}


void make_fragmentShader()
{
	GLchar* fragmentSource;
	fragmentSource = filetobuf("fragment.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

}


void InitShader()
{
	make_vertexShaders();
	make_fragmentShader();

	s_program[0] = glCreateProgram();
	glAttachShader(s_program[0], vertexShader);
	glAttachShader(s_program[0], fragmentShader);
	s_program[1] = glCreateProgram();
	glAttachShader(s_program[1], qobjShader);
	glAttachShader(s_program[1], fragmentShader);

	glLinkProgram(s_program[1]);
	glLinkProgram(s_program[0]);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(qobjShader);

	glUseProgram(s_program[0]);
	glUseProgram(s_program[1]);

}


GLvoid InitBuffer()
{
	if (rotchk==true)
	{
		Make_spinprogram();
		rotchk = false;
	}
	

	glGenVertexArrays(6, VAO);

	glBindVertexArray(VAO[0]);
	glGenBuffers(2, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle1.size(), &maincircle1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle1.size(), &maincircle1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[1]);
	glGenBuffers(2, &VBO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle2.size(), &maincircle2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle2.size(), &maincircle2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[2]);
	glGenBuffers(2, &VBO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle3.size(), &maincircle3[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[5]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle3.size(), &maincircle3[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[3]);
	glGenBuffers(2, &VBO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * subcircle1.size(), &subcircle1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[7]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * subcircle1.size(), &subcircle1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[4]);
	glGenBuffers(2, &VBO[8]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * subcircle2.size(), &subcircle2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[9]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * subcircle2.size(), &subcircle2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[5]);
	glGenBuffers(2, &VBO[10]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * subcircle3.size(), &subcircle3[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[11]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * subcircle3.size(), &subcircle3[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


}


void timer(int value)
{
	if (check == 1)
	{

		if (xcheck == true)
		{
			MainA_y = 0.0f;
			MainA_x += 5.0f;
		}
		if (xcheck == false)
		{
			MainA_y = 0.0f;
			MainA_x -= 5.0f;
		}
	}
	if (check==2)
	{
	if (ycheck == true)
	{
		MainA_x = 30.0f;
		MainA_y += 5.0f;
	}
	if (ycheck == false)
	{
		MainA_x = 30.0f;
		MainA_y -= 5.0f;
	}
	}
	
		mainTrans1_x = maincircle1[6 * mainrotate + 0];
		mainTrans1_y = maincircle1[6 * mainrotate + 1];
		mainTrans1_z = maincircle1[6 * mainrotate + 2];
		mainTrans2_x = maincircle2[18 * mainrotate2 + 0];
		mainTrans2_y = maincircle2[18 * mainrotate2 + 1];
		mainTrans2_z = maincircle2[18 * mainrotate2 + 2];
		mainTrans3_x = maincircle3[12 * mainrotate3 + 0];
		mainTrans3_y = maincircle3[12 * mainrotate3 + 1];
		mainTrans3_z = maincircle3[12 * mainrotate3 + 2];
		subTrans1_x = subcircle1[12 * subrotate1 + 0];
		subTrans1_y = subcircle1[12 * subrotate1 + 1];
		subTrans1_z = subcircle1[12 * subrotate1 + 2];
		subTrans2_x = subcircle2[24 * subrotate2 + 0];
		subTrans2_y = subcircle2[24 * subrotate2 +1 ];
		subTrans2_z = subcircle2[24 * subrotate2+2];
		subTrans3_x = subcircle3[18 * subrotate3 + 0];
		subTrans3_y = subcircle3[18 * subrotate3 + 1];
		subTrans3_z = subcircle3[18 * subrotate3 + 2];
		mainrotate++;
		mainrotate2++;
		mainrotate3++;
		subrotate1++;
		subrotate2++;
		subrotate3++;

		if (mainrotate == 360) {
			mainrotate = 0;
		}
		if (mainrotate2 == 120) {
			mainrotate2 = 0;
		}
		if (mainrotate3 == 180) {
			mainrotate3 = 0;
		}

		if (subrotate1 == 180) {
			subrotate1 = 0;
		}
		if (subrotate2== 90) {
			subrotate2 = 0;
		}
		if (subrotate3 == 120) {
			subrotate3 = 0;
		}

	
	glutPostRedisplay();
	glutTimerFunc(100, timer, 1);
}
void drawScene()
{
	GLfloat rColor = 0.2;
	GLfloat gColor = 0.2;
	GLfloat bColor = 0.2;
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //깊이 체크 (컬링)

	InitBuffer(); 
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	if (solidchk==true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}
	

	glUseProgram(s_program[0]);
	unsigned int viewLocation = glGetUniformLocation(s_program[0], "viewTransform");
	unsigned int projLoc = glGetUniformLocation(s_program[0], "projectionTransform");
	glm::vec3 cameraPos = glm::vec3(C_viewX, C_viewY, C_viewZ);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 100.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);


	//vao0
	glm::mat4 MainCircle1 = glm::mat4(1.0f);
	MainCircle1 = glm::rotate(MainCircle1, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainCircle1 = glm::rotate(MainCircle1, glm::radians(MainA_y), glm::vec3(0.0f, 1.0, 0.0f));
	MainCircle1 = glm::translate(MainCircle1, glm::vec3(MainT_x, MainT_y, MainT_z));
	unsigned int MainLocation1 = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(MainLocation1, 1, GL_FALSE, glm::value_ptr(MainCircle1));
	glBindVertexArray(VAO[0]);
	glLineWidth(1.5f);
	glDrawArrays(GL_LINE_STRIP, 0, maincircle1.size() / 6);

	//vao1
	glm::mat4 MainCircle2 = glm::mat4(1.0f);
	MainCircle2 = glm::rotate(MainCircle2, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainCircle2 = glm::rotate(MainCircle2, glm::radians(MainA_y), glm::vec3(0.0f, 1.0, 0.0f));
	MainCircle2 = glm::translate(MainCircle2, glm::vec3(MainT_x, MainT_y, MainT_z));
	unsigned int MainLocation2 = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(MainLocation2, 1, GL_FALSE, glm::value_ptr(MainCircle2));
	glBindVertexArray(VAO[1]);
	glLineWidth(1.5f);
	glDrawArrays(GL_LINE_STRIP, 0, maincircle2.size() / 6);

	//vao2
	glm::mat4 MainCircle3 = glm::mat4(1.0f);
	MainCircle3 = glm::rotate(MainCircle3, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainCircle3 = glm::rotate(MainCircle3, glm::radians(MainA_y), glm::vec3(0.0f, 1.0, 0.0f));
	MainCircle3 = glm::translate(MainCircle3, glm::vec3(MainT_x, MainT_y, MainT_z));
	unsigned int MainLocation3 = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(MainLocation3, 1, GL_FALSE, glm::value_ptr(MainCircle3));
	glBindVertexArray(VAO[2]);
	glLineWidth(1.5f);
	glDrawArrays(GL_LINE_STRIP, 0, maincircle3.size() / 6);

	//vao3
	glm::mat4 SubCircle1 = glm::mat4(1.0f);
	SubCircle1 = glm::rotate(SubCircle1, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	SubCircle1 = glm::rotate(SubCircle1, glm::radians(MainA_y), glm::vec3(0.0f, 1.0, 0.0f));
	SubCircle1 = glm::translate(SubCircle1, glm::vec3(MainT_x, MainT_y, MainT_z));
	SubCircle1 = glm::translate(SubCircle1, glm::vec3(mainTrans1_x, mainTrans1_y, mainTrans1_z));
	unsigned int SubLocation1 = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(SubLocation1, 1, GL_FALSE, glm::value_ptr(SubCircle1));
	glBindVertexArray(VAO[3]);
	glLineWidth(1.5f);
	glDrawArrays(GL_LINE_STRIP, 0, subcircle1.size() / 6);

	//vao4
	glm::mat4 SubCircle2 = glm::mat4(1.0f);
	SubCircle2 = glm::rotate(SubCircle2, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	SubCircle2 = glm::rotate(SubCircle2, glm::radians(MainA_y), glm::vec3(0.0f, 1.0, 0.0f));
	SubCircle2 = glm::translate(SubCircle2, glm::vec3(MainT_x, MainT_y, MainT_z));
	SubCircle2 = glm::translate(SubCircle2, glm::vec3(mainTrans2_x, mainTrans2_y, mainTrans2_z));
	unsigned int SubLocation2 = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(SubLocation2, 1, GL_FALSE, glm::value_ptr(SubCircle2));
	glBindVertexArray(VAO[4]);
	glLineWidth(1.5f);
	glDrawArrays(GL_LINE_STRIP, 0, subcircle2.size() / 6);

	//vao5
	glm::mat4 SubCircle3 = glm::mat4(1.0f);
	SubCircle3= glm::rotate(SubCircle3, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	SubCircle3= glm::rotate(SubCircle3, glm::radians(MainA_y), glm::vec3(0.0f, 1.0, 0.0f));
	SubCircle3= glm::translate(SubCircle3, glm::vec3(MainT_x, MainT_y, MainT_z));
	SubCircle3= glm::translate(SubCircle3, glm::vec3(mainTrans3_x, mainTrans3_y, mainTrans3_z));
	unsigned int SubLocation3 = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(SubLocation3, 1, GL_FALSE, glm::value_ptr(SubCircle3));
	glBindVertexArray(VAO[5]);
	glLineWidth(1.5f);
	glDrawArrays(GL_LINE_STRIP, 0, subcircle3.size() / 6);


	glUseProgram(s_program[1]);
	Qobj = gluNewQuadric();
	gluQuadricDrawStyle(Qobj, GLU_FILL);
	
	unsigned int SphviewLocation = glGetUniformLocation(s_program[1], "viewTransform");
	unsigned int SphprojLoc = glGetUniformLocation(s_program[1], "projectionTransform");
	glm::vec3 SphcameraPos = glm::vec3(C_viewX, C_viewY, C_viewZ);
	glm::vec3 SphcameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 SphcameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 Sphview = glm::mat4(1.0f);
	Sphview = glm::lookAt(SphcameraPos, SphcameraDirection, SphcameraUp);
	glUniformMatrix4fv(SphviewLocation, 1, GL_FALSE, glm::value_ptr(Sphview));
	glm::mat4 Sphproj = glm::mat4(1.0f);
	Sphproj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 100.0f);
	glUniformMatrix4fv(SphprojLoc, 1, GL_FALSE, &Sphproj[0][0]);

	glm::mat4 CenterQobj = glm::mat4(1.0f);
	CenterQobj = glm::rotate(CenterQobj, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	CenterQobj = glm::rotate(CenterQobj, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	CenterQobj = glm::rotate(CenterQobj, glm::radians(MainA_z), glm::vec3(0.0f, 0.0f, 1.0f));
	CenterQobj = glm::translate(CenterQobj, glm::vec3(MainT_x, MainT_y, MainT_z));
	CenterQobj = glm::scale(CenterQobj, glm::vec3(0.6f, 0.6f, 0.6f));
	unsigned int CenterQobjLocation = glGetUniformLocation(s_program[1], "modelTransform");
	unsigned int CenterQobjFrag= glGetUniformLocation(s_program[1], "vColor");
	glUniformMatrix4fv(CenterQobjLocation, 1, GL_FALSE, glm::value_ptr(CenterQobj));
	glUniform3f(CenterQobjFrag, 1.0f, 0.0f, 1.0f);
	gluSphere(Qobj, 0.25, 20, 20);

	glm::mat4 MainQobj1 = glm::mat4(1.0f);
	mainQobj1 = gluNewQuadric();
	gluQuadricDrawStyle(mainQobj1, GLU_FILL);
	MainQobj1= glm::rotate(MainQobj1, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainQobj1= glm::rotate(MainQobj1, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	MainQobj1= glm::translate(MainQobj1, glm::vec3(MainT_x, MainT_y, MainT_z));
	MainQobj1 = glm::translate(MainQobj1, glm::vec3(mainTrans1_x, mainTrans1_y, mainTrans1_z));
	MainQobj1 = glm::rotate(MainQobj1, glm::radians(mainAngle_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainQobj1 = glm::rotate(MainQobj1, glm::radians(mainAngle_x), glm::vec3(0.0f, 1.0f, 0.0f));
	MainQobj1= glm::scale(MainQobj1, glm::vec3(0.3f, 0.3f, 0.3f));
	unsigned int CenterQobjLocation1 = glGetUniformLocation(s_program[1], "modelTransform");
	unsigned int CenterQobjFrag1 = glGetUniformLocation(s_program[1], "vColor");
	glUniformMatrix4fv(CenterQobjLocation1, 1, GL_FALSE, glm::value_ptr(MainQobj1));
	glUniform3f(CenterQobjFrag1, 1.0f, 0.0f, 0.7f);
	gluSphere(mainQobj1, 0.25, 20, 20);

	glm::mat4 MainQobj2 = glm::mat4(1.0f);
	mainQobj2 = gluNewQuadric();
	gluQuadricDrawStyle(mainQobj2, GLU_FILL);
	
	MainQobj2 = glm::rotate(MainQobj2, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainQobj2 = glm::rotate(MainQobj2, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	MainQobj2 = glm::translate(MainQobj2, glm::vec3(MainT_x, MainT_y, MainT_z));
	MainQobj2 = glm::translate(MainQobj2, glm::vec3(mainTrans2_x, mainTrans2_y, mainTrans2_z));
	MainQobj2 = glm::rotate(MainQobj2, glm::radians(mainAngle_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainQobj2 = glm::rotate(MainQobj2, glm::radians(mainAngle_y), glm::vec3(0.0f, 1.0f, 0.0f));
	MainQobj2 = glm::scale(MainQobj2, glm::vec3(0.3f, 0.3f, 0.3f));
	unsigned int CenterQobjLocation2 = glGetUniformLocation(s_program[1], "modelTransform");
	unsigned int CenterQobjFrag2 = glGetUniformLocation(s_program[1], "vColor");
	glUniformMatrix4fv(CenterQobjLocation2, 1, GL_FALSE, glm::value_ptr(MainQobj2));
	glUniform3f(CenterQobjFrag2, 1.0f, 0.3f, 1.0f);
	gluSphere(mainQobj2, 0.25, 20, 20);

	glm::mat4 MainQobj3 = glm::mat4(1.0f);
	mainQobj3 = gluNewQuadric();
	gluQuadricDrawStyle(mainQobj3, GLU_FILL);
	
	MainQobj3 = glm::rotate(MainQobj3, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainQobj3 = glm::rotate(MainQobj3, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	MainQobj3 = glm::translate(MainQobj3, glm::vec3(MainT_x, MainT_y, MainT_z));
	MainQobj3 = glm::translate(MainQobj3, glm::vec3(mainTrans3_x, mainTrans3_y, mainTrans3_z));
	MainQobj3 = glm::rotate(MainQobj3, glm::radians(mainAngle_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainQobj3 = glm::rotate(MainQobj3, glm::radians(mainAngle_y), glm::vec3(0.0f, 1.0f, 0.0f));
	MainQobj3 = glm::scale(MainQobj3, glm::vec3(0.3f, 0.3f, 0.3f));
	unsigned int CenterQobjLocation3 = glGetUniformLocation(s_program[1], "modelTransform");
	unsigned int CenterQobjFrag3 = glGetUniformLocation(s_program[1], "vColor");
	glUniformMatrix4fv(CenterQobjLocation3, 1, GL_FALSE, glm::value_ptr(MainQobj3));
	glUniform3f(CenterQobjFrag3, 1.0f, 0.3f, 0.4f);
	gluSphere(mainQobj3, 0.25, 20, 20);

	glm::mat4 SubQobj1 = glm::mat4(1.0f);
	subQobj1 = gluNewQuadric();
	gluQuadricDrawStyle(subQobj1, GLU_FILL);
	
	SubQobj1= glm::rotate(SubQobj1, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	SubQobj1= glm::rotate(SubQobj1, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	SubQobj1= glm::translate(SubQobj1, glm::vec3(MainT_x, MainT_y, MainT_z));
	SubQobj1= glm::translate(SubQobj1, glm::vec3(mainTrans1_x, mainTrans1_y, mainTrans1_z));
	SubQobj1 = glm::translate(SubQobj1, glm::vec3(subTrans1_x, subTrans1_y, subTrans1_z));
	SubQobj1= glm::rotate(SubQobj1, glm::radians(subAngle1_x), glm::vec3(1.0f, 0.0f, 0.0f));
	SubQobj1= glm::rotate(SubQobj1, glm::radians(subAngle1_y), glm::vec3(0.0f, 1.0f, 0.0f));
	SubQobj1= glm::scale(SubQobj1, glm::vec3(0.2f, 0.2f, 0.2f));
	unsigned int SubQobjLocation1 = glGetUniformLocation(s_program[1], "modelTransform");
	unsigned int SubQobjFrag1 = glGetUniformLocation(s_program[1], "vColor");
	glUniformMatrix4fv(SubQobjLocation1, 1, GL_FALSE, glm::value_ptr(SubQobj1));
	glUniform3f(SubQobjFrag1, 1.0f, 0.3f, 1.0f);
	gluSphere(subQobj1, 0.25, 20, 20);

	glm::mat4 SubQobj2 = glm::mat4(1.0f);
	subQobj2 = gluNewQuadric();
	gluQuadricDrawStyle(subQobj2, GLU_FILL);

	SubQobj2 = glm::rotate(SubQobj2, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	SubQobj2 = glm::rotate(SubQobj2, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	SubQobj2 = glm::translate(SubQobj2, glm::vec3(MainT_x, MainT_y, MainT_z));
	SubQobj2 = glm::translate(SubQobj2, glm::vec3(mainTrans2_x, mainTrans2_y, mainTrans2_z));
	SubQobj2 = glm::translate(SubQobj2, glm::vec3(subTrans2_x, subTrans2_y, subTrans2_z));
	SubQobj2 = glm::rotate(SubQobj2, glm::radians(subAngle2_x), glm::vec3(1.0f, 0.0f, 0.0f));
	SubQobj2 = glm::rotate(SubQobj2, glm::radians(subAngle2_y), glm::vec3(0.0f, 1.0f, 0.0f));
	SubQobj2 = glm::scale(SubQobj2, glm::vec3(0.2f, 0.2f, 0.2f));
	unsigned int SubQobjLocation2 = glGetUniformLocation(s_program[1], "modelTransform");
	unsigned int SubQobjFrag2 = glGetUniformLocation(s_program[1], "vColor");
	glUniformMatrix4fv(SubQobjLocation2, 1, GL_FALSE, glm::value_ptr(SubQobj2));
	glUniform3f(SubQobjFrag2, 0.7f, 0.3f, 1.0f);
	gluSphere(subQobj2, 0.25, 20, 20);

	glm::mat4 SubQobj3 = glm::mat4(1.0f);
	subQobj3 = gluNewQuadric();
	gluQuadricDrawStyle(subQobj3, GLU_FILL);
	SubQobj3 = glm::rotate(SubQobj3, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	SubQobj3 = glm::rotate(SubQobj3, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	SubQobj3 = glm::translate(SubQobj3, glm::vec3(MainT_x, MainT_y, MainT_z));
	SubQobj3 = glm::translate(SubQobj3, glm::vec3(mainTrans3_x, mainTrans3_y, mainTrans3_z));
	SubQobj3 = glm::translate(SubQobj3, glm::vec3(subTrans3_x, subTrans3_y, subTrans3_z));
	SubQobj3 = glm::rotate(SubQobj3, glm::radians(subAngle3_x), glm::vec3(1.0f, 0.0f, 0.0f));
	SubQobj3 = glm::rotate(SubQobj3, glm::radians(subAngle3_y), glm::vec3(0.0f, 1.0f, 0.0f));
	SubQobj3 = glm::scale(SubQobj3, glm::vec3(0.2f, 0.2f, 0.2f));
	unsigned int SubQobjLocation3 = glGetUniformLocation(s_program[1], "modelTransform");
	unsigned int SubQobjFrag3 = glGetUniformLocation(s_program[1], "vColor");
	glUniformMatrix4fv(SubQobjLocation3, 1, GL_FALSE, glm::value_ptr(SubQobj3));
	glUniform3f(SubQobjFrag3, 0.2f, 0.3f, 1.0f);
	gluSphere(subQobj3, 0.25, 20, 20);

	glutSwapBuffers();
}

GLvoid KeyBoard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'x':
		MainT_z -= 0.1f;
		break;
	case 'z':
		MainT_z += 0.1f;
		break;
	case 'y':
		check = 2;
		ycheck = !ycheck;
		break;
	case 'Y':
		check = 2;
		ycheck = !ycheck;
		break;
	case 'm':
		solidchk = !solidchk;
		break;
	case 'w':
		MainT_y += 0.05f;
		break;
	case 's':
		MainT_y -= 0.05f;
		break;
	case 'a':
		MainT_x -= 0.05f;
		break;
	case 'd':
		MainT_x += 0.05f;
		break;
	case 'c':
		rotchk = false;
		check = 0;
		 ycheck = false;
		 xcheck = false;
		 solidchk = false;

		RotateStatex = 0;
		RotateStatey = 0;
		r = 0.8;
		sub_r = 0.4;
		theta = 180;

	mainrotate = 0;
	mainrotate2 = 0;
	mainrotate3 = 0;
	subrotate1 = 0;
	subrotate2 = 0;
	subrotate3 = 0;


		MainA_y = 0.0f;
		MainA_x = 30.0f;
		MainA_z = 0.0f;
		MainT_x = 0.0f;
		MainT_y = 0.0f;
		MainT_z = 0.0f;

		subAngle1_x = 0.0f;
		subAngle1_y = 0.0f;
		subAngle1_z = 0.0f;
		subAngle2_x = 0.0f;
		subAngle2_y = 0.0f;
		subAngle2_z = 0.0f;
		subAngle3_x = 0.0f;
		subAngle3_y = 0.0f;
		subAngle3_z = 0.0f;

		subTrans1_x = 1.2f;
		subTrans1_y = 0.0f;
		subTrans1_z = 0.0f;
		subTrans2_x = 1.0f;
		subTrans2_y = 0.8f;
		subTrans2_z = 0.0f;
		subTrans3_x = -1.2f;
		subTrans3_y = 0.8f;
		subTrans3_z = 0.0f;

		mainAngle_x = 0.0f;
		mainAngle_y = 0.0f;
		mainAngle_z = 0.0f;

		mainTrans1_x = 0.8f;
		mainTrans1_y = 0.0f;
		mainTrans1_z = 0.0f;
		mainTrans2_x = -0.8f;
		mainTrans2_y = -0.8f;
		mainTrans2_z = 0.0f;
		mainTrans3_x = -0.8f;
		mainTrans3_y = 0.8f;
		mainTrans3_z = 0.0f;

		C_viewX = -1.0f;
		C_viewY = -0.7f;
		C_viewZ = 2.0f;
		break;
	case 'q':
		exit(0);
		break;
	}
}

GLvoid Reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}

int main(int argc, char** argv)
{

	width = 800;
	height = 600;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //depth+
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example 1");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "NOT INIT" << endl;
	}
	else
		cout << "INIT<<endl";

	rotchk = true;
	InitShader();
	InitBuffer();
	glutKeyboardFunc(KeyBoard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(120, timer, 1);
	glutReshapeFunc(Reshape);

	glutMainLoop();

	return 0;
}

