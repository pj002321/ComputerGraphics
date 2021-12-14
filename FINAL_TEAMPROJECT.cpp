﻿#include<gl/glew.h>
#include<gl/freeglut.h>
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
#include "_makeshader.h"
#include "readTriangleObj.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void InitBuffer();
void initTexture();
using namespace std;
unsigned int texture[10];
//call_back
void MainView();
void Resize(int w, int h);
void keyboardCall(unsigned char key, int x, int y);

//func
void timer(int value);
void drawPlane();
void ObjList();
void drawscene();
void LocationRandom();

int Wwidth = 0;
int Wheight = 0;

//Struck

struct Camera
{
	float C_x = 1.0f;
	float C_y = 5.0f;
	float C_z = 9.0f;

}Camerapos;


struct Angle
{
	float angle = 0.0f;
	float anglex = 0.0f;
	float angley = 0.0f;
	float AngleTrap2 = 00.0f;
	float AngleTrap = 0.0f;
	float Radian = 0.0f;
	//---------------------
	float AngleRevolx = 45.0f;
	float AngleRevoly = 45.0f;
	//----------------------
	float anglecamera = 160.0f;
	float anglecamera2 = 0.0f;
	float ObjAngle = 20.0f;
	//------------------
	float LightRadian = 10.0f;
	//------------------
	float BodyAngle = 0.0f;
	float ArmAngle = 45.0f;
	float LegAngle = 0.0f;
	float MainSwing1 = 0.0f;
	float MainSwing2 = 0.0f;
	float StageAngle = 0.0f;
	float StageAngle2 = 0.0f;
	float EyeAngle = 0.0f;
	float CpaeAngle = 0.0f;
}AngleList;


//scale
struct Scale
{
	float X = 0.0f;
	float Y = 4.5f;
	float Z = 6.5f;
	//-------------
	float x = 2.0f;
	float y = 2.0f;
	float z = 2.0f;
	//-------------
	float Mx = 0.0f;
	float My = 0.0f;
	float Mz = 0.0f;
	//--------------
	float ALx = 0.1f;
	float ALy = 0.3f;
	float ALz = 0.1f;
	//---------------
	float TSy = 0.6f;
	//---------------
	float Doorx = 6.0f;
	//---------------
	float PullScaleRx[3] = { 6.0f,6.0f,6.0f };
	float PullScaleRz = 2.0f;
	float PullScaleRy = 2.0f;
	//------------------
	float PullScaleLx[3] = { 6.0f,6.0f,6.0f };
	float PullScaleLz = 2.0f;
	float PullScaleLy = 2.0f;
}Scalepos;

//trans
struct Transration
{
	float T_x = 0.0f;
	float T_y = 0.8f;
	float T_z = 0.0f;
	//---------------
	float T_StageX = 0.0f;
	float T_StageY = 0.0f;
	float T_StageZ = 0.0f;
	//----------------
	float T_Stage2X = 0.0f;
	float T_Stage2Y = 0.0f;
	float T_Stage2Z = 0.0f;
	//------------------
	float T_Stage2ZA[3] = { 35.0f,50.0f,65.0f };
	//----------------
	float T_Trapx = 0.0f;
	float T_Trapy = 0.6f;
	float T_Trapz = 0.0f;
	//-----------------
	float T_Trapx2 = 16.0f;
	float T_Trapy2 = 1.5f;
	float T_Trapz2 = 20.0f;
	//---------------
	float T_Bodyx = 0.0f;
	float T_Bodyy = 0.9f;
	float T_Bodyz = -2.0f;
	//--------------------
	float T_Cpaex = 0.0f;
	float T_Cpaey = 0.6f;
	float T_Cpaez = -2.0f;
	//-------------------
	float T_Eyex = 0.0f;
	float T_Eyey = 0.9f;
	float T_Eyez = -2.0f;
	//----------------
	float T_ArmLegx = 0.0f;
	float T_ArmLegy = 0.77f;
	float T_ArmLegz = 0.0f;
	//-------------------
	float DoorxL = 1.8f;
	float DoorxR = -1.8f;

}TransList;

struct Snow {
	float x;
	float y;
	float z;
};
Snow SLocation[200];
Snow SaveLocation[200];
Snow SnowSpeed[200];

struct Star {
	float x;
	float y;
	float z;
};
Star StarLocation[15];
Star StarSaveLocation[15];
Star StarSpeed[15];

struct Trap {
	float x;
	float y;
	float z;
};
Trap radomcorail[6];
Trap Pullmove[3];
GLuint VAO[30];
GLuint VBO[90];

vector<glm::vec4> Vertex[25];
vector<glm::vec4> Nomal[25];
vector<glm::vec2> Texture[25];


float snowx = 0.0f;
float snowy = 5.8f;
float snowz = 0.0f;
unsigned int pyramidtexture;
float angle = 0.0f;
float cameraRevolu = 0.0f;
float lightRevoluAngle = 0.0f;
bool change = false;
bool Rotate = true;
bool ScreenRotate = false;
bool Opening = false;
int Mainswingchk = 1;
bool MainswingAngle1 = true;
bool MainswingAngle2 = false;
bool TrapAction = true;
bool Door = true;
bool Opencheck = false;
bool TrapHelyAction = false;
bool JumpState = false;
bool TrapJumpState = true;
int jumpcheck = 0;
int trapjumpcheck = 0;
bool PullTrapcheck = true;
int selectLightColor = 0;
bool snowcheck = true;
int PullTrapPoint = 0;
int PullTrapPoint2 = 0;
int PullTrapPoint3 = 0;
int PullTrapPoint4 = 0;
int PullTrapPoint5 = 0;
int PullTrapPoint6 = 0;
glm::vec3 objC = glm::vec3(0, 0, 0);
glm::vec3 cameraPos = glm::vec3(1.0f, 3.0f, 10.0f);
glm::vec3 lightPos = glm::vec3(0, 3.0f, 2.5f);
glm::vec3 lightColor = glm::vec3(1.4f, 1.3f, 1.3f);
glm::vec3 Cameraposdir = glm::vec3(0.0f);
glm::vec3 Cameradir = glm::vec3(0.0f);
float Movevalue = 0.2f;

glm::vec3 lightColorKind[4] = {
	glm::vec3(0.7f, 0.7f, 0.7f),
	glm::vec3(1,0,0),
	glm::vec3(0,1,0),
	glm::vec3(0,0,1)
};


void LocationRandom() {
	for (int i = 0; i < 200; i++) {
		random_device rd;
		default_random_engine dre(rd());
		uniform_real_distribution<>ScaleXZ(-15.0, 22.0);
		uniform_real_distribution<>LoctionY(0.0, 7.0);
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
	for (int i = 0; i < 15; i++) {
		random_device rd;
		default_random_engine dre(rd());
		uniform_real_distribution<>ScaleXZ(-15.0, 22.0);
		uniform_real_distribution<>LoctionY(0.0, 7.0);
		uniform_real_distribution<>Speed(0.02, 0.05);

		float Sx1 = ScaleXZ(dre);
		float Sz1 = ScaleXZ(dre);
		float Sy1 = LoctionY(dre);
		float SpeedY = Speed(dre);


		StarLocation[i].x = Sx1;
		StarLocation[i].y = Sy1;
		StarLocation[i].z = Sz1;

		StarSaveLocation[i].x = Sx1;
		StarSaveLocation[i].y = Sy1;
		StarSaveLocation[i].z = Sz1;

		StarSpeed[i].y = SpeedY;
	}
	for (int i = 0; i < 6; i++)
	{
		random_device rdx;
		random_device rdz;
		default_random_engine drex(rdx());
		default_random_engine drez(rdz());
		uniform_int_distribution<>Random(-4, 5);
		uniform_real_distribution<>RandomY(0, 0.05);
		float RX = Random(drex);
		float RZ = Random(drez);
		float RY = RandomY(drez);

		radomcorail[i].x = RX;
		radomcorail[i].z = RZ;
		radomcorail[i].y = 1.0f;

		

	}
	

}

float PullTrapLx[3] = { 5.0f,5.0f,5.0f };
float PullTrapLz[3] = { 36.0f,48.0f,63.0f };
float PullTrapRx[3] = { -5.0f,-5.0f,-5.0f, };
float PullTrapRz[3] = { 43.0f,53.0f,68.0f };
float HelyTrapx[7] = { 12.0f,16.0f,22.0f,24.0f,18.0f,8.0f,10.0f };
float HelyTrapz[7] = { 20.0f,17.0f,16.0f,18.0f,15.0f,19.0f,14.0f };
float Potalx[3] = { 28.0,-4.0 };
float Potalz[3] = { 21.0,30.0 };

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(Wwidth, Wheight);
	glutCreateWindow("TeamProject");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cerr << "fail Initialize" << endl;
	else cout << "Initialize" << endl;
	ObjList();

	makeShaderID();
	InitBuffer();
	initTexture();
	LocationRandom();
	glutDisplayFunc(MainView);
	glutReshapeFunc(Resize);
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
		for (int i = 0; i < 80; i++) {
			SLocation[i].y += SnowSpeed[i].y;
			if (SLocation[i].y >= 6.0f) {
				SLocation[i].y = SaveLocation[i].y;
			}

		}
	}


	if (JumpState == true)
	{

		if (jumpcheck == 0)
		{

			Scalepos.My = 0.0f;
			TransList.T_Bodyy += 0.05f;
			TransList.T_ArmLegy += 0.05f;
			TransList.T_Eyey += 0.05f;
			if (TransList.T_Bodyy >= 1.6f)
			{

				jumpcheck = 1;
			}
		}
		if (jumpcheck == 1)
		{

			TransList.T_Bodyy -= 0.05f;
			TransList.T_ArmLegy -= 0.05f;
			TransList.T_Eyey -= 0.05f;
			Scalepos.My -= 0.005f;
			if (Scalepos.My < -0.1f)
			{
				Scalepos.My += 0.005f;
			}

			if (TransList.T_Bodyy <= 0.7f)
			{
				jumpcheck = 0;

			}

		}


	}

	if (TrapJumpState == true)
	{
		for (size_t i = 0; i < 4; i++)
		{

			if (trapjumpcheck == 0)
			{

				radomcorail[0].y += 0.004f;
				radomcorail[1].y += 0.008f;
				radomcorail[2].y += 0.005f;
				radomcorail[3].y += 0.01f;
				radomcorail[4].y += 0.015f;
				radomcorail[5].y += 0.012f;
				if (radomcorail[i].y > 2.3234f)
				{

					trapjumpcheck = 1;
				}
			}
			if (trapjumpcheck == 1)
			{
				radomcorail[0].y -= 0.004f;
				radomcorail[1].y -= 0.008f;
				radomcorail[2].y -= 0.005f;
				radomcorail[3].y -= 0.01f;
				radomcorail[4].y -= 0.015f;
				radomcorail[5].y -= 0.012f;
				if (radomcorail[i].y < 0.7f)
				{

					trapjumpcheck = 0;

				}

			}
		}


	}

	if (Mainswingchk)
	{

		if (MainswingAngle1 == true) {
			AngleList.MainSwing1 += 2.0f;
			if (AngleList.MainSwing1 == 20.0f) {
				MainswingAngle1 = false;
			}
		}
		if (MainswingAngle1 == false) {
			AngleList.MainSwing1 -= 2.0f;
			if (AngleList.MainSwing1 == -20.0f) {
				MainswingAngle1 = true;
			}

		}
		if (MainswingAngle2 == true) {
			AngleList.MainSwing2 += 2.0f;

			if (AngleList.MainSwing2 == 20.0f) {
				MainswingAngle2 = false;
			}
		}
		if (MainswingAngle2 == false) {
			AngleList.MainSwing2 -= 2.0f;
			if (AngleList.MainSwing2 == -20.0f) {
				MainswingAngle2 = true;
			}

		}
	}

	if (TrapAction == true)
	{

		AngleList.AngleTrap -= 5.0f;
		for (int i = 0; i < 6; i++)
		{
			radomcorail[i].z -= 0.03f;

			if (radomcorail[i].z + 16.0f < -6.0f)
			{
				radomcorail[i].z = 0.0f;
			}

		}

	}

	if (TransList.T_Bodyz >= 15.0f)
	{
		TrapHelyAction = true;
	}
	if (TrapHelyAction == true)
	{
		AngleList.AngleTrap2 += 60.23234f;
	}


	if (Opencheck == true)
	{

		if (Door == true)
		{

			TransList.DoorxL += 0.01f;
			TransList.DoorxR -= 0.01f;
			Scalepos.Doorx -= 0.02f;
			if (TransList.DoorxR <= -3.0f && TransList.DoorxL >= 3.0f)
			{
				TransList.DoorxL -= 0.01f;
				TransList.DoorxR += 0.01f;
				Scalepos.Doorx += 0.02f;
				Door = false;
			}

		}


		if (Door == false)
		{
			TransList.DoorxL -= 0.01f;
			TransList.DoorxR += 0.01f;
			Scalepos.Doorx += 0.02f;
			if (TransList.DoorxR >= -2.1f && TransList.DoorxL <= 2.1f)
			{
				TransList.DoorxL += 0.01f;
				TransList.DoorxR -= 0.01f;
				Scalepos.Doorx -= 0.02f;
				Door = true;
			}

		}
	}

	if (PullTrapcheck == true)
	{
			//L
			if (PullTrapPoint == 0){
				PullTrapLx[0] -= 0.75;
				Scalepos.PullScaleLx[0]= 6.0f;
				if (PullTrapLx[0] <= -1.0f)
					PullTrapPoint = 1;
			}
			if (PullTrapPoint2 == 0){
				PullTrapLx[1] -= 0.6;
				Scalepos.PullScaleLx[1] = 6.0f;
				if (PullTrapLx[1] <= -1.0f)
					PullTrapPoint2 = 1;
			}
			if (PullTrapPoint3==0){
				PullTrapLx[2] -= 0.9;
				Scalepos.PullScaleLx[2] = 7.0f;
				if (PullTrapLx[2] <= -1.0f)
					PullTrapPoint3 =1;
			}

			if (PullTrapPoint == 1){	
				PullTrapLx[0] += 0.04;
				Scalepos.PullScaleLx[0] -= 0.02f;
				if (PullTrapLx[0] >= 3.0f)
					PullTrapPoint = 0;
			}

			if (PullTrapPoint2 == 1){
				PullTrapLx[1] += 0.04;
				Scalepos.PullScaleLx[1] -= 0.02f;
				if (PullTrapLx[1] >= 3.0f)
					PullTrapPoint2 =0;
			}

			if (PullTrapPoint3 == 1)	{
				PullTrapLx[2] += 0.04;
				Scalepos.PullScaleLx[2] -= 0.02f;
				if (PullTrapLx[2] >= 3.0f)
					PullTrapPoint3 = 0;
			}
				
			//R
			if (PullTrapPoint4 == 0) {
				PullTrapRx[0] += 0.8;
				Scalepos.PullScaleRx[0] = 7.0f;
				if (PullTrapRx[0] >= -1.0f)
					PullTrapPoint4 = 1;
			}
			if (PullTrapPoint5 == 0) {
				PullTrapRx[1] += 1.0;
				Scalepos.PullScaleRx[1] = 7.0f;
				if (PullTrapRx[1] >= -1.0f)
					PullTrapPoint5 = 1;
			}
			if (PullTrapPoint6 == 0) {
				PullTrapRx[2] += 0.65;
				Scalepos.PullScaleRx[2] = 7.0f;
				if (PullTrapRx[2] >= -1.0f)
					PullTrapPoint6 = 1;
			}

			if (PullTrapPoint4 == 1) {
				PullTrapRx[0] -= 0.04;
				Scalepos.PullScaleRx[0] -= 0.02f;
				if (PullTrapRx[0] <= -3.0f)
					PullTrapPoint4 = 0;
			}

			if (PullTrapPoint5 == 1) {
				PullTrapRx[1] -= 0.04;
				Scalepos.PullScaleRx[1] -= 0.02f;
				if (PullTrapRx[1] <= -3.0f)
					PullTrapPoint5 = 0;
			}

			if (PullTrapPoint6 == 1) {
				PullTrapRx[2] -= 0.04;
				Scalepos.PullScaleRx[2] -= 0.02f;
				if (PullTrapRx[2] <= -3.0f)
					PullTrapPoint6 = 0;
			}
		

	}
	
	AngleList.Radian += 20.234f;

	if (TransList.T_Bodyz >= TransList.T_StageZ-6.0f && TransList.T_Bodyz <= TransList.T_StageZ + 15.0f)
	{
		if (TransList.T_Bodyx >= TransList.T_StageX + 5.0f ||TransList.T_Bodyx <= TransList.T_StageX - 5.0f)
		{
			TransList.T_Bodyy -= 0.2f;
			TransList.T_ArmLegy -= 0.2f;
			TransList.T_Eyey -= 0.2f;
		}
	}

	if (TransList.T_Bodyz >= TransList.T_Stage2ZA[0]) {
		if (TransList.T_Bodyx >= TransList.T_Stage2X+5.0f || TransList.T_Bodyx <= TransList.T_Stage2X -5.0f)
		{
			TransList.T_Bodyy -= 0.2f;
			TransList.T_ArmLegy -= 0.2f;
			TransList.T_Eyey -= 0.2f;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(17, timer, value);
}

void MainView()
{
	glClearColor(0.9989, 0.9989, 0.9989, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	{
		glBindVertexArray(VAO[0]);
		unsigned int StartGroundBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(StartGroundBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 StartGround = glm::mat4(1.0f);
		unsigned int StartGroundNormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(StartGroundNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(StartGround));
		unsigned int cameraViewLocation = glGetUniformLocation(shaderID, "viewTransform");
		glUniformMatrix4fv(cameraViewLocation, 1, GL_FALSE, glm::value_ptr(StartGround));
		unsigned int cameraPosLocation = glGetUniformLocation(shaderID, "cameraPos");
		glUniform3fv(cameraPosLocation, 1, glm::value_ptr(glm::vec3(0, 0, 1)));
		unsigned int projectionLocation = glGetUniformLocation(shaderID, "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(StartGround));
		StartGround = glm::translate(StartGround, glm::vec3(0, 0, -1));
		StartGround = glm::rotate(StartGround, glm::radians(-90.0f), glm::vec3(1, 0, 0));
		StartGround = glm::scale(StartGround, glm::vec3(2, 2, 2));
		unsigned int backgroundMatrixLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(backgroundMatrixLocation, 1, GL_FALSE, glm::value_ptr(StartGround));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[0].size());
	}

	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderID);
	//------------------------------camera---------------------------------------------

	glm::vec3 ObjectCamerapos = glm::vec3(Camerapos.C_x - TransList.T_Bodyx, Camerapos.C_y + TransList.T_Bodyy, Camerapos.C_z - TransList.T_Bodyz);
	glm::mat4 CameraSpacepos = glm::mat4(1.0f);
	CameraSpacepos = glm::rotate(CameraSpacepos, glm::radians(AngleList.anglecamera), glm::vec3(0.0f, 1.0f, 0.0f));//����
	glm::vec3 Cameraposdir = glm::vec3(CameraSpacepos * glm::vec4(ObjectCamerapos, 1));
	glm::vec3 ObjectCameraPicking = glm::vec3(TransList.T_Bodyx, TransList.T_Bodyy, TransList.T_Bodyz);
	glm::vec3 ObjectCameradir = Cameraposdir - ObjectCameraPicking;
	glm::vec3 Up_y = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 CameraSpacedir = glm::mat4(1.0f);
	CameraSpacedir = glm::rotate(CameraSpacedir, glm::radians(AngleList.anglecamera2), glm::vec3(0.0f, 1.0f, 0.0f));//���� 
	glm::vec3 Cameradir = glm::vec3(CameraSpacedir * glm::vec4(-ObjectCameradir, 1));

	glm::vec3 Crosspos = glm::normalize(glm::cross(Up_y, glm::normalize(Cameradir)));
	glm::vec3 Cross = glm::cross(glm::normalize(Cameradir), Crosspos);

	glm::mat4 ObjView = glm::mat4(1.0f);
	ObjView = glm::lookAt(Cameraposdir, Cameradir + Cameraposdir, Cross);
	unsigned int ObjcameraViewLocation = glGetUniformLocation(shaderID, "viewTransform");
	glUniformMatrix4fv(ObjcameraViewLocation, 1, GL_FALSE, glm::value_ptr(ObjView));

	glm::vec3 CameraView;
	CameraView = glm::vec3(Cameraposdir);
	unsigned int ViewPositionLocation = glGetUniformLocation(shaderID, "camerapos");
	glUniform3fv(ViewPositionLocation, 1, glm::value_ptr(CameraView));

	//--------����
	glm::mat4 Proj = glm::mat4(1.0f);
	Proj = glm::perspective(glm::radians(60.0f), (float)Wwidth / Wheight, 0.1f, 100.0f);
	unsigned int ModelProjLocation = glGetUniformLocation(shaderID, "projectionTransform");
	glUniformMatrix4fv(ModelProjLocation, 1, GL_FALSE, &Proj[0][0]);


	//--------����
	glm::mat4 LightPosition = glm::mat4(1.0f);
	LightPosition = glm::rotate(LightPosition, glm::radians(AngleList.LightRadian), glm::vec3(0.0f, 1.0f, 0.0f));
	LightPosition = glm::translate(LightPosition, glm::vec3(Scalepos.X, Scalepos.Y, Scalepos.Z - 1.0f));
	unsigned int lightPosLocation = glGetUniformLocation(shaderID, "LightPos");
	glUniform3fv(lightPosLocation, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	unsigned int lightColorLocation = glGetUniformLocation(shaderID, "LightColor");
	glUniform3fv(lightColorLocation, 1, glm::value_ptr(lightColor));
	unsigned int LightTransformLocation = glGetUniformLocation(shaderID, "LightTransform");
	glUniformMatrix4fv(LightTransformLocation, 1, GL_FALSE, glm::value_ptr(LightPosition));


	drawscene();
	glutSwapBuffers();
}

void Resize(int w, int h)
{
	glViewport(0, 0, w, h);
	Wwidth = w;
	Wheight = h;
}

void keyboardCall(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'w':
		Mainswingchk = 1;
		AngleList.BodyAngle = Movevalue;
		AngleList.LegAngle = Movevalue;
		TransList.T_Eyez += Movevalue;
		TransList.T_Bodyz += Movevalue;
		TransList.T_ArmLegz += Movevalue;

		if (TransList.T_Bodyz > TransList.T_StageZ + 70.0f && TransList.T_Bodyz < TransList.T_StageZ + 85.0f)
		{

			TransList.T_Eyez += Movevalue;
			TransList.T_Bodyz += Movevalue;
			TransList.T_ArmLegz += Movevalue;
			TransList.T_Bodyy += Movevalue;
			TransList.T_ArmLegy += Movevalue;
			TransList.T_Eyey += Movevalue;
		}
		break;

	case's':
		Mainswingchk = 1;
		AngleList.BodyAngle = 180.0f;
		AngleList.LegAngle = 0.0f;
		TransList.T_Eyez -= Movevalue;
		TransList.T_Bodyz -= Movevalue;
		TransList.T_ArmLegz -= Movevalue;
		TransList.T_Cpaez -= Movevalue;
		if (TransList.T_Bodyz > TransList.T_StageZ + 70.0f && TransList.T_Bodyz < TransList.T_StageZ + 85.0f)
		{

			TransList.T_Eyez -= Movevalue;
			TransList.T_Bodyz -= Movevalue;
			TransList.T_ArmLegz -= Movevalue;
			TransList.T_Bodyy -= Movevalue;
			TransList.T_ArmLegy -= Movevalue;
			TransList.T_Eyey -= Movevalue;
		}
		break;

	case'a':
		Mainswingchk = 2;
		AngleList.BodyAngle = 90.0f;
		AngleList.LegAngle = 180.0f;
		TransList.T_Eyex += Movevalue;
		TransList.T_Bodyx += Movevalue;
		TransList.T_ArmLegx += Movevalue;
		break;

	case'd':
		Mainswingchk = 2;
		AngleList.BodyAngle = 270.0f;
		AngleList.LegAngle = 180.0f;
		TransList.T_Eyex -= Movevalue;
		TransList.T_Bodyx -= Movevalue;
		TransList.T_ArmLegx -= Movevalue;
		break;

	case'z':
		cameraPos.y += 0.1f;
		break;

	case'Z':
		AngleList.anglecamera += 3.0f;
		break;

	case'c':
		selectLightColor++;
		lightColor = lightColorKind[selectLightColor % 4];
		break;
	case'r':
		AngleList.ArmAngle += 1.0f;
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
	case 'j': //special
		JumpState = true;
		jumpcheck = 0;
		break;
	case 'N': //special
		AngleList.StageAngle += 5.0f;
		AngleList.StageAngle2 += 5.0f;
		break;



	}
	glutPostRedisplay();
}





void InitBuffer()
{
	glGenVertexArrays(24, VAO);

	for (int i = 0; i < 23; i++)
	{
		glBindVertexArray(VAO[i]);
		glGenBuffers(3, &VBO[3 * i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[3 * i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Vertex[i].size(), &Vertex[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[3 * i + 1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Nomal[i].size(), &Nomal[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[3 * i + 2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * Texture[i].size(), &Texture[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
		glEnableVertexAttribArray(2);

	}

}

void ObjList()
{
	readTriangleObj("plane3.obj", Vertex[0], Texture[0], Nomal[0]);
	readTriangleObj("plane3.obj", Vertex[9], Texture[9], Nomal[9]);


	readTriangleObj("cube3_.obj", Vertex[2], Texture[2], Nomal[2]);
	readTriangleObj("Sphere2.obj", Vertex[3], Texture[3], Nomal[3]);
	readTriangleObj("plane3.obj", Vertex[4], Texture[4], Nomal[4]);

	readTriangleObj("Sphere2.obj", Vertex[1], Texture[1], Nomal[1]);
	for (int i = 5; i < 9; i++)
	{
		readTriangleObj("Sphere2.obj", Vertex[i], Texture[i], Nomal[i]);
	}
	for (int i = 10; i < 13; i++)
	{
		readTriangleObj("Sphere2.obj", Vertex[i], Texture[i], Nomal[i]);
	}

	readTriangleObj("hely.obj", Vertex[13], Texture[13], Nomal[13]);
	readTriangleObj("hely.obj", Vertex[14], Texture[14], Nomal[14]);
	readTriangleObj("cube3_.obj", Vertex[15], Texture[15], Nomal[15]);
	readTriangleObj("cube3_.obj", Vertex[16], Texture[16], Nomal[16]);
	readTriangleObj("hely.obj", Vertex[17], Texture[17], Nomal[17]);
	readTriangleObj("crown.obj", Vertex[18], Texture[18], Nomal[18]);
	readTriangleObj("sword.obj", Vertex[19], Texture[19], Nomal[19]);

	readTriangleObj("plane3.obj", Vertex[20], Texture[20], Nomal[20]);
	readTriangleObj("cube3_.obj", Vertex[21], Texture[21], Nomal[21]);
	readTriangleObj("cube3_.obj", Vertex[22], Texture[22], Nomal[22]);
	//readTriangleObj("countingstar.obj", Vertex[23], Texture[23], Nomal[23]);
}

void drawscene()
{
	glUseProgram(shaderID);

	for (int i = 0; i < 200; i++)
	{
		glBindVertexArray(VAO[3]);
		unsigned int snowBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(snowBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glm::mat4 Snow = glm::mat4(1.0f);
		Snow = glm::translate(Snow, glm::vec3(SLocation[i].x, SLocation[i].y, SLocation[i].z));
		Snow = glm::scale(Snow, glm::vec3(0.03f, 0.03f, 0.03f));
		unsigned int SnowLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(SnowLocation, 1, GL_FALSE, glm::value_ptr(Snow));
		glm::mat4 SnowNormalmodel = glm::mat4(1.0f);
		SnowNormalmodel = glm::translate(SnowNormalmodel, glm::vec3(SLocation[i].x, SLocation[i].y, SLocation[i].z));
		unsigned int SnowNormalmodelLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(SnowNormalmodelLocation, 1, GL_FALSE, glm::value_ptr(SnowNormalmodel));
		unsigned int SnowColorLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(SnowColorLocation, 1, 0.388235, 0.278431);
		glDrawArrays(GL_TRIANGLES, 0, Vertex[3].size());
	}


	//for (int i = 0; i < 15; i++)
	//{
	/*	glBindVertexArray(VAO[23]);
		unsigned int StarBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(StarBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glm::mat4 Star = glm::mat4(1.0f);
		Star = glm::translate(Star, glm::vec3(0.0,0.0,0.0));
		Star = glm::scale(Star, glm::vec3(1.0f, 1.0f, 1.0f));
		unsigned int StarLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(StarLocation, 1, GL_FALSE, glm::value_ptr(Star));
		glm::mat4 StarNormalmodel = glm::mat4(1.0f);
		StarNormalmodel = glm::translate(StarNormalmodel, glm::vec3(0.0,0.0,0.0));
		unsigned int StarNormalmodelLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(StarNormalmodelLocation, 1, GL_FALSE, glm::value_ptr(StarNormalmodel));
		unsigned int StarColorLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(StarColorLocation, 1, 0.388235, 0.278431);
		glDrawArrays(GL_TRIANGLES, 0, Vertex[23].size());*/
	//}

	//--------STAGE1
	{
		glBindVertexArray(VAO[4]);
		unsigned int StageBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(StageBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 StageTrasMatrix = glm::mat4(1.0f);
		StageTrasMatrix = glm::translate(StageTrasMatrix, glm::vec3(TransList.T_StageX + 17.0f, TransList.T_StageY, TransList.T_StageZ + 18.0f));
		StageTrasMatrix = glm::rotate(StageTrasMatrix, glm::radians(AngleList.StageAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		StageTrasMatrix = glm::scale(StageTrasMatrix, glm::vec3(24.0, 1.0, 10.0));
		unsigned int StageTransMatrixLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(StageTransMatrixLocation, 1, GL_FALSE, glm::value_ptr(StageTrasMatrix));
		glm::mat4 StageNormalMatrix = glm::mat4(1.0f);
		unsigned int StageNormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(StageNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(StageNormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[4].size());

		glBindVertexArray(VAO[9]);
		unsigned int Stage1BlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(Stage1BlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 Stage1TrasMatrix = glm::mat4(1.0f);
		Stage1TrasMatrix = glm::translate(Stage1TrasMatrix, glm::vec3(TransList.T_StageX, TransList.T_StageY, TransList.T_StageZ + 8.0f));
		Stage1TrasMatrix = glm::rotate(Stage1TrasMatrix, glm::radians(AngleList.StageAngle2), glm::vec3(0.0f, 1.0f, 0.0f));
		Stage1TrasMatrix = glm::scale(Stage1TrasMatrix, glm::vec3(10.0, 1.0, 30.0f));
		unsigned int Stage1TransMatrixLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(Stage1TransMatrixLocation, 1, GL_FALSE, glm::value_ptr(Stage1TrasMatrix));
		glm::mat4 Stage1NormalMatrix = glm::mat4(1.0f);
		unsigned int Stage1NormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(Stage1NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(Stage1NormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[9].size());

		glBindVertexArray(VAO[15]);
		unsigned int DoorBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(DoorBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 DoorTrasMatrix = glm::mat4(1.0f);
		DoorTrasMatrix = glm::translate(DoorTrasMatrix, glm::vec3(TransList.DoorxL + 0.5f, TransList.T_StageY + 1.0f, TransList.T_StageZ + 32.0f));
		DoorTrasMatrix = glm::scale(DoorTrasMatrix, glm::vec3(Scalepos.Doorx, 3.0, 0.5f));
		unsigned int DoorTransMatrixLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(DoorTransMatrixLocation, 1, GL_FALSE, glm::value_ptr(DoorTrasMatrix));
		glm::mat4 DoorNormalMatrix = glm::mat4(1.0f);
		unsigned int DoorNormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(DoorNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(DoorNormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[15].size());

		glBindVertexArray(VAO[16]);
		unsigned int Door2BlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(Door2BlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 Door2TrasMatrix = glm::mat4(1.0f);
		Door2TrasMatrix = glm::translate(Door2TrasMatrix, glm::vec3(TransList.DoorxR - 0.5f, TransList.T_StageY + 1.0f, TransList.T_StageZ + 32.0f));
		Door2TrasMatrix = glm::scale(Door2TrasMatrix, glm::vec3(Scalepos.Doorx, 3.0, 0.5f));
		unsigned int Door2TransMatrixLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(Door2TransMatrixLocation, 1, GL_FALSE, glm::value_ptr(Door2TrasMatrix));
		glm::mat4 Door2NormalMatrix = glm::mat4(1.0f);
		unsigned int Door2NormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(Door2NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(Door2NormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[16].size());

		if ((TransList.DoorxR + 2.0f >= TransList.T_Bodyx && (TransList.T_StageZ + 32.0f) - 1.0f <= TransList.T_Bodyz && (TransList.T_StageZ + 32.0f) + 1.0f >= TransList.T_Bodyz)
			|| (TransList.DoorxL - 2.0f <= TransList.T_Bodyx && (TransList.T_StageZ + 32.0f) - 1.0f <= TransList.T_Bodyz && (TransList.T_StageZ + 32.0f) + 1.0f >= TransList.T_Bodyz))
		{
			TransList.T_Bodyz -= 0.05f;
			TransList.T_ArmLegz -= 0.05f;
			TransList.T_Eyez -= 0.05f;
		}
	}



	//----------STAGE2
	{

		glBindVertexArray(VAO[4]);
		for (size_t i = 0; i < 3; i++)
		{
		unsigned int StageBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(StageBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 StageTrasMatrix = glm::mat4(1.0f);
		StageTrasMatrix = glm::translate(StageTrasMatrix, glm::vec3(TransList.T_Stage2X, TransList.T_Stage2Y, TransList.T_Stage2ZA[i]));
		StageTrasMatrix = glm::rotate(StageTrasMatrix, glm::radians(AngleList.StageAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		StageTrasMatrix = glm::scale(StageTrasMatrix, glm::vec3(11.0, 1.0, 15.0));
		unsigned int StageTransMatrixLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(StageTransMatrixLocation, 1, GL_FALSE, glm::value_ptr(StageTrasMatrix));
		glm::mat4 StageNormalMatrix = glm::mat4(1.0f);
		unsigned int StageNormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(StageNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(StageNormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[4].size());
		}

		glBindVertexArray(VAO[9]);
		unsigned int Stage1BlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(Stage1BlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 Stage1TrasMatrix = glm::mat4(1.0f);
		Stage1TrasMatrix = glm::translate(Stage1TrasMatrix, glm::vec3(TransList.T_Stage2X, TransList.T_Stage2Y + 2.5f, TransList.T_Stage2Z + 76.0f));
		Stage1TrasMatrix = glm::rotate(Stage1TrasMatrix, glm::radians(AngleList.StageAngle2 - 31.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		Stage1TrasMatrix = glm::scale(Stage1TrasMatrix, glm::vec3(11.0, 2.0, 10.0f));
		unsigned int Stage1TransMatrixLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(Stage1TransMatrixLocation, 1, GL_FALSE, glm::value_ptr(Stage1TrasMatrix));
		glm::mat4 Stage1NormalMatrix = glm::mat4(1.0f);
		unsigned int Stage1NormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(Stage1NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(Stage1NormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[9].size());

		glBindVertexArray(VAO[20]);
		unsigned int Stage1BlendCheck2 = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(Stage1BlendCheck2, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 Stage1TrasMatrix2 = glm::mat4(1.0f);
		Stage1TrasMatrix2 = glm::translate(Stage1TrasMatrix2, glm::vec3(TransList.T_Stage2X - 5.5f, TransList.T_Stage2Y + 4.8f, TransList.T_Stage2Z + 85));
		Stage1TrasMatrix2 = glm::scale(Stage1TrasMatrix2, glm::vec3(20.0, 1.0, 11.0f));
		unsigned int Stage1TransMatrixLocation2 = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(Stage1TransMatrixLocation2, 1, GL_FALSE, glm::value_ptr(Stage1TrasMatrix2));
		glm::mat4 Stage2NormalMatrix2 = glm::mat4(1.0f);
		unsigned int Stage1NormalMatrixLocation2 = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(Stage1NormalMatrixLocation2, 1, GL_FALSE, glm::value_ptr(Stage2NormalMatrix2));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[20].size());
	}



	glBindVertexArray(VAO[1]);
	unsigned int BODYBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
	glUniform1i(BODYBlendCheck, 0);
	glm::mat4 BODY = glm::mat4(1.0f);
	BODY = glm::translate(BODY, glm::vec3(TransList.T_Bodyx, TransList.T_Bodyy - 0.2f, TransList.T_Bodyz));
	BODY = glm::rotate(BODY, glm::radians(AngleList.BodyAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	BODY = glm::scale(BODY, glm::vec3(0.3f, Scalepos.My + 0.4, 0.3f));
	unsigned int BODYLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(BODYLocation, 1, GL_FALSE, glm::value_ptr(BODY));
	glm::mat4 BODYNormal = glm::mat4(1.0f);
	BODYNormal = glm::rotate(BODYNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int BODYNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(BODYNormalLocation, 1, GL_FALSE, glm::value_ptr(BODYNormal));
	unsigned int BODYfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(BODYfragLocation, 0.847f, 0.45f, 0.628f);
	glDrawArrays(GL_TRIANGLES, 0, Vertex[1].size());


	glBindVertexArray(VAO[5]);
	unsigned int ArmLegBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
	glUniform1i(ArmLegBlendCheck, 0);
	glm::mat4 LEFTARM = glm::mat4(1.0f);
	LEFTARM = glm::translate(LEFTARM, glm::vec3(TransList.T_ArmLegx + 0.18f, TransList.T_ArmLegy - 0.2f, TransList.T_ArmLegz - 2.15f));
	if (Mainswingchk == 1) {
		LEFTARM = glm::rotate(LEFTARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 0.0f, 1.0f));
		LEFTARM = glm::translate(LEFTARM, glm::vec3(0.16f, 0.0f, 0.2f));
		LEFTARM = glm::rotate(LEFTARM, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Mainswingchk == 2) {
		LEFTARM = glm::translate(LEFTARM, glm::vec3(-0.16f, 0.1f, -0.1f));
		LEFTARM = glm::rotate(LEFTARM, glm::radians(AngleList.ArmAngle + 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		LEFTARM = glm::rotate(LEFTARM, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	LEFTARM = glm::scale(LEFTARM, glm::vec3(Scalepos.ALx, Scalepos.ALy, Scalepos.ALz));
	unsigned int LEFTARMLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(LEFTARMLocation, 1, GL_FALSE, glm::value_ptr(LEFTARM));
	glm::mat4 LEFTARMNormal = glm::mat4(1.0f);
	LEFTARMNormal = glm::rotate(LEFTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int LEFTARMNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(LEFTARMNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTARMNormal));
	unsigned int LEFTARMfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(LEFTARMfragLocation, 0.847f, 0.45f, 0.628f);
	glDrawArrays(GL_TRIANGLES, 0, Vertex[5].size());


	glBindVertexArray(VAO[6]);
	unsigned int ArmLeg2BlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
	glUniform1i(ArmLeg2BlendCheck, 0);
	glm::mat4 RIGHTARM = glm::mat4(1.0f);
	RIGHTARM = glm::translate(RIGHTARM, glm::vec3(TransList.T_ArmLegx - 0.18f, TransList.T_ArmLegy - 0.2f, TransList.T_ArmLegz - 2.15f));
	if (Mainswingchk == 1) {
		RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.ArmAngle - 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		RIGHTARM = glm::translate(RIGHTARM, glm::vec3(-0.16f, 0.0f, 0.2f));
		RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Mainswingchk == 2) {
		RIGHTARM = glm::translate(RIGHTARM, glm::vec3(0.16f, 0.1f, 0.4f));
		RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.ArmAngle + 270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	RIGHTARM = glm::scale(RIGHTARM, glm::vec3(Scalepos.ALx, Scalepos.ALy, Scalepos.ALz));
	unsigned int RIGHTARMLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(RIGHTARMLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARM));
	glm::mat4 RIGHTARMNormal = glm::mat4(1.0f);
	RIGHTARMNormal = glm::rotate(RIGHTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int RIGHTARMNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(RIGHTARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARMNormal));
	unsigned int RIGHTARMfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(RIGHTARMfragLocation, 0.847f, 0.45f, 0.628f);
	glDrawArrays(GL_TRIANGLES, 0, Vertex[6].size());


	glBindVertexArray(VAO[7]);
	unsigned int ArmLeg3BlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
	glUniform1i(ArmLeg3BlendCheck, 0);
	glm::mat4 LEFTLEG = glm::mat4(1.0f);
	LEFTLEG = glm::translate(LEFTLEG, glm::vec3(TransList.T_ArmLegx + 0.03f, TransList.T_ArmLegy - 0.5f, TransList.T_ArmLegz - 2.1f));
	if (Mainswingchk == 1) {
		LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.LegAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		LEFTLEG = glm::translate(LEFTLEG, glm::vec3(0.08f, 0.0f, 0.1f));
		LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Mainswingchk == 2) {
		LEFTLEG = glm::translate(LEFTLEG, glm::vec3(0.0f, 0.0f, 0.0f));
		LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.LegAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	LEFTLEG = glm::scale(LEFTLEG, glm::vec3(Scalepos.ALx, Scalepos.ALy, Scalepos.ALz));
	unsigned int LEFTLEGLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(LEFTLEGLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEG));
	glm::mat4 LEFTLEGNormal = glm::mat4(1.0f);
	LEFTLEGNormal = glm::rotate(LEFTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int LEFTLEGNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(LEFTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEGNormal));
	unsigned int LEFTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(LEFTLEGfragLocation, 0.847f, 0.45f, 0.628f);
	glDrawArrays(GL_TRIANGLES, 0, Vertex[7].size());


	glBindVertexArray(VAO[8]);
	unsigned int ArmLeg4BlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
	glUniform1i(ArmLeg4BlendCheck, 0);
	glm::mat4 RIGHTLEG = glm::mat4(1.0f);
	RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(TransList.T_ArmLegx - 0.03f, TransList.T_ArmLegy - 0.5f, TransList.T_ArmLegz - 2.1f));

	if (Mainswingchk == 1) {
		RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.LegAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(-0.08f, 0.0f, 0.1f));
		RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Mainswingchk == 2) {
		RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(0.0f, 0.0f, 0.2f));
		RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.LegAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	RIGHTLEG = glm::scale(RIGHTLEG, glm::vec3(Scalepos.ALx, Scalepos.ALy, Scalepos.ALz));
	unsigned int RIGHTLEGLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(RIGHTLEGLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEG));
	glm::mat4 RIGHTLEGNormal = glm::mat4(1.0f);
	RIGHTLEGNormal = glm::rotate(RIGHTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int RIGHTLEGNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(RIGHTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEGNormal));
	unsigned int RIGHTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(RIGHTLEGfragLocation, 0.847f, 0.45f, 0.628f);
	glDrawArrays(GL_TRIANGLES, 0, Vertex[8].size());

	glBindVertexArray(VAO[10]);
	unsigned int EYEBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
	glUniform1i(EYEBlendCheck, 0);
	glm::mat4 EYE = glm::mat4(1.0f);
	EYE = glm::rotate(EYE, glm::radians(AngleList.EyeAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	if (AngleList.BodyAngle == 0.0f)
		EYE = glm::translate(EYE, glm::vec3(TransList.T_Eyex - 0.1f, TransList.T_Eyey, TransList.T_Eyez + 0.25f));
	if (AngleList.BodyAngle == 180.0f)
		EYE = glm::translate(EYE, glm::vec3(TransList.T_Eyex - 0.1f, TransList.T_Eyey, TransList.T_Eyez - 0.25f));
	if (AngleList.BodyAngle == 90.0f)
		EYE = glm::translate(EYE, glm::vec3(TransList.T_Eyex + 0.25f, TransList.T_Eyey, TransList.T_Eyez - 0.1f));
	if (AngleList.BodyAngle == 270.0f)
		EYE = glm::translate(EYE, glm::vec3(TransList.T_Eyex - 0.25f, TransList.T_Eyey, TransList.T_Eyez + 0.1f));
	EYE = glm::scale(EYE, glm::vec3(0.04f, 0.04f, 0.04f));
	unsigned int EYELocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(EYELocation, 1, GL_FALSE, glm::value_ptr(EYE));
	glm::mat4 EYENormal = glm::mat4(1.0f);
	BODYNormal = glm::rotate(EYENormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int EYENormalLocation = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(EYENormalLocation, 1, GL_FALSE, glm::value_ptr(EYENormal));
	unsigned int EYEfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(EYEfragLocation, 0.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, Vertex[10].size());

	glBindVertexArray(VAO[11]);
	unsigned int EYEBlendCheck2 = glGetUniformLocation(shaderID, "Blendcheck");
	glUniform1i(EYEBlendCheck2, 0);
	glm::mat4 EYE2 = glm::mat4(1.0f);
	EYE2 = glm::rotate(EYE2, glm::radians(AngleList.EyeAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	if (AngleList.BodyAngle == 0.0f)
		EYE2 = glm::translate(EYE2, glm::vec3(TransList.T_Eyex + 0.1f, TransList.T_Eyey, TransList.T_Eyez + 0.25f));
	if (AngleList.BodyAngle == 180.0f)
		EYE2 = glm::translate(EYE2, glm::vec3(TransList.T_Eyex + 0.1f, TransList.T_Eyey, TransList.T_Eyez - 0.25f));
	if (AngleList.BodyAngle == 90.0f)
		EYE2 = glm::translate(EYE2, glm::vec3(TransList.T_Eyex + 0.25f, TransList.T_Eyey, TransList.T_Eyez + 0.125f));
	if (AngleList.BodyAngle == 270.0f)
		EYE2 = glm::translate(EYE2, glm::vec3(TransList.T_Eyex - 0.25f, TransList.T_Eyey, TransList.T_Eyez - 0.125f));
	EYE2 = glm::scale(EYE2, glm::vec3(0.04f, 0.04f, 0.04f));
	unsigned int EYELocation2 = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(EYELocation2, 1, GL_FALSE, glm::value_ptr(EYE2));
	glm::mat4 EYENormal2 = glm::mat4(1.0f);
	EYENormal2 = glm::rotate(EYENormal2, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int EYENormalLocation2 = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(EYENormalLocation2, 1, GL_FALSE, glm::value_ptr(EYENormal2));
	unsigned int EYEfragLocation2 = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(EYEfragLocation2, 0.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, Vertex[11].size());

	glBindVertexArray(VAO[18]);
	unsigned int ClownBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
	glUniform1i(ClownBlendCheck, 0);
	glm::mat4 Clown = glm::mat4(1.0f);
	Clown = glm::translate(Clown, glm::vec3(TransList.T_Bodyx, TransList.T_Bodyy + 0.1f, TransList.T_Bodyz));
	Clown = glm::rotate(Clown, glm::radians(AngleList.BodyAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	Clown = glm::scale(Clown, glm::vec3(3.0f, Scalepos.My + 3.0f, 3.0f));
	unsigned int ClownLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(ClownLocation, 1, GL_FALSE, glm::value_ptr(Clown));
	glm::mat4 ClownNormal = glm::mat4(1.0f);
	ClownNormal = glm::rotate(ClownNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int ClownNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(ClownNormalLocation, 1, GL_FALSE, glm::value_ptr(ClownNormal));
	unsigned int ClownfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(ClownfragLocation, 0.980392, 0.980392, 0.823529);
	glDrawArrays(GL_TRIANGLES, 0, Vertex[18].size());

	//-------Blank VAO
	glBindVertexArray(VAO[19]);
	unsigned int CapeBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
	glUniform1i(CapeBlendCheck, 0);

	glm::mat4 Cape = glm::mat4(1.0f);
	Cape = glm::translate(Cape, glm::vec3(TransList.T_Bodyx, TransList.T_Bodyy + 1.1f, TransList.T_Bodyz));
	Cape = glm::rotate(Cape, glm::radians(AngleList.BodyAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	Cape = glm::scale(Cape, glm::vec3(3.0f, 3.0f, 3.5f));
	unsigned int CapeLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(CapeLocation, 1, GL_FALSE, glm::value_ptr(Cape));
	glm::mat4 CapeNormal = glm::mat4(1.0f);
	CapeNormal = glm::rotate(CapeNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int CapeNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(CapeNormalLocation, 1, GL_FALSE, glm::value_ptr(CapeNormal));

	glDrawArrays(GL_TRIANGLES, 0, Vertex[19].size());

	//--------------TRAP
	for (int i = 0; i < 6; i++)
	{

		glBindVertexArray(VAO[12]);
		unsigned int RECOILBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(RECOILBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glm::mat4 RECOIL = glm::mat4(1.0f);
		RECOIL = glm::translate(RECOIL, glm::vec3(radomcorail[i].x, radomcorail[i].y, radomcorail[i].z + 16.0));
		RECOIL = glm::rotate(RECOIL, glm::radians(AngleList.AngleTrap), glm::vec3(1.0f, 0.0f, 0.0f));
		RECOIL = glm::scale(RECOIL, glm::vec3(0.6f, Scalepos.TSy, 0.6f));
		unsigned int RECOILLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(RECOILLocation, 1, GL_FALSE, glm::value_ptr(RECOIL));
		glm::mat4 RECOILNormal = glm::mat4(1.0f);
		RECOILNormal = glm::rotate(RECOILNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RECOILNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(RECOILNormalLocation, 1, GL_FALSE, glm::value_ptr(RECOILNormal));
		unsigned int RECOILfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RECOILfragLocation, 0.6f, 0.45f, 0.65f);
		glDrawArrays(GL_TRIANGLES, 0, Vertex[12].size());
		if ((radomcorail[i].z + 16.0f) - 0.6f <= TransList.T_Bodyz && (radomcorail[i].z + 16.0f) + 0.6f >= TransList.T_Bodyz && radomcorail[i].x + 0.6 >= TransList.T_Bodyx && radomcorail[i].x - 0.6 <= TransList.T_Bodyx)
		{
			TransList.T_Bodyz -= 0.2f;
			TransList.T_ArmLegz -= 0.2f;
			TransList.T_Eyez -= 0.2f;

		}
	}

	for (int i = 0; i < 7; i++)
	{
		glBindVertexArray(VAO[13]);
		unsigned int HELYCOPBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(HELYCOPBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 HELYCOP = glm::mat4(1.0f);
		HELYCOP = glm::translate(HELYCOP, glm::vec3(HelyTrapx[i], TransList.T_Trapy2, HelyTrapz[i] + 0.2f));
		HELYCOP = glm::rotate(HELYCOP, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		HELYCOP = glm::rotate(HELYCOP, glm::radians(AngleList.AngleTrap2), glm::vec3(0.0f, 1.0f, 0.0f));
		HELYCOP = glm::scale(HELYCOP, glm::vec3(2.0f, 2.0f, 2.0f));
		unsigned int HELYCOPLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(HELYCOPLocation, 1, GL_FALSE, glm::value_ptr(HELYCOP));
		glm::mat4 HELYCOPNormal = glm::mat4(1.0f);
		HELYCOPNormal = glm::rotate(HELYCOPNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 0.0f, 1.0f));
		unsigned int HELYCOPNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(HELYCOPNormalLocation, 1, GL_FALSE, glm::value_ptr(HELYCOPNormal));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[13].size());

		glBindVertexArray(VAO[14]);
		unsigned int HELYCOPBlendCheck2 = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(HELYCOPBlendCheck2, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glm::mat4 HELYCOPROW = glm::mat4(1.0f);
		HELYCOPROW = glm::translate(HELYCOPROW, glm::vec3(HelyTrapx[i], TransList.T_Trapy2, HelyTrapz[i]));
		HELYCOPROW = glm::rotate(HELYCOPROW, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		HELYCOPROW = glm::rotate(HELYCOPROW, glm::radians(AngleList.AngleTrap2), glm::vec3(0.0f, 1.0f, 0.0f));
		HELYCOPROW = glm::scale(HELYCOPROW, glm::vec3(0.15f, 0.15f, 2.0f));
		unsigned int HELYCOPROWLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(HELYCOPROWLocation, 1, GL_FALSE, glm::value_ptr(HELYCOPROW));
		glm::mat4 HELYCOPROWNormal = glm::mat4(1.0f);
		HELYCOPROWNormal = glm::rotate(HELYCOPROWNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int HELYCOPROWNormalLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(HELYCOPROWNormalLocation, 1, GL_FALSE, glm::value_ptr(HELYCOPROWNormal));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[14].size());
		if (TransList.T_Bodyx >= HelyTrapx[i] - 3.0f && TransList.T_Bodyx <= HelyTrapx[i] + 0.5f && HelyTrapz[i] - 1.0 <= TransList.T_Bodyz && HelyTrapz[i] + 1.0 >= TransList.T_Bodyz)
		{
			TransList.T_Bodyx -= 0.02f;
			TransList.T_ArmLegx -= 0.02f;
			TransList.T_Eyex -= 0.02f;
		}
	}

	for (size_t i = 0; i < 3; i++)
	{


		glBindVertexArray(VAO[21]);
		unsigned int PullTrapBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(PullTrapBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 PullTrap = glm::mat4(1.0f);
		PullTrap = glm::translate(PullTrap, glm::vec3(PullTrapLx[i], TransList.T_StageY + 1.0f, PullTrapLz[i]));
		PullTrap = glm::scale(PullTrap, glm::vec3(Scalepos.PullScaleLx[i], Scalepos.PullScaleLy, Scalepos.PullScaleLz));
		unsigned int PullTrapLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(PullTrapLocation, 1, GL_FALSE, glm::value_ptr(PullTrap));
		glm::mat4 PullTrapNormalMatrix = glm::mat4(1.0f);
		unsigned int PullTrapNormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(PullTrapNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(PullTrapNormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[21].size());

		glBindVertexArray(VAO[22]);
		unsigned int PullTrap2Check = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(PullTrap2Check, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 PullTrap2Matrix = glm::mat4(1.0f);
		PullTrap2Matrix = glm::translate(PullTrap2Matrix, glm::vec3(PullTrapRx[i], TransList.T_StageY + 1.0f, PullTrapRz[i]));
		PullTrap2Matrix = glm::scale(PullTrap2Matrix, glm::vec3(Scalepos.PullScaleRx[i], Scalepos.PullScaleRy, Scalepos.PullScaleRz));
		unsigned int PullTrap2Location = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(PullTrap2Location, 1, GL_FALSE, glm::value_ptr(PullTrap2Matrix));
		glm::mat4 PullTrap2NormalMatrix = glm::mat4(1.0f);
		unsigned int PullTrap2NormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(PullTrap2NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(PullTrap2NormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[22].size());

		if (PullTrapRx[i] + 4.0f >= TransList.T_Bodyx && PullTrapRz[i] - 0.5f <= TransList.T_Bodyz && PullTrapRz[i] + 0.5f >= TransList.T_Bodyz)
		{
				TransList.T_Bodyx += 0.7f;
				TransList.T_ArmLegx += 0.7f;
				TransList.T_Eyex += 0.7f;
		}
		if (PullTrapLx[i] - 4.0f <= TransList.T_Bodyx && PullTrapLz[i] - 0.5f <= TransList.T_Bodyz && PullTrapLz[i] + 0.5f >= TransList.T_Bodyz)
		{
			TransList.T_Bodyx -= 0.7f;
			TransList.T_ArmLegx -= 0.7f;
			TransList.T_Eyex -= 0.7f;
		}
	
	}



	//---potal
	glBindVertexArray(VAO[17]);
	for (size_t i = 0; i < 2; i++)
	{
		unsigned int FlagBlendCheck = glGetUniformLocation(shaderID, "Blendcheck");
		glUniform1i(FlagBlendCheck, 2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glUniform1i(glGetUniformLocation(shaderID, "textureC"), 0);
		glm::mat4 FlagTrasMatrix = glm::mat4(1.0f);
		FlagTrasMatrix = glm::translate(FlagTrasMatrix, glm::vec3(Potalx[i], TransList.T_StageY, Potalz[i]));
		FlagTrasMatrix = glm::rotate(FlagTrasMatrix, glm::radians(AngleList.Radian), glm::vec3(0.0f, 1.0f, 0.0f));
		FlagTrasMatrix = glm::scale(FlagTrasMatrix, glm::vec3(1.0f, 1.0, 1.0f));
		unsigned int FlagTransMatrixLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(FlagTransMatrixLocation, 1, GL_FALSE, glm::value_ptr(FlagTrasMatrix));
		glm::mat4 FlagNormalMatrix = glm::mat4(1.0f);
		unsigned int FlagNormalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
		glUniformMatrix4fv(FlagNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(FlagNormalMatrix));
		glDrawArrays(GL_TRIANGLES, 0, Vertex[17].size());
		if (TransList.T_Bodyz >= (TransList.T_StageZ + 21.0f) - 0.5f && TransList.T_Bodyz <= (TransList.T_StageZ + 21.0f) + 0.5f &&
			TransList.T_Bodyx >= (TransList.T_StageX + 28.0f) - 0.5f && TransList.T_Bodyx <= (TransList.T_StageX + 28.0f) + 0.5f)
		{
			TransList.T_Bodyx = Potalx[1];
			TransList.T_ArmLegx = Potalx[1];
			TransList.T_Eyex = Potalx[1];
			TransList.T_Bodyz = Potalz[1];
			TransList.T_ArmLegz = TransList.T_Bodyz + 2.0f;
			TransList.T_Eyez = TransList.T_Bodyz;
			AngleList.anglecamera += 15.0f;
			Opencheck = true;
		}
	}

}


void initTexture()
{

	glGenTextures(5, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int widthImage, heightImage, numberOfChannel;
	unsigned char* data = stbi_load("fireball.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int PYwidthImage, PYheightImage, PYnumberOfChannel;
	unsigned char* PYdata = stbi_load("123.jpg", &PYwidthImage, &PYheightImage, &PYnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, PYwidthImage, PYheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, PYdata);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(PYdata);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int BackwidthImage, BackheightImage, BacknumberOfChannel;
	unsigned char* Backdata = stbi_load("FireHely.jpg", &BackwidthImage, &BackheightImage, &BacknumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BackwidthImage, BackheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, Backdata);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(Backdata);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int TrapwidthImage, TrapheightImage, TrapnumberOfChannel;
	unsigned char* Trap = stbi_load("Helyimage.jpg", &TrapwidthImage, &TrapheightImage, &TrapnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TrapwidthImage, TrapheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, Trap);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(Trap);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int TailWidthImage, TailHeightImage, TailnumberOfChannel;
	unsigned char* TailData = stbi_load("tail.jpg", &TailWidthImage, &TailHeightImage, &TailnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TailWidthImage, TailHeightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, TailData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(TailData);

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int Stage2WidthImage, Stage2HeightImage, Stage2numberOfChannel;
	unsigned char* Stage2Data = stbi_load("Stage2Tail.jpg", &Stage2WidthImage, &Stage2HeightImage, &Stage2numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Stage2WidthImage, Stage2HeightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, Stage2Data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(Stage2Data);

}