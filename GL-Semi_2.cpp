#include "stdafx.h"
#include "readobjNomal.h"

char vn[64] = "Shader/vertexlighting.glsl";
char fn[64] = "Shader/fragmentlighting.glsl";
//Func
void timer(int value);
void SnowPlay();
void ResetCollection();
GLvoid InitBuffer();
GLvoid drawScene();
GLvoid KeyBoard(unsigned char Key, int x, int y);

//Statick
GLuint VAO[40], VBO[80];
GLuint shaderID;

//Vector
vector<glm::vec4>ObjNomarVal[38];
vector<glm::vec4>ObjVertexVal[38];
glm::vec3 LightColor = glm::vec3(0.903922,0.852941,0.790196);


//Check
bool ycheck = true;
bool xcheck = false;
bool solidchk = true;
bool LightBoxRotateM = false;
bool LightBoxRotateP = false;
bool CameraRotateP = false;
bool CameraRotateM = false;
bool rotchk = false;
bool swingAngle1 = true;
bool swingAngle2 = false;
bool MainswingAngle1 = true;
bool MainswingAngle2 = false;
bool LightOnOff = true;
bool Change1 = false;
bool Change2 = false;
bool Change3 = false;
bool Change4 = false;
bool TrapRotate = true;
bool snowcheck = true;
bool JumpState = false;
int jumpcheck = 0;
int Mainswingchk = 1;
int transcheck1 = 0;
int transcheck2 = 0;
int transcheck3 = 0;
int transcheck4 = 0;


//Struct
struct Camera
{
	float C_x = 1.0f;
	float C_y = 4.0f;
	float C_z = 10.0f;

}Camerapos;


//angle
struct Angle
{
	float angle = 0.0f;
	float anglex = 0.0f;
	float angley = 0.0f;
	float AngleTrap = 0.0f;
	float Radian = 0.0f;
	//---------------------
	float AngleRevolx = 45.0f;
	float AngleRevoly = 45.0f;
	//----------------------
	float anglecamera = 0.0f;
	float anglecamera2 = 0.0f;
	float ObjAngle = 20.0f;
	//------------------
	float LightRadian = 210.0f;
	//------------------
	float BodyAngle = 0.0f;
	float ArmAngle = 0.0f;
	float SwingAngle1 = 0.0f;
	float SwingAngle2 = 0.0f;
	float MainSwing1 = 0.0f;
	float MainSwing2 = 0.0f;

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

}Scalepos;

//trans
struct Transration
{
	float T_r1x = 4.0f;
	float T_r1y = 0.0f;
	float T_r1z = -4.0f;
	//---------------
	float T_r2x = -4.0f;
	float T_r2y = 0.0f;
	float T_r2z = -4.0f;
	//--------------
	float T_r3x = -2.0f;
	float T_r3y = 0.0f;
	float T_r3z = 0.0f;
	//----------------
	float T_r4x = 2.0f;
	float T_r4y = 0.0f;
	float T_r4z = 0.0f;
	//------------------
	float T_x = 0.0f;
	float T_y = 0.8f;
	float T_z = 0.0f;
	//---------------
	float T_X = 0.0f;
	float T_Y = -0.3f;
	float T_Z = 0.0f;
	//----------------
	float T_Trapx = 0.0f;
	float T_Trapy = 0.1f;
	float T_Trapz = 0.0f;
	//---------------
	float T_Bodyx = 0.0f;
	float T_Bodyy = -0.1f;
	float T_Bodyz = -2.0f;
	float T_hairy = -0.1f;
	//----------------
	float T_ArmLegx = 0.0f;
	float T_ArmLegy = 0.25f;
	float T_ArmLegz = 0.0f;

}TransList;

//snow
struct Snow {
	float x;
	float y;
	float z;
};

Snow SLocation[50];
Snow SaveLocation[50];
Snow SnowSpeed[50];


GLvoid InitBuffer()
{
	glGenVertexArrays(37, VAO);


	for (int i = 0; i < 14; i++)
	{
		glBindVertexArray(VAO[i]);
		glGenBuffers(2, &VBO[2 * i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjVertexVal[i].size(), &ObjVertexVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i + 1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjNomarVal[i].size(), &ObjNomarVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);
	}

	for (int i = 14; i < 19; i++)
	{
		glBindVertexArray(VAO[i]);
		glGenBuffers(2, &VBO[2 * i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjVertexVal[i].size(), &ObjVertexVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i + 1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjNomarVal[i].size(), &ObjNomarVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);

	}

	for (int i = 19; i < 24; i++)
	{
		glBindVertexArray(VAO[i]);
		glGenBuffers(2, &VBO[2 * i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjVertexVal[i].size(), &ObjVertexVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i + 1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjNomarVal[i].size(), &ObjNomarVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);

	}

	for (int i = 24; i < 29; i++)
	{
		glBindVertexArray(VAO[i]);
		glGenBuffers(2, &VBO[2 * i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjVertexVal[i].size(), &ObjVertexVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i + 1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjNomarVal[i].size(), &ObjNomarVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);

	}

	for (int i = 29; i < 34; i++)
	{
		glBindVertexArray(VAO[i]);
		glGenBuffers(2, &VBO[2 * i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjVertexVal[i].size(), &ObjVertexVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i + 1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjNomarVal[i].size(), &ObjNomarVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);

	}

	for (int i = 34; i < 38; i++)
	{

		glBindVertexArray(VAO[i]);
		glGenBuffers(2, &VBO[2 * i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjVertexVal[i].size(), &ObjVertexVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i + 1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjNomarVal[i].size(), &ObjNomarVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);
	}

}

void SnowPlay() 
{
	for (int i = 0; i < 50; i++) 
	{
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
void drawScene()
{

	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderID);
	//------------------------------camera---------------------------------------------

	glm::vec3 ObjectCamerapos = glm::vec3(Camerapos.C_x, Camerapos.C_y, Camerapos.C_z);
	glm::mat4 CameraSpacepos = glm::mat4(1.0f);
	CameraSpacepos = glm::rotate(CameraSpacepos, glm::radians(AngleList.anglecamera), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 CameraPosDis = glm::vec4(ObjectCamerapos, 1);
	CameraPosDis = CameraSpacepos * CameraPosDis;
	glm::vec3 Cameraposdir = glm::vec3(CameraPosDis.x, CameraPosDis.y, CameraPosDis.z);
	glm::vec3 ObjectCameraPicking = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 ObjectCameradir = Cameraposdir - ObjectCameraPicking;
	glm::vec3 Up_y = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 CameraSpacedir = glm::mat4(1.0f);
	CameraSpacedir = glm::rotate(CameraSpacedir, glm::radians(AngleList.anglecamera2), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 CameraSpaceMul = CameraSpacedir * glm::vec4(ObjectCameradir, 1);

	glm::vec3 Cameradir;
	Cameradir.x = CameraSpaceMul.x; Cameradir.y = CameraSpaceMul.y; Cameradir.z = CameraSpaceMul.z;
	Cameradir = glm::normalize(Cameradir);


	glm::mat4 RotateSpacedir = glm::mat4(1.0f);
	RotateSpacedir = glm::rotate(RotateSpacedir, glm::radians(AngleList.anglecamera2), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 RotateobjSpacedir = glm::vec3(ObjectCameraPicking - Cameraposdir);
	glm::vec4 Rotatedir = glm::vec4(RotateobjSpacedir, 1);
	Rotatedir = RotateSpacedir * Rotatedir;
	RotateobjSpacedir = glm::vec3(Rotatedir.x + Cameraposdir.x, Rotatedir.y + Cameraposdir.y, Rotatedir.z + Cameraposdir.z);
	glm::vec3 Crosspos = glm::normalize(glm::cross(Up_y, Cameradir));
	glm::vec3 Cross = glm::cross(Cameradir, Crosspos);

	glm::mat4 ObjView = glm::mat4(1.0f);
	ObjView = glm::lookAt(Cameraposdir, RotateobjSpacedir, Cross);
	unsigned int ObjcameraViewLocation = glGetUniformLocation(shaderID, "viewtransform");
	glUniformMatrix4fv(ObjcameraViewLocation, 1, GL_FALSE, glm::value_ptr(ObjView));


	glm::vec3 CameraView;
	CameraView = glm::vec3(Cameraposdir);
	unsigned int ViewPositionLocation = glGetUniformLocation(shaderID, "camerapos");
	glUniform3fv(ViewPositionLocation, 1, glm::value_ptr(CameraView));

	//--------원근
	glm::mat4 Proj = glm::mat4(1.0f);
	Proj = glm::perspective(glm::radians(60.0f), (float)(FRAME_WIDTH / FRAME_HEIGHT), 0.1f, 100.0f);
	unsigned int ModelProjLocation = glGetUniformLocation(shaderID, "projectiontransform");
	glUniformMatrix4fv(ModelProjLocation, 1, GL_FALSE, &Proj[0][0]);


	//--------조명
	glm::mat4 LightPosition = glm::mat4(1.0f);
	LightPosition = glm::rotate(LightPosition, glm::radians(AngleList.LightRadian), glm::vec3(0.0f, 1.0f, 0.0f));
	LightPosition = glm::translate(LightPosition, glm::vec3(Scalepos.X, Scalepos.Y, Scalepos.Z));
	unsigned int lightPosLocation = glGetUniformLocation(shaderID, "LightPos");
	glUniform3fv(lightPosLocation, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	unsigned int lightColorLocation = glGetUniformLocation(shaderID, "LightColor");
	glUniform3fv(lightColorLocation, 1, glm::value_ptr(LightColor));
	unsigned int LightTransformLocation = glGetUniformLocation(shaderID, "LightTransform");
	glUniformMatrix4fv(LightTransformLocation, 1, GL_FALSE, glm::value_ptr(LightPosition));


	//--------------------------------------draw-----------------------------------------------------
	//--------------------------------------바닥 조명-------------------------------------------------
	//바닥
	glBindVertexArray(VAO[0]);
	glm::mat4 BaseObj = glm::mat4(1.0f);
	BaseObj = glm::rotate(BaseObj, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	BaseObj = glm::translate(BaseObj, glm::vec3(TransList.T_X, TransList.T_Y - 0.4f, TransList.T_z));
	BaseObj = glm::scale(BaseObj, glm::vec3(12.0f, 0.1f, 12.0f));
	unsigned int BaseobjLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(BaseobjLocation, 1, GL_FALSE, glm::value_ptr(BaseObj));
	glm::mat4 BaseObjNormal = glm::mat4(1.0f);
	BaseObjNormal = glm::rotate(BaseObjNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int BaseObjNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(BaseObjNormalLocation, 1, GL_FALSE, glm::value_ptr(BaseObjNormal));
	unsigned int BaseobjfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(BaseobjfragLocation, 0.933333f, 0.913725f, 0.913725f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[0].size());
	if (TransList.T_Bodyx<=-5.8f) {
		TransList.T_Bodyx += 0.41f; TransList.T_ArmLegx += 0.41f;
	}
	if (TransList.T_Bodyx >= 5.8f) {
		TransList.T_Bodyx -= 0.41f; TransList.T_ArmLegx -= 0.41f;
	}
	if (TransList.T_Bodyz <= -5.8f) {
		TransList.T_Bodyz += 0.41f; TransList.T_ArmLegz += 0.41f;
	}
	if (TransList.T_Bodyz >= 5.8f) {
		TransList.T_Bodyz -= 0.41f; TransList.T_ArmLegz -= 0.41f;
	}

	//조명
	glBindVertexArray(VAO[1]);
	glm::mat4 LightBox = glm::mat4(1.0f);
	LightBox = glm::rotate(LightBox, glm::radians(AngleList.LightRadian), glm::vec3(0.0f, 1.0f, 0.0f));
	LightBox = glm::translate(LightBox, glm::vec3(Scalepos.X, Scalepos.Y, Scalepos.Z));
	//LightBox = glm::rotate(LightBox, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	LightBox = glm::scale(LightBox, glm::vec3(0.7f, 0.7f, 0.7f));
	unsigned int LightBoxLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(LightBoxLocation, 1, GL_FALSE, glm::value_ptr(LightBox));
	glm::mat4 LightBoxNormalmodel = glm::mat4(1.0f);
	LightBoxNormalmodel = glm::rotate(LightBoxNormalmodel, glm::radians(AngleList.LightRadian), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int LightBoxNormalmodelLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(LightBoxNormalmodelLocation, 1, GL_FALSE, glm::value_ptr(LightBoxNormalmodel));
	unsigned int LightBoxColorLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(LightBoxColorLocation, 0.933333	,0.866667,0.509804);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[1].size());


	//-------------------------------객체 변환---------------------------------------

	// 4. 왼쪽 상단 
	//----------충돌
	if (TransList.T_Bodyx >= TransList.T_x + 3.6f && TransList.T_Bodyx <= TransList.T_x + 5.0f && TransList.T_Bodyz >= TransList.T_z + 3.5 && TransList.T_Bodyz <= TransList.T_z + 4.5) {
		Change4 = true;
		transcheck4 = 1;
	}
	else
	{
		Change4 = false;
		if (transcheck4 == 1)
		{
			Change4 = true;
		}
	}
	//----------로봇-기둥 변환
	// * 로봇
	if (Change4 == true)
	{
		transcheck4 = 1;
		glBindVertexArray(VAO[29]);//VAO29
		glm::mat4 RobotBody = glm::mat4(1.0f);
		RobotBody = glm::translate(RobotBody, glm::vec3(TransList.T_r4x, TransList.T_r4y - 0.1f, TransList.T_r4z ));
		RobotBody = glm::rotate(RobotBody, glm::radians(AngleList.BodyAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RobotBody = glm::scale(RobotBody, glm::vec3(1.0f, 1.5f, 1.0f));
		unsigned int RobotBodyLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RobotBodyLocation, 1, GL_FALSE, glm::value_ptr(RobotBody));
		glm::mat4 RobotBodyNormal = glm::mat4(1.0f);
		RobotBodyNormal = glm::rotate(RobotBodyNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RobotBodyNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RobotBodyNormalLocation, 1, GL_FALSE, glm::value_ptr(RobotBodyNormal));
		unsigned int RobotBodyfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RobotBodyfragLocation, 0.147f, 0.345f, 0.428f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[29].size());

		glBindVertexArray(VAO[30]);//VAO30
		glm::mat4 RobotLARM = glm::mat4(1.0f);
		RobotLARM = glm::translate(RobotLARM, glm::vec3(TransList.T_r4x + 0.15f, TransList.T_r4y + 0.2f, TransList.T_r4z - 0.1f));
		RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RobotLARM = glm::translate(RobotLARM, glm::vec3(0.18f, 0.0f, 0.15f));
		if (Mainswingchk == 1) {
			RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Mainswingchk == 2) {
			RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
		}


		RobotLARM = glm::scale(RobotLARM, glm::vec3(0.15f, 0.6f, 0.15f));
		unsigned int RobotLARMLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RobotLARMLocation, 1, GL_FALSE, glm::value_ptr(RobotLARM));
		glm::mat4 RobotLARMNormal = glm::mat4(1.0f);
		RobotLARMNormal = glm::rotate(RobotLARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RobotLARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RobotLARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RobotLARMNormal));
		unsigned int RobotLARMfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RobotLARMfragLocation, 0.637f, 0.645f, 0.228f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[30].size());

		glBindVertexArray(VAO[31]);//VAO31
		glm::mat4 RIGHTARM = glm::mat4(1.0f);
		RIGHTARM = glm::translate(RIGHTARM, glm::vec3(TransList.T_r4x-0.15f, TransList.T_r4y + 0.2f, TransList.T_r4z+0.1f));
		RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RIGHTARM = glm::translate(RIGHTARM, glm::vec3(-0.18f, 0.0f, -0.2f));
		if (Mainswingchk == 1) {
			RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Mainswingchk == 2) {
			RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
		}


		RIGHTARM = glm::scale(RIGHTARM, glm::vec3(0.15f, 0.6f, 0.15f));
		unsigned int RIGHTARMLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RIGHTARMLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARM));
		glm::mat4 RIGHTARMNormal = glm::mat4(1.0f);
		RIGHTARMNormal = glm::rotate(RIGHTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RIGHTARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RIGHTARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARMNormal));
		unsigned int RIGHTARMfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RIGHTARMfragLocation, 0.637f, 0.645f, 0.228f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[31].size());

		glBindVertexArray(VAO[32]);//VAO32
		glm::mat4 LEFTLEG = glm::mat4(1.0f);
		LEFTLEG = glm::translate(LEFTLEG, glm::vec3(TransList.T_r4x , TransList.T_r4y - 0.3f, TransList.T_r4z));
		LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		LEFTLEG = glm::translate(LEFTLEG, glm::vec3(0.08f, 0.0f, 0.1f));
		if (Mainswingchk == 1) {
			LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Mainswingchk == 2) {
			LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
		}

		LEFTLEG = glm::scale(LEFTLEG, glm::vec3(0.15f, 0.6f, 0.2f));
		unsigned int LEFTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(LEFTLEGLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEG));
		glm::mat4 LEFTLEGNormal = glm::mat4(1.0f);
		LEFTLEGNormal = glm::rotate(LEFTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int LEFTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(LEFTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEGNormal));
		unsigned int LEFTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(LEFTLEGfragLocation, 0.637f, 0.645f, 0.228f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[32].size());

		glBindVertexArray(VAO[33]);//VAO33
		glm::mat4 RIGHTLEG = glm::mat4(1.0f);
		RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(TransList.T_r4x-0.1f, TransList.T_r4y - 0.3f, TransList.T_r4z));
		RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(-0.08f, 0.0f, -0.1f));
		if (Mainswingchk == 1)
		{
			RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Mainswingchk == 2)
		{
			RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		RIGHTLEG = glm::scale(RIGHTLEG, glm::vec3(0.15f, 0.6f, 0.2f));
		unsigned int RIGHTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RIGHTLEGLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEG));
		glm::mat4 RIGHTLEGNormal = glm::mat4(1.0f);
		RIGHTLEGNormal = glm::rotate(RIGHTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RIGHTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RIGHTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEGNormal));
		unsigned int RIGHTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RIGHTLEGfragLocation, 0.637f, 0.645f, 0.228f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[33].size());
	}
	// * 기둥
	if (Change4 == false)
	{
		transcheck4 = 0;
		glBindVertexArray(VAO[2]);//VAO2
		glm::mat4 LeftUPTransRobot = glm::mat4(1.0f);
		LeftUPTransRobot = glm::translate(LeftUPTransRobot, glm::vec3(TransList.T_x + 4.0f, TransList.T_y, TransList.T_z + 4.0f));
		LeftUPTransRobot = glm::rotate(LeftUPTransRobot, glm::radians(AngleList.Radian), glm::vec3(0.0f, 1.0f, 0.0f));
		LeftUPTransRobot = glm::scale(LeftUPTransRobot, glm::vec3(0.8f, 3.0f, 0.8f));
		unsigned int LeftUPobjLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(LeftUPobjLocation, 1, GL_FALSE, glm::value_ptr(LeftUPTransRobot));
		glm::mat4 LeftUPObjNormal = glm::mat4(1.0f);
		LeftUPObjNormal = glm::rotate(LeftUPObjNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int LeftUPObjNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(LeftUPObjNormalLocation, 1, GL_FALSE, glm::value_ptr(LeftUPObjNormal));
		unsigned int LeftUPobjfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(LeftUPobjfragLocation, 0.33f, 0.425f, 0.7f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[2].size());

	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 3.오른쪽 상단
	//-----------충돌
	if (TransList.T_Bodyx <= TransList.T_x - 3.5f && TransList.T_Bodyx >= TransList.T_x - 5.0f && TransList.T_Bodyz >= TransList.T_z + 3.5 && TransList.T_Bodyz <= TransList.T_z + 4.5) {
		Change3 = true;
		transcheck3 = 1;
	}
	else {
		Change3 = false;
		if (transcheck3 == 1) {
			Change3 = true;
		}
	}
	// 로봇 - 기둥 변환
	// *로봇
	if (Change3 == true)
	{
		transcheck3 == 1;
		glBindVertexArray(VAO[24]);//VAO24
		glm::mat4 RobotBody = glm::mat4(1.0f);
		RobotBody = glm::translate(RobotBody, glm::vec3(TransList.T_r3x, TransList.T_r3y - 0.1f, TransList.T_r3z));
		RobotBody = glm::rotate(RobotBody, glm::radians(AngleList.BodyAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RobotBody = glm::scale(RobotBody, glm::vec3(1.0f, 1.5f, 1.0f));
		unsigned int RobotBodyLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RobotBodyLocation, 1, GL_FALSE, glm::value_ptr(RobotBody));
		glm::mat4 RobotBodyNormal = glm::mat4(1.0f);
		RobotBodyNormal = glm::rotate(RobotBodyNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RobotBodyNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RobotBodyNormalLocation, 1, GL_FALSE, glm::value_ptr(RobotBodyNormal));
		unsigned int RobotBodyfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RobotBodyfragLocation, 0.747f, 0.145f, 0.528f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[24].size());

		glBindVertexArray(VAO[25]);//VAO25
		glm::mat4 RobotLARM = glm::mat4(1.0f);
		RobotLARM = glm::translate(RobotLARM, glm::vec3(TransList.T_r3x + 0.15f, TransList.T_r3y + 0.2f, TransList.T_r3z - 0.1f));
		RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RobotLARM = glm::translate(RobotLARM, glm::vec3(0.18f, 0.0f, 0.2f));

		if (Mainswingchk == 1) {
			RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Mainswingchk == 2) {
			RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		RobotLARM = glm::scale(RobotLARM, glm::vec3(0.15f, 0.6f, 0.15f));
		unsigned int RobotLARMLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RobotLARMLocation, 1, GL_FALSE, glm::value_ptr(RobotLARM));
		glm::mat4 RobotLARMNormal = glm::mat4(1.0f);
		RobotLARMNormal = glm::rotate(RobotLARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RobotLARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RobotLARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RobotLARMNormal));
		unsigned int RobotLARMfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RobotLARMfragLocation, 0.537f, 0.845f, 0.728f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[25].size());

		glBindVertexArray(VAO[26]);//VAO26
		glm::mat4 RIGHTARM = glm::mat4(1.0f);
		RIGHTARM = glm::translate(RIGHTARM, glm::vec3(TransList.T_r3x -0.15, TransList.T_r3y + 0.2f, TransList.T_r3z +0.1f));
		RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RIGHTARM = glm::translate(RIGHTARM, glm::vec3(-0.18f, 0.0f, -0.2f));

		if (Mainswingchk == 1) {
			RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Mainswingchk == 2) {
			RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		RIGHTARM = glm::scale(RIGHTARM, glm::vec3(0.15f, 0.6f, 0.15f));
		unsigned int RIGHTARMLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RIGHTARMLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARM));
		glm::mat4 RIGHTARMNormal = glm::mat4(1.0f);
		RIGHTARMNormal = glm::rotate(RIGHTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RIGHTARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RIGHTARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARMNormal));
		unsigned int RIGHTARMfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RIGHTARMfragLocation, 0.537f, 0.845f, 0.728f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[26].size());

		glBindVertexArray(VAO[27]);//VAO27
		glm::mat4 LEFTLEG = glm::mat4(1.0f);
		LEFTLEG = glm::translate(LEFTLEG, glm::vec3(TransList.T_r3x , TransList.T_r3y - 0.3f, TransList.T_r3z ));
		LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		LEFTLEG = glm::translate(LEFTLEG, glm::vec3(0.08f, 0.0f, 0.1f));

		if (Mainswingchk == 1) {
			LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Mainswingchk == 2) {
			LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		LEFTLEG = glm::scale(LEFTLEG, glm::vec3(0.15f, 0.6f, 0.15f));
		unsigned int LEFTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(LEFTLEGLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEG));
		glm::mat4 LEFTLEGNormal = glm::mat4(1.0f);
		LEFTLEGNormal = glm::rotate(LEFTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int LEFTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(LEFTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEGNormal));
		unsigned int LEFTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(LEFTLEGfragLocation, 0.537f, 0.845f, 0.728f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[27].size());

		glBindVertexArray(VAO[28]);//VAO28
		glm::mat4 RIGHTLEG = glm::mat4(1.0f);
		RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(TransList.T_r3x , TransList.T_r3y - 0.3f, TransList.T_r3z ));
		RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(-0.08f, 0.0f, -0.1f));

		if (Mainswingchk == 1) {
			RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Mainswingchk == 2) {
			RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		RIGHTLEG = glm::scale(RIGHTLEG, glm::vec3(0.15f, 0.6f, 0.15f));
		unsigned int RIGHTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RIGHTLEGLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEG));
		glm::mat4 RIGHTLEGNormal = glm::mat4(1.0f);
		RIGHTLEGNormal = glm::rotate(RIGHTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RIGHTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RIGHTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEGNormal));
		unsigned int RIGHTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RIGHTLEGfragLocation, 0.537f, 0.845f, 0.728f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[28].size());
	}
	// * 기둥
	if (Change3 == false)
	{
		transcheck3 == 0;
		glBindVertexArray(VAO[3]);//VAO3
		glm::mat4 RightUPTransRobot = glm::mat4(1.0f);
		RightUPTransRobot = glm::translate(RightUPTransRobot, glm::vec3(TransList.T_x - 4.0f, TransList.T_y, TransList.T_z + 4.0f));
		RightUPTransRobot = glm::rotate(RightUPTransRobot, glm::radians(AngleList.Radian), glm::vec3(0.0f, 1.0f, 0.0f));
		RightUPTransRobot = glm::scale(RightUPTransRobot, glm::vec3(0.8f, 3.0f, 0.8f));
		unsigned int RightUPobjLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RightUPobjLocation, 1, GL_FALSE, glm::value_ptr(RightUPTransRobot));
		glm::mat4 RightUPObjNormal = glm::mat4(1.0f);
		RightUPObjNormal = glm::rotate(RightUPObjNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RightUPObjNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RightUPObjNormalLocation, 1, GL_FALSE, glm::value_ptr(RightUPObjNormal));
		unsigned int RightUPobjfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RightUPobjfragLocation, 0.83f, 0.225f, 0.51f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[3].size());
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 2.오른쪽 하단
	//-----------충돌
	if (TransList.T_Bodyx <= TransList.T_x - 3.5f && TransList.T_Bodyx >= TransList.T_x - 5.0f && TransList.T_Bodyz >= TransList.T_z - 4.5f && TransList.T_Bodyz <= TransList.T_z - 3.0f)
	{
		Change2 = true;
		transcheck2 = 1;
	}
	else
	{
		Change2 = false;
		if (transcheck2 == 1)
		{
			Change2 = true;
		}
	}
	//--------------로봇-기둥 변환
	//*로봇
	if (Change2 == true)
	{
		transcheck2 = 1;
		{
			glBindVertexArray(VAO[19]);//VAO19
			glm::mat4 RobotBody = glm::mat4(1.0f);
			RobotBody = glm::translate(RobotBody, glm::vec3(TransList.T_r2x , TransList.T_r2y - 0.1f, TransList.T_r2z ));
			RobotBody = glm::rotate(RobotBody, glm::radians(AngleList.BodyAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			RobotBody = glm::scale(RobotBody, glm::vec3(1.0f, 1.5f, 1.0f));
			unsigned int RobotBodyLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(RobotBodyLocation, 1, GL_FALSE, glm::value_ptr(RobotBody));
			glm::mat4 RobotBodyNormal = glm::mat4(1.0f);
			RobotBodyNormal = glm::rotate(RobotBodyNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int RobotBodyNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(RobotBodyNormalLocation, 1, GL_FALSE, glm::value_ptr(RobotBodyNormal));
			unsigned int RobotBodyfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(RobotBodyfragLocation, 0.547f, 0.845f, 0.228f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[19].size());

			glBindVertexArray(VAO[20]);//VAO20
			glm::mat4 RobotLARM = glm::mat4(1.0f);
			RobotLARM = glm::translate(RobotLARM, glm::vec3(TransList.T_r2x + 0.15f, TransList.T_r2y + 0.2f, TransList.T_r2z - 0.2f));
			RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			RobotLARM = glm::translate(RobotLARM, glm::vec3(0.18f, 0.0f, 0.15f));
			if (Mainswingchk == 1) {
				RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (Mainswingchk == 2) {
				RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
			}

			RobotLARM = glm::scale(RobotLARM, glm::vec3(0.15f, 0.6f, 0.15f));
			unsigned int RobotLARMLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(RobotLARMLocation, 1, GL_FALSE, glm::value_ptr(RobotLARM));
			glm::mat4 RobotLARMNormal = glm::mat4(1.0f);
			RobotLARMNormal = glm::rotate(RobotLARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int RobotLARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(RobotLARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RobotLARMNormal));
			unsigned int RobotLARMfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(RobotLARMfragLocation, 0.737f, 0.245f, 0.528f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[20].size());

			glBindVertexArray(VAO[21]);//VAO21
			glm::mat4 RIGHTARM = glm::mat4(1.0f);
			RIGHTARM = glm::translate(RIGHTARM, glm::vec3(TransList.T_r2x -0.15f, TransList.T_r2y + 0.2f, TransList.T_r2z +0.2f));
			RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			RIGHTARM = glm::translate(RIGHTARM, glm::vec3(-0.18f, 0.0f, -0.2f));
			if (Mainswingchk == 1) {
				RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (Mainswingchk == 2) {
				RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
			}

			RIGHTARM = glm::scale(RIGHTARM, glm::vec3(0.15f, 0.6f, 0.15f));
			unsigned int RIGHTARMLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(RIGHTARMLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARM));
			glm::mat4 RIGHTARMNormal = glm::mat4(1.0f);
			RIGHTARMNormal = glm::rotate(RIGHTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int RIGHTARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(RIGHTARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARMNormal));
			unsigned int RIGHTARMfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(RIGHTARMfragLocation, 0.737f, 0.245f, 0.528f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[21].size());

			glBindVertexArray(VAO[22]);//VAO22
			glm::mat4 LEFTLEG = glm::mat4(1.0f);
			LEFTLEG = glm::translate(LEFTLEG, glm::vec3(TransList.T_r2x, TransList.T_r2y - 0.3f, TransList.T_r2z));
			LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			LEFTLEG = glm::translate(LEFTLEG, glm::vec3(0.08f, 0.0f, 0.1f));
			if (Mainswingchk == 1) {
				LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (Mainswingchk == 2) {
				LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			LEFTLEG = glm::scale(LEFTLEG, glm::vec3(0.15f, 0.6f, 0.2f));
			unsigned int LEFTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(LEFTLEGLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEG));
			glm::mat4 LEFTLEGNormal = glm::mat4(1.0f);
			LEFTLEGNormal = glm::rotate(LEFTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int LEFTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(LEFTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEGNormal));
			unsigned int LEFTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(LEFTLEGfragLocation, 0.737f, 0.245f, 0.528f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[22].size());

			glBindVertexArray(VAO[23]);//VAO23
			glm::mat4 RIGHTLEG = glm::mat4(1.0f);
			RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(TransList.T_r2x -0.1f, TransList.T_r2y - 0.3f, TransList.T_r2z ));
			RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(-0.08f, 0.0f, -0.1f));
			if (Mainswingchk == 1) {
				RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (Mainswingchk == 2) {
				RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
			}

			RIGHTLEG = glm::scale(RIGHTLEG, glm::vec3(0.15f, 0.6f, 0.15f));
			unsigned int RIGHTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(RIGHTLEGLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEG));
			glm::mat4 RIGHTLEGNormal = glm::mat4(1.0f);
			RIGHTLEGNormal = glm::rotate(RIGHTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int RIGHTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(RIGHTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEGNormal));
			unsigned int RIGHTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(RIGHTLEGfragLocation, 0.737f, 0.245f, 0.528f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[23].size());
		}
	}
	//*기둥
	if (Change2 == false)
	{
		transcheck2 = 0;
		glBindVertexArray(VAO[4]);//VAO4
		glm::mat4 RightDOWNTransRobot = glm::mat4(1.0f);
		RightDOWNTransRobot = glm::translate(RightDOWNTransRobot, glm::vec3(TransList.T_x - 4.0f, TransList.T_y, TransList.T_z - 4.0f));
		RightDOWNTransRobot = glm::rotate(RightDOWNTransRobot, glm::radians(AngleList.Radian), glm::vec3(0.0f, 1.0f, 0.0f));
		RightDOWNTransRobot = glm::scale(RightDOWNTransRobot, glm::vec3(0.8f, 3.0f, 0.8f));
		unsigned int RightDownobjLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RightDownobjLocation, 1, GL_FALSE, glm::value_ptr(RightDOWNTransRobot));
		glm::mat4 RightDownObjNormal = glm::mat4(1.0f);
		RightDownObjNormal = glm::rotate(RightDownObjNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RightDownObjNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RightDownObjNormalLocation, 1, GL_FALSE, glm::value_ptr(RightDownObjNormal));
		unsigned int RightDownobjfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RightDownobjfragLocation, 0.153f, 0.625f, 0.034f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[4].size());
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 1.오른쪽 상단
	//-------------충돌 부분
	if (TransList.T_Bodyx >= TransList.T_x + 3.0f && TransList.T_Bodyx <= TransList.T_x + 5.0f && TransList.T_Bodyz >= TransList.T_z - 5.0f && TransList.T_Bodyz <= TransList.T_z - 3.3f)
	{
		Change1 = true;
		transcheck1 = 1;
	}
	else
	{
		Change1 = false;
		if (transcheck1 == 1)
		{
			Change1 = true;
		}
	}
	//-------------로봇 - 기둥 변환 부분
	//*로봇
	if (Change1 == true)
	{
		transcheck1 = 1;
		{
			glBindVertexArray(VAO[14]);//VAO14
			glm::mat4 RobotBody = glm::mat4(1.0f);
			RobotBody = glm::translate(RobotBody, glm::vec3(TransList.T_r1x, TransList.T_r1y - 0.1f, TransList.T_r1z));
			RobotBody = glm::rotate(RobotBody, glm::radians(AngleList.BodyAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			RobotBody = glm::scale(RobotBody, glm::vec3(1.0f, 1.5f, 1.0f));
			unsigned int RobotBodyLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(RobotBodyLocation, 1, GL_FALSE, glm::value_ptr(RobotBody));
			glm::mat4 RobotBodyNormal = glm::mat4(1.0f);
			RobotBodyNormal = glm::rotate(RobotBodyNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int RobotBodyNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(RobotBodyNormalLocation, 1, GL_FALSE, glm::value_ptr(RobotBodyNormal));
			unsigned int RobotBodyfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(RobotBodyfragLocation, 0.877f, 0.345f, 0.928f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[14].size());

			glBindVertexArray(VAO[15]);//VAO15
			glm::mat4 RobotLARM = glm::mat4(1.0f);
			RobotLARM = glm::translate(RobotLARM, glm::vec3(TransList.T_r1x + 0.15f, TransList.T_r1y + 0.2f, TransList.T_r1z - 0.1f));
			RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			RobotLARM = glm::translate(RobotLARM, glm::vec3(0.18f, 0.0f, 0.2f));
			if (Mainswingchk == 1) {
				RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (Mainswingchk == 2) {
				RobotLARM = glm::rotate(RobotLARM, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			RobotLARM = glm::scale(RobotLARM, glm::vec3(0.15f, 0.6f, 0.15f));
			unsigned int RobotLARMLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(RobotLARMLocation, 1, GL_FALSE, glm::value_ptr(RobotLARM));
			glm::mat4 RobotLARMNormal = glm::mat4(1.0f);
			RobotLARMNormal = glm::rotate(RobotLARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int RobotLARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(RobotLARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RobotLARMNormal));
			unsigned int RobotLARMfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(RobotLARMfragLocation, 0.237f, 0.545f, 0.428f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[15].size());

			glBindVertexArray(VAO[16]);//VAO16
			glm::mat4 RIGHTARM = glm::mat4(1.0f);
			RIGHTARM = glm::translate(RIGHTARM, glm::vec3(TransList.T_r1x - 0.15f, TransList.T_r1y + 0.2f, TransList.T_r1z + 0.1f));
			RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			RIGHTARM = glm::translate(RIGHTARM, glm::vec3(-0.18f, 0.0f, -0.2f));
			if (Mainswingchk == 1) {
				RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (Mainswingchk == 2) {
				RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			RIGHTARM = glm::scale(RIGHTARM, glm::vec3(0.15f, 0.6f, 0.15f));
			unsigned int RIGHTARMLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(RIGHTARMLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARM));
			glm::mat4 RIGHTARMNormal = glm::mat4(1.0f);
			RIGHTARMNormal = glm::rotate(RIGHTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int RIGHTARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(RIGHTARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARMNormal));
			unsigned int RIGHTARMfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(RIGHTARMfragLocation, 0.237f, 0.545f, 0.428f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[16].size());

			glBindVertexArray(VAO[17]);//VAO17
			glm::mat4 LEFTLEG = glm::mat4(1.0f);
			LEFTLEG = glm::translate(LEFTLEG, glm::vec3(TransList.T_r1x, TransList.T_r1y - 0.3f, TransList.T_r1z));
			LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			LEFTLEG = glm::translate(LEFTLEG, glm::vec3(0.08f, 0.0f, 0.1f));
			if (Mainswingchk == 1) {
				LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (Mainswingchk == 2) {
				LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			LEFTLEG = glm::scale(LEFTLEG, glm::vec3(0.15f, 0.6f, 0.15f));
			unsigned int LEFTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(LEFTLEGLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEG));
			glm::mat4 LEFTLEGNormal = glm::mat4(1.0f);
			LEFTLEGNormal = glm::rotate(LEFTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int LEFTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(LEFTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEGNormal));
			unsigned int LEFTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(LEFTLEGfragLocation, 0.237f, 0.545f, 0.428f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[17].size());

			glBindVertexArray(VAO[18]);//VAO18
			glm::mat4 RIGHTLEG = glm::mat4(1.0f);
			RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(TransList.T_r1x - 0.1f, TransList.T_r1y - 0.3f, TransList.T_r1z));
			RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(-0.08f, 0.0f, -0.1f));
			if (Mainswingchk == 1) {
				RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (Mainswingchk == 2) {
				RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			RIGHTLEG = glm::scale(RIGHTLEG, glm::vec3(0.15f, 0.6f, 0.15f));
			unsigned int RIGHTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
			glUniformMatrix4fv(RIGHTLEGLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEG));
			glm::mat4 RIGHTLEGNormal = glm::mat4(1.0f);
			RIGHTLEGNormal = glm::rotate(RIGHTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int RIGHTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
			glUniformMatrix4fv(RIGHTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEGNormal));
			unsigned int RIGHTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
			glUniform3f(RIGHTLEGfragLocation, 0.237f, 0.545f, 0.428f);
			glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[18].size());
		}
	}
	//*기둥
	if (Change1 == false)
	{
		transcheck1 = 0;

		glBindVertexArray(VAO[5]);//VAO5
		glm::mat4 LEFTDOWNTransRobot = glm::mat4(1.0f);
		LEFTDOWNTransRobot = glm::translate(LEFTDOWNTransRobot, glm::vec3(TransList.T_x + 4.0f, TransList.T_y, TransList.T_z - 4.0f));
		LEFTDOWNTransRobot = glm::rotate(LEFTDOWNTransRobot, glm::radians(AngleList.Radian), glm::vec3(0.0f, 1.0f, 0.0f));
		LEFTDOWNTransRobot = glm::scale(LEFTDOWNTransRobot, glm::vec3(0.8f, 3.0f, 0.8f));
		unsigned int LEFTDOWNobjLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(LEFTDOWNobjLocation, 1, GL_FALSE, glm::value_ptr(LEFTDOWNTransRobot));
		glm::mat4 LEFTDOWNObjNormal = glm::mat4(1.0f);
		LEFTDOWNObjNormal = glm::rotate(LEFTDOWNObjNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int LEFTDOWNObjNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(LEFTDOWNObjNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTDOWNObjNormal));
		unsigned int LEFTDOWNobjfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(LEFTDOWNobjfragLocation, 0.53f, 0.325f, 0.6f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[5].size());
	}

///////////////////////////////////////////////////////////////////////////////장애물 및 주인공 객체///////////////////////////////////////////////////////////////////////////////////////////////

	//하단 자전 도형
	{
		glBindVertexArray(VAO[6]);//VAO6
		glm::mat4 DOWNREVOLUTION = glm::mat4(1.0f);
		DOWNREVOLUTION = glm::translate(DOWNREVOLUTION, glm::vec3(TransList.T_Trapx, TransList.T_Trapy, TransList.T_Trapz + 4.0f));
		DOWNREVOLUTION = glm::rotate(DOWNREVOLUTION, glm::radians(AngleList.AngleRevoly), glm::vec3(0.0f, 1.0f, 0.0f));
		DOWNREVOLUTION = glm::rotate(DOWNREVOLUTION, glm::radians(AngleList.AngleRevolx), glm::vec3(1.0f, 0.0f, 1.0f));
		DOWNREVOLUTION = glm::scale(DOWNREVOLUTION, glm::vec3(0.7f, 0.7f, 0.7f));
		unsigned int DOWNREVOLUTIONLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(DOWNREVOLUTIONLocation, 1, GL_FALSE, glm::value_ptr(DOWNREVOLUTION));
		glm::mat4 DOWNREVOLUTIONNormal = glm::mat4(1.0f);
		DOWNREVOLUTIONNormal = glm::rotate(DOWNREVOLUTIONNormal, glm::radians(AngleList.angle), glm::vec3(1.0f, 1.0f, 1.0f));
		unsigned int DOWNREVOLUTIONNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(DOWNREVOLUTIONNormalLocation, 1, GL_FALSE, glm::value_ptr(DOWNREVOLUTIONNormal));
		unsigned int DOWNREVOLUTIONfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(DOWNREVOLUTIONfragLocation, 0.73f, 0.325f, 0.2f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[6].size());
		if (TransList.T_Bodyx >= TransList.T_Trapx -1.0f && TransList.T_Bodyx <= TransList.T_Trapx + 1.0f && TransList.T_Bodyz <= TransList.T_Trapz +5.0f && TransList.T_Bodyz >= TransList.T_Trapz +2.0f)
		{
			TransList.T_Bodyz -= 0.2f;
			TransList.T_ArmLegz -= 0.2f;
		}
	}

	//왼쪽 자전 도형
	{
		glBindVertexArray(VAO[7]);//VAO7
		glm::mat4 LEFTREVOLUTIONTransRobot = glm::mat4(1.0f);
		LEFTREVOLUTIONTransRobot = glm::translate(LEFTREVOLUTIONTransRobot, glm::vec3(TransList.T_Trapx + 4.0f, TransList.T_Trapy, TransList.T_Trapz));
		LEFTREVOLUTIONTransRobot = glm::rotate(LEFTREVOLUTIONTransRobot, glm::radians(AngleList.AngleRevoly), glm::vec3(0.0f, 1.0f, 0.0f));
		LEFTREVOLUTIONTransRobot = glm::rotate(LEFTREVOLUTIONTransRobot, glm::radians(AngleList.AngleRevolx), glm::vec3(1.0f, 0.0f, 1.0f));
		LEFTREVOLUTIONTransRobot = glm::scale(LEFTREVOLUTIONTransRobot, glm::vec3(0.7f, 0.7f, 0.7f));
		unsigned int LEFTREVOLUTIONobjLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(LEFTREVOLUTIONobjLocation, 1, GL_FALSE, glm::value_ptr(LEFTREVOLUTIONTransRobot));
		glm::mat4 LEFTREVOLUTIONObjNormal = glm::mat4(1.0f);
		LEFTREVOLUTIONObjNormal = glm::rotate(LEFTREVOLUTIONObjNormal, glm::radians(AngleList.angle), glm::vec3(1.0f, 1.0f, 0.0f));
		unsigned int LEFTREVOLUTIONObjNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(LEFTREVOLUTIONObjNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTREVOLUTIONObjNormal));
		unsigned int LEFTREVOLUTIONobjfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(LEFTREVOLUTIONobjfragLocation, 0.13f, 0.625f, 0.56f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[7].size());
		if (TransList.T_Bodyx <= TransList.T_Trapx + 5.0f && TransList.T_Bodyx >= TransList.T_Trapx + 3.0f && TransList.T_Bodyz >= TransList.T_Trapz - 1.0f && TransList.T_Bodyz <= TransList.T_Trapz + 1.0f)
		{
			TransList.T_Bodyx -= 0.2f;
			TransList.T_ArmLegx -= 0.2f;
		}
	}

	//오른쪽 자전 도형
	{
		glBindVertexArray(VAO[8]);//VAO8
		glm::mat4 RIGHTREVOLUTIONTransRobot = glm::mat4(1.0f);
		RIGHTREVOLUTIONTransRobot = glm::translate(RIGHTREVOLUTIONTransRobot, glm::vec3(TransList.T_Trapx - 4.0f, TransList.T_Trapy, TransList.T_Trapz));
		RIGHTREVOLUTIONTransRobot = glm::rotate(RIGHTREVOLUTIONTransRobot, glm::radians(AngleList.AngleRevoly), glm::vec3(0.0f, 1.0f, 0.0f));
		RIGHTREVOLUTIONTransRobot = glm::rotate(RIGHTREVOLUTIONTransRobot, glm::radians(AngleList.AngleRevolx), glm::vec3(1.0f, 0.0f, 1.0f));
		RIGHTREVOLUTIONTransRobot = glm::scale(RIGHTREVOLUTIONTransRobot, glm::vec3(0.7f, 0.7f, 0.7f));
		unsigned int RIGHTREVOLUTIONobjLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(RIGHTREVOLUTIONobjLocation, 1, GL_FALSE, glm::value_ptr(RIGHTREVOLUTIONTransRobot));
		glm::mat4 RIGHTREVOLUTIONObjNormal = glm::mat4(1.0f);
		RIGHTREVOLUTIONObjNormal = glm::rotate(RIGHTREVOLUTIONObjNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int RIGHTREVOLUTIONObjNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(RIGHTREVOLUTIONObjNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTREVOLUTIONObjNormal));
		unsigned int RIGHTREVOLUTIONobjfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(RIGHTREVOLUTIONobjfragLocation, 0.367f, 0.125f, 0.8f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[8].size());

		if (TransList.T_Bodyx >= TransList.T_Trapx - 5.0f && TransList.T_Bodyx <= TransList.T_Trapx - 3.0f && TransList.T_Bodyz >= TransList.T_Trapz - 1.0f && TransList.T_Bodyz <= TransList.T_Trapz + 1.0f)
		{
			TransList.T_Bodyx += 0.2f;
			TransList.T_ArmLegx += 0.2f;

		}
	}

	//로봇 몸통 & 머리 
	glBindVertexArray(VAO[9]);//VAO9
	glm::mat4 BODY = glm::mat4(1.0f);
	BODY = glm::translate(BODY, glm::vec3(TransList.T_Bodyx, TransList.T_Bodyy, TransList.T_Bodyz));
	BODY = glm::rotate(BODY, glm::radians(AngleList.BodyAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	BODY = glm::scale(BODY, glm::vec3(1.0f, Scalepos.My+1.5f, 1.0f));
	unsigned int BODYLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(BODYLocation, 1, GL_FALSE, glm::value_ptr(BODY));
	glm::mat4 BODYNormal = glm::mat4(1.0f);
	BODYNormal = glm::rotate(BODYNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int BODYNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(BODYNormalLocation, 1, GL_FALSE, glm::value_ptr(BODYNormal));
	unsigned int BODYfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(BODYfragLocation, 0.862745f, 0.862745f, 0.862745f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[9].size());

	glBindVertexArray(VAO[35]);//VAO35
	glm::mat4 HAIR = glm::mat4(1.0f);
	HAIR = glm::translate(HAIR, glm::vec3(TransList.T_Bodyx, TransList.T_hairy + 1.0f, TransList.T_Bodyz));
	HAIR = glm::scale(HAIR, glm::vec3(0.4f, 0.1f, 0.3f));
	unsigned int HAIRLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(HAIRLocation, 1, GL_FALSE, glm::value_ptr(HAIR));
	glm::mat4 HAIRNormal = glm::mat4(1.0f);
	HAIRNormal = glm::rotate(HAIRNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int HAIRNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(HAIRNormalLocation, 1, GL_FALSE, glm::value_ptr(HAIRNormal));
	unsigned int HAIRfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(HAIRfragLocation, 0.956863f, 0.933333f, 0.878431f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[35].size());

	glBindVertexArray(VAO[36]);//VAO35
	glm::mat4 HAIR2 = glm::mat4(1.0f);
	HAIR2 = glm::translate(HAIR2, glm::vec3(TransList.T_Bodyx, TransList.T_hairy + 1.1f, TransList.T_Bodyz));
	HAIR2 = glm::scale(HAIR2, glm::vec3(0.1f, 0.1f, 0.1f));
	unsigned int HAIR2Location = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(HAIR2Location, 1, GL_FALSE, glm::value_ptr(HAIR2));
	glm::mat4 HAIR2Normal = glm::mat4(1.0f);
	HAIR2Normal = glm::rotate(HAIR2Normal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int HAIR2NormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(HAIR2NormalLocation, 1, GL_FALSE, glm::value_ptr(HAIR2Normal));
	unsigned int HAIR2fragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(HAIR2fragLocation, 0.956863f, 0.933333f, 0.878431f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[36].size());

	//왼쪽 팔
	glBindVertexArray(VAO[10]);//VAO10 : ObjVertexVal[10] ~  ObjVertexVal[13]
	glm::mat4 LEFTARM = glm::mat4(1.0f);
	LEFTARM = glm::translate(LEFTARM, glm::vec3(TransList.T_ArmLegx + 0.2f, TransList.T_ArmLegy, TransList.T_ArmLegz - 2.15f));
	LEFTARM = glm::rotate(LEFTARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	LEFTARM = glm::translate(LEFTARM, glm::vec3(0.18f, 0.0f, 0.15f));
	if (Mainswingchk == 1) {
		LEFTARM = glm::rotate(LEFTARM, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Mainswingchk == 2) {
		LEFTARM = glm::rotate(LEFTARM, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	LEFTARM = glm::scale(LEFTARM, glm::vec3(0.15f, Scalepos.My+0.6f, 0.15f));
	unsigned int LEFTARMLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(LEFTARMLocation, 1, GL_FALSE, glm::value_ptr(LEFTARM));
	glm::mat4 LEFTARMNormal = glm::mat4(1.0f);
	LEFTARMNormal = glm::rotate(LEFTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int LEFTARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(LEFTARMNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTARMNormal));
	unsigned int LEFTARMfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(LEFTARMfragLocation, 0.247f, 0.45f, 0.628f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[10].size());

	//오른쪽 팔
	glm::mat4 RIGHTARM = glm::mat4(1.0f);
	RIGHTARM = glm::translate(RIGHTARM, glm::vec3(TransList.T_ArmLegx - 0.2f, TransList.T_ArmLegy, TransList.T_ArmLegz - 1.85f));
	RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	RIGHTARM = glm::translate(RIGHTARM, glm::vec3(-0.18f, 0.0f, -0.15f));
	if (Mainswingchk == 1) {
		RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Mainswingchk == 2) {
		RIGHTARM = glm::rotate(RIGHTARM, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	RIGHTARM = glm::scale(RIGHTARM, glm::vec3(0.15f, Scalepos.My+ 0.6f, 0.15f));
	unsigned int RIGHTARMLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(RIGHTARMLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARM));
	glm::mat4 RIGHTARMNormal = glm::mat4(1.0f);
	RIGHTARMNormal = glm::rotate(RIGHTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int RIGHTARMNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(RIGHTARMNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTARMNormal));
	unsigned int RIGHTARMfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(RIGHTARMfragLocation, 0.247f, 0.45f, 0.628f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[11].size());

	//왼쪽 발
	glm::mat4 LEFTLEG = glm::mat4(1.0f);
	LEFTLEG = glm::translate(LEFTLEG, glm::vec3(TransList.T_ArmLegx + 0.03f, TransList.T_ArmLegy - 0.5f, TransList.T_ArmLegz - 2.1f));
	LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	LEFTLEG = glm::translate(LEFTLEG, glm::vec3(0.08f, 0.0f, 0.1f));
	if (Mainswingchk == 1) {
		LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Mainswingchk == 2) {
		LEFTLEG = glm::rotate(LEFTLEG, glm::radians(AngleList.MainSwing2), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	LEFTLEG = glm::scale(LEFTLEG, glm::vec3(0.15f, Scalepos.My+0.6f, 0.15f));
	unsigned int LEFTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(LEFTLEGLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEG));
	glm::mat4 LEFTLEGNormal = glm::mat4(1.0f);
	LEFTLEGNormal = glm::rotate(LEFTARMNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int LEFTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(LEFTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(LEFTLEGNormal));
	unsigned int LEFTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(LEFTLEGfragLocation, 0.247f, 0.45f, 0.628f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[12].size());

	//오른쪽 발
	glm::mat4 RIGHTLEG = glm::mat4(1.0f);
	RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(TransList.T_ArmLegx - 0.03f, TransList.T_ArmLegy - 0.5f, TransList.T_ArmLegz - 1.9f));
	RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.ArmAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	RIGHTLEG = glm::translate(RIGHTLEG, glm::vec3(-0.08f, 0.0f, -0.1f));
	if (Mainswingchk == 1) {
		RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Mainswingchk == 2) {
		RIGHTLEG = glm::rotate(RIGHTLEG, glm::radians(AngleList.MainSwing1), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	RIGHTLEG = glm::scale(RIGHTLEG, glm::vec3(0.15f, Scalepos.My+0.6f, 0.15f));
	unsigned int RIGHTLEGLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(RIGHTLEGLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEG));
	glm::mat4 RIGHTLEGNormal = glm::mat4(1.0f);
	RIGHTLEGNormal = glm::rotate(RIGHTLEGNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int RIGHTLEGNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(RIGHTLEGNormalLocation, 1, GL_FALSE, glm::value_ptr(RIGHTLEGNormal));
	unsigned int RIGHTLEGfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(RIGHTLEGfragLocation, 0.247f, 0.45f, 0.628f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[13].size());


	// 눈
	for (int i = 0; i < 50; i++)
	{
		glBindVertexArray(VAO[37]);
		glm::mat4 Snow = glm::mat4(1.0f);
		Snow = glm::translate(Snow, glm::vec3(SLocation[i].x, SLocation[i].y, SLocation[i].z));
		Snow = glm::scale(Snow, glm::vec3(0.05f, 0.05f, 0.05f));
		unsigned int SnowLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(SnowLocation, 1, GL_FALSE, glm::value_ptr(Snow));
		glm::mat4 SnowNormalmodel = glm::mat4(1.0f);
		SnowNormalmodel = glm::translate(SnowNormalmodel, glm::vec3(SLocation[i].x, SLocation[i].y, SLocation[i].z));
		unsigned int SnowNormalmodelLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(SnowNormalmodelLocation, 1, GL_FALSE, glm::value_ptr(SnowNormalmodel));
		unsigned int SnowColorLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(SnowColorLocation, 0.958f, 0.958f, 0.958f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[37].size());
	}


	glutSwapBuffers();
}

GLvoid KeyBoard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	//---------------------------조명 
	case 'r':
		LightBoxRotateP = false;
		LightBoxRotateM = !LightBoxRotateM;
		break;
	case 'R':
		LightBoxRotateM = false;
		LightBoxRotateP = !LightBoxRotateP;
		break;
	case 't':
		LightOnOff = !LightOnOff;
		break;
	//---------------------------카메라
	case 'z':
		Camerapos.C_z -= 0.04f;
		break;
	case 'Z':
		Camerapos.C_z += 0.04f;
		break;
	case 'x':
		Camerapos.C_x -= 0.04f;
		break;
	case 'X':
		Camerapos.C_x += 0.04f;
		break;
	case 'c':
		CameraRotateM = false;
		CameraRotateP = !CameraRotateP;
		break;
	case 'C':
		CameraRotateP = false;
		CameraRotateM = !CameraRotateM;
		break;

	// --------------------------이동키
	case 'j':
		Mainswingchk = 2;
		AngleList.BodyAngle = 180.0f;
		AngleList.ArmAngle = 180.0f;
		TransList.T_Bodyx -= 0.08f;
		TransList.T_ArmLegx -= 0.08f;
		break;

	case 'i':
		Mainswingchk = 1;
		AngleList.BodyAngle = 0.0f;
		AngleList.ArmAngle = 0.0f;
		TransList.T_Bodyz -= 0.06f;
		TransList.T_ArmLegz -= 0.06f;
		break;

	case 'l':
		Mainswingchk = 2;
		AngleList.BodyAngle = -180.0f;
		AngleList.ArmAngle = -180.0f;
		TransList.T_ArmLegx += 0.08f;
		TransList.T_Bodyx += 0.08f;
		break;

	case 'k':
		Mainswingchk = 1;
		AngleList.BodyAngle = 0.0f;
		AngleList.ArmAngle = 0.0f;
		TransList.T_Bodyz += 0.06f;
		TransList.T_ArmLegz += 0.06f;
		break;
	// 점프
	case 'm':
		JumpState =!JumpState;
		jumpcheck = 0;
		break;

	case 's':
		ResetCollection();
		break;
	case 'q':
		exit(0);
		break;
	}
}

void timer(int value)
{
	if (ycheck == true)
		AngleList.AngleRevoly += 2.0f;
	if (LightBoxRotateM)
		AngleList.LightRadian -= 1.5f;
	if (LightBoxRotateP)
		AngleList.LightRadian += 1.5f;
	if (CameraRotateP)
		AngleList.anglecamera += 2.5f;
	if (CameraRotateM)
		AngleList.anglecamera -= 2.5f;

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


	if (LightOnOff == true) {
		LightColor.x = 0.903922; 
		LightColor.y= 0.852941;
		LightColor.z=0.790196;
	}

	if (LightOnOff == false) {
		LightColor.x = 0.1f;
		LightColor.y = 0.1f;
		LightColor.z = 0.1f;
	}

	if (JumpState == true)
	{
		if (jumpcheck==0) {
			
			Scalepos.My =0.00f;
			TransList.T_Bodyy += 0.05f;
			TransList.T_ArmLegy += 0.05f;
			TransList.T_hairy += 0.06f;
			if (TransList.T_Bodyy >= 0.5f) {
				TransList.T_Bodyy -= 0.05f;
				TransList.T_ArmLegy -= 0.05f;
				TransList.T_hairy -= 0.06f;
				jumpcheck = 1;
			}
		}
		if (jumpcheck==1) {
		
			TransList.T_Bodyy -= 0.05f;
			TransList.T_ArmLegy -= 0.05f;
			TransList.T_hairy -=0.06f;
			Scalepos.My -= 0.015f;
			if (TransList.T_Bodyy<-0.2f) {
				TransList.T_Bodyy += 0.05f;
				TransList.T_ArmLegy += 0.05f;
				TransList.T_hairy += 0.06f;
				jumpcheck = 0;
			}
		}
	}
	else
	{
		Scalepos.My = 0.00f;
		TransList.T_Bodyy = -0.1f;
		TransList.T_ArmLegy = 0.25f;
		TransList.T_hairy = -0.1f;
	}

	if (transcheck1 == 1 || Change1 == true)
	{
		if (TransList.T_r1x < TransList.T_Bodyx) {
			TransList.T_r1x += 0.1f;
			if (TransList.T_r1x > TransList.T_Bodyx - 0.5f)
				TransList.T_r1x -= 0.1f;
		}
		if (TransList.T_r1x > TransList.T_Bodyx) {
			TransList.T_r1x -= 0.1f;
			if (TransList.T_r1x < TransList.T_Bodyx +0.5f)
				TransList.T_r1x += 0.1f;

		}
		if (TransList.T_r1z < TransList.T_Bodyz) {
			TransList.T_r1z += 0.1f;
			if (TransList.T_r1z > TransList.T_Bodyz -0.5f)
				TransList.T_r1z -= 0.1f;
		}
		if (TransList.T_r1z > TransList.T_Bodyz) {
			TransList.T_r1z -= 0.1f;
			if (TransList.T_r1z < TransList.T_Bodyz +0.5f)
				TransList.T_r1z += 0.1f;
		}
	}


	if (transcheck2 == 1)
	{
		if (TransList.T_r2x < TransList.T_Bodyx)
		{
			TransList.T_r2x += 0.12f;
			if (TransList.T_r2x > TransList.T_Bodyx - 1.0f)
				TransList.T_r2x -= 0.12f;
		}
		if (TransList.T_r2x > TransList.T_Bodyx)
		{
			TransList.T_r2x -= 0.12f;
			if (TransList.T_r2x < TransList.T_Bodyx +1.0f)
				TransList.T_r2x += 0.12f;

		}
		if (TransList.T_r2z < TransList.T_Bodyz)
		{
			TransList.T_r2z += 0.12f;
			if (TransList.T_r2z > TransList.T_Bodyz - 1.0f)
				TransList.T_r2z -= 0.12f;
		}
		if (TransList.T_r2z > TransList.T_Bodyz)
		{
			TransList.T_r2z -= 0.12f;
			if (TransList.T_r2z < TransList.T_Bodyz + 1.0f)
				TransList.T_r2z += 0.12f;

		}
	}
	if (transcheck3 == 1)
	{

		if (TransList.T_r3x < TransList.T_Bodyx)
		{
			TransList.T_r3x += 0.13f;
			if (TransList.T_r3x > TransList.T_Bodyx - 1.5f)
				TransList.T_r3x -= 0.13f;
		}
		if (TransList.T_r3x > TransList.T_Bodyx)
		{
			TransList.T_r3x -= 0.13f;
			if (TransList.T_r3x < TransList.T_Bodyx + 1.5f)
				TransList.T_r3x += 0.13f;
		}
		if (TransList.T_r3z < TransList.T_Bodyz)
		{
			TransList.T_r3z += 0.13f;
			if (TransList.T_r3z > TransList.T_Bodyz - 1.5f)
				TransList.T_r3z -= 0.13f;
		}
		if (TransList.T_r3z > TransList.T_Bodyz)
		{
			TransList.T_r3z -= 0.13f;
			if (TransList.T_r3z < TransList.T_Bodyz + 1.5f)
				TransList.T_r3z += 0.13f;
		}
	}
	if (transcheck4 == 1)
	{
		if (TransList.T_r4x < TransList.T_Bodyx)
		{
			TransList.T_r4x += 0.14f;
			if (TransList.T_r4x > TransList.T_Bodyx - 2.0f) {
				TransList.T_r4x -= 0.14f; }
		}
		if (TransList.T_r4x > TransList.T_Bodyx) {
			TransList.T_r4x -= 0.14f;
			if (TransList.T_r4x < TransList.T_Bodyx + 2.0f) {
				TransList.T_r4x += 0.14f;}
		}
		if (TransList.T_r4z < TransList.T_Bodyz) {
			TransList.T_r4z += 0.14f;
			if (TransList.T_r4z > TransList.T_Bodyz - 2.0f) {
				TransList.T_r4z -= 0.14f; }
		}
		if (TransList.T_r4z > TransList.T_Bodyz) {
			TransList.T_r4z -= 0.14f;
			if (TransList.T_r4z < TransList.T_Bodyz + 2.0f) {
				TransList.T_r4z += 0.14f; }
		}
	}

	if (TrapRotate == true)
		AngleList.AngleTrap -= 40.0f;

	if (snowcheck == true)
	{
		for (int i = 0; i < 50; i++) {
			SLocation[i].y -= SnowSpeed[i].y;
			if (SLocation[i].y <= 0.0f) 
				SLocation[i].y = SaveLocation[i].y;
		}
	}
	

	glutPostRedisplay();
	glutTimerFunc(60, timer, 1);
}
void ReadObj()
{

	readobjNomal("Model/Semi/cube.obj", ObjVertexVal[0], ObjNomarVal[0]);
	readobjNomal("Model/Semi/Sphere2.obj", ObjVertexVal[1], ObjNomarVal[1]);
	for (int i = 2; i < 9; i++)
	{
		readobjNomal("Model/Semi/cube.obj", ObjVertexVal[i], ObjNomarVal[i]);
	}
	for (int i = 9; i < 37; i++) {
		if (i == 9 || i == 14 || i == 19 || i == 24 || i == 29) {
			readobjNomal("Model/Semi/j_body.obj", ObjVertexVal[i], ObjNomarVal[i]);
		}
		else {
			readobjNomal("Model/Semi/cube.obj", ObjVertexVal[i], ObjNomarVal[i]);
		}
	}
	readobjNomal("Model/Semi/Sphere2.obj", ObjVertexVal[37], ObjNomarVal[37]);

}
int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(FRAME_WIDTH,FRAME_HEIGHT);
	glutCreateWindow("Homework2");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cerr << "NOT INIT" << endl;
	else cout << "INIT<<endl";
	ReadObj();
	cout << "r/R : 조명 양/음 회전 "<<endl;
	cout << "t : 조명 끄고 키기" << endl;
	cout << "z/Z/x/X : 카메라 상하좌우 이동 " << endl;
	cout << "c/C : 카메라 y축기준 양/음 회전" << endl;
	cout << "j/l/k/i : 상하좌우 이동키" << endl;
	cout << "m : 점프 " << endl;
	cout << "s : 초기화 " << endl;
	cout << "q : 종료 " << endl;

	SnowPlay();
	makeShader(vn,fn,shaderID);
	InitBuffer();
	glutKeyboardFunc(KeyBoard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, timer, 1);
	glutReshapeFunc(Resize);
	glutMainLoop();

	return 0;
}



void ResetCollection()
{
	ycheck = true;
	xcheck = false;
	solidchk = true;
	LightBoxRotateM = false;
	LightBoxRotateP = false;
	CameraRotateP = false;
	CameraRotateM = false;
	rotchk = false;
	swingAngle1 = true;
	swingAngle2 = false;
	MainswingAngle1 = true;
	MainswingAngle2 = false;
	LightOnOff = true;
	Change1 = false;
	Change2 = false;
	Change3 = false;
	Change4 = false;
	TrapRotate = true;
	snowcheck = true;
	JumpState = false;
	AngleList.angle = 0.0f;
	AngleList.anglex = 0.0f;
	AngleList.angley = 0.0f;
	AngleList.AngleTrap = 0.0f;
	AngleList.Radian = 0.0f;
	AngleList.AngleRevolx = 45.0f;
	AngleList.AngleRevoly = 45.0f;
	AngleList.anglecamera = 0.0f;
	AngleList.anglecamera2 = 0.0f;
	AngleList.ObjAngle = 20.0f;
	AngleList.LightRadian = 210.0f;
	AngleList.BodyAngle = 0.0f;
	AngleList.ArmAngle = 0.0f;
	AngleList.SwingAngle1 = 0.0f;
	AngleList.SwingAngle2 = 0.0f;
	AngleList.MainSwing1 = 0.0f;
	AngleList.MainSwing2 = 0.0f;
	Scalepos.X = 0.0f;
	Scalepos.Y = 4.5f;
	Scalepos.Z = 6.5f;
	Scalepos.x = 2.0f;
	Scalepos.y = 2.0f;
	Scalepos.z = 2.0f;
	Scalepos.Mx = 0.0f;
	Scalepos.My = 0.0f;
	Scalepos.Mz = 0.0f;
	TransList.T_r1x = 4.0f;
	TransList.T_r1y = 0.0f;
	TransList.T_r1z = -4.0f;
	TransList.T_r2x = -4.0f;
	TransList.T_r2y = 0.0f;
	TransList.T_r2z = -4.0f;
	TransList.T_r3x = -2.0f;
	TransList.T_r3y = 0.0f;
	TransList.T_r3z = 0.0f;
	TransList.T_r4x = 2.0f;
	TransList.T_r4y = 0.0f;
	TransList.T_r4z = 0.0f;
	TransList.T_x = 0.0f;
	TransList.T_y = 0.8f;
	TransList.T_z = 0.0f;
	TransList.T_X = 0.0f;
	TransList.T_Y = -0.3f;
	TransList.T_Z = 0.0f;
	TransList.T_Trapx = 0.0f;
	TransList.T_Trapy = 0.1f;
	TransList.T_Trapz = 0.0f;
	TransList.T_Bodyx = 0.0f;
	TransList.T_Bodyy = -0.1f;
	TransList.T_Bodyz = -2.0f;
	TransList.T_hairy = -0.1f;
	TransList.T_ArmLegx = 0.0f;
	TransList.T_ArmLegy = 0.25f;
	TransList.T_ArmLegz = 0.0f;
	Camerapos.C_x = 1.0f;
	Camerapos.C_y = 4.0f;
	Camerapos.C_z = 10.0f;
	transcheck1 = 0;
	transcheck2 = 0;
	transcheck3 = 0;
	transcheck4 = 0;
}