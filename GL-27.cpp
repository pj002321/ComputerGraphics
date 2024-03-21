#include "stdafx.h"
#include "readobjNomal.h"
using namespace std;
char vn[64] = "Shader/vertexlighting.glsl";
char fn[64] = "Shader/fragmentlighting.glsl";
void timer(int value);
GLvoid InitBuffer();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char Key, int x, int y);

GLuint VAO[10], VBO[20];
GLuint shaderID;
GLint width, height;

vector<glm::vec4>ObjNomarVal[7];
vector<glm::vec4>ObjVertexVal[7];
glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);

bool rotchk = false;
int check = 0;
bool ycheck = false;
bool xcheck = false;
bool solidchk = true;
bool LightBoxRotateM = false;
bool LightBoxRotateP = false;
bool snowcheck = false;
int Practerversion = 0;
int RotateStatex = 0;
int RotateStatey = 0;
int theta = 180;
int SierpinskiCount = 0;

float cx, cy, cz;
float r = 3.0f;
float r1 = 3.0f;
float r2 = 3.0f;
float Seperate = -2.0f;

int mainrotate = 0;
int mainrotate2 = 0;
int mainrotate3 = 0;

float MainA_y = 0.0f;
float MainA_x = 7.0f;
float MainA_z = 0.0f;
float MainT_x = 0.0f;
float MainT_y = 1.5f;
float MainT_z = 0.0f;

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

struct Camera
{
	float C_x = 0.0f;
	float C_y = 0.0f;
	float C_z = 8.0f;

}Camerapos;

struct Angle
{
	float angle = 20.0f;
	float anglex = 0.0f;
	float angley = 0.0f;
	float anglecamera = 180.0f;
	float anglecamera2 = 0.0f;
	float LightRadian = 180.0f;
	float ObjAngle = 20.0f;
	float LightAngle = 10.0f;

}AngleList;

struct Scale
{
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 5.0f;

	float x = 2.0f;
	float y = 2.0f;
	float z = 2.0f;
}Scalepos;

struct Transration
{

	float T_x = 0.0f;
	float T_y = -1.5f;
	float T_z = 0.0f;
	float  T_X = 0.0f;
	float  T_Y = -2.0f;
	float  T_Z = 0.0f;
	float snowx = 0.0f;
	float snowy = 4.0f;
	float snowz = 0.0f;

}TransList;

void Make_spinprogram()
{

	float r_color, g_color, b_color;
	r_color = 0.5, g_color = 1.0, b_color = 0.3;
	for (int i = 0; i < theta * 2.0f; i++)
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

	for (int i = 0; i < theta * 2.0f; i++)
	{
		cx = r1 * cos(3.14 * i / theta);
		cy = (-r1) * cos(3.14 * i / theta);
		cz = r1 * sin(3.14 * i / theta);

		maincircle2.push_back(cx);
		maincircle2.push_back(cy);
		maincircle2.push_back(cz);
		maincircle2.push_back(0);
		maincircle2.push_back(0);
		maincircle2.push_back(0);

	}
	for (int i = 0; i < theta * 2; i++)
	{
		cx = r2 * cos(3.14 * i / theta);
		cy = r2 * cos(3.14 * i / theta);
		cz = r2 * sin(3.14 * i / theta);

		maincircle3.push_back(cx);
		maincircle3.push_back(cy);
		maincircle3.push_back(cz);
		maincircle3.push_back(0);
		maincircle3.push_back(0);
		maincircle3.push_back(0);

	}


}

GLvoid InitBuffer()
{

	if (rotchk == true)
	{
		Make_spinprogram();
		rotchk = false;
	}

	glGenVertexArrays(9, VAO);


	for (int i = 0; i < 7; i++)
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
	glBindVertexArray(VAO[7]);
	glGenBuffers(2, &VBO[10]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle1.size(), &maincircle1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[11]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle1.size(), &maincircle1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[8]);
	glGenBuffers(2, &VBO[12]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[12]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle2.size(), &maincircle2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[13]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle2.size(), &maincircle2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[9]);
	glGenBuffers(2, &VBO[14]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[14]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle3.size(), &maincircle3[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[15]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maincircle3.size(), &maincircle3[0], GL_STATIC_DRAW);
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
	if (check == 2)
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

	if (LightBoxRotateM)
	{
		AngleList.LightRadian -= 3.0f;
	}
	if (LightBoxRotateP)
	{
		AngleList.LightRadian += 3.0f;
	}

	if (snowcheck == true)
	{

		TransList.snowy -= 0.05f;

		if (TransList.snowy <= -2.5f)
		{
			TransList.snowy = 6.0f;
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
	mainrotate++;
	mainrotate2++;
	mainrotate3++;

	if (mainrotate == 360) {
		mainrotate = 0;
	}
	if (mainrotate2 == 120) {
		mainrotate2 = 0;
	}
	if (mainrotate3 == 180) {
		mainrotate3 = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(60, timer, 1);
}
void Sierpinski(int _Count, int _Seperate, float _x, float _y, float _z)
{
	if (_Count == 0)
	{
		glBindVertexArray(VAO[1]);
		glm::mat4 Pyramid = glm::mat4(1.0f);
		Pyramid = glm::rotate(Pyramid, glm::radians(AngleList.ObjAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		Pyramid = glm::translate(Pyramid, glm::vec3(_x, _y - 0.5f, _z));
		Pyramid = glm::scale(Pyramid, glm::vec3(powf(0.5, _Seperate), powf(0.5, _Seperate), powf(0.5, _Seperate)));
		unsigned int PyramidLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(PyramidLocation, 1, GL_FALSE, glm::value_ptr(Pyramid));
		unsigned int PyramidfragLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(PyramidfragLocation, 0.524f, 0.651f, 0.432f);
		glm::mat4 PyramidNormal = glm::mat4(1.0f);
		PyramidNormal = glm::rotate(PyramidNormal, glm::radians(AngleList.ObjAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		Pyramid = glm::translate(Pyramid, glm::vec3(_x, _y, _z));
		unsigned int PyramidNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(PyramidNormalLocation, 1, GL_FALSE, glm::value_ptr(PyramidNormal));
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[1].size());
	}
	else
	{
		Sierpinski(_Count - 1, _Seperate, _x + powf(0.5, (_Seperate - _Count + 2)), _y,
			_z + powf(0.5, _Seperate - _Count + 2));
		Sierpinski(_Count - 1, _Seperate, _x + powf(0.5, (_Seperate - _Count + 2)), _y,
			_z - powf(0.5, _Seperate - _Count + 2));
		Sierpinski(_Count - 1, _Seperate, _x - powf(0.5, (_Seperate - _Count + 2)), _y,
			_z - powf(0.5, _Seperate - _Count + 2));
		Sierpinski(_Count - 1, _Seperate, _x - powf(0.5, (_Seperate - _Count + 2)), _y,
			_z + powf(0.5, _Seperate - _Count + 2));
		Sierpinski(_Count - 1, _Seperate, _x, _y + powf(0.5, (_Seperate - _Count + 1)),
			_z);
	}
}


void drawScene()
{

	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderID);

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

	{//--------원근
		glm::mat4 Proj = glm::mat4(1.0f);
		Proj = glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 100.0f);
		unsigned int ModelProjLocation = glGetUniformLocation(shaderID, "projectiontransform");
		glUniformMatrix4fv(ModelProjLocation, 1, GL_FALSE, &Proj[0][0]);
	}

	{//--------조명
		glm::mat4 LightPosition = glm::mat4(1.0f);
		LightPosition = glm::rotate(LightPosition, glm::radians(AngleList.LightRadian), glm::vec3(0.0f, 0.5f, 0.0f));
		LightPosition = glm::translate(LightPosition, glm::vec3(Scalepos.X, Scalepos.Y + 0.4f, Scalepos.Z - 1.0f));
		unsigned int lightPosLocation = glGetUniformLocation(shaderID, "LightPos");
		glUniform3fv(lightPosLocation, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
		unsigned int lightColorLocation = glGetUniformLocation(shaderID, "LightColor");
		glUniform3fv(lightColorLocation, 1, glm::value_ptr(LightColor));
		unsigned int LightTransformLocation = glGetUniformLocation(shaderID, "LightTransform");
		glUniformMatrix4fv(LightTransformLocation, 1, GL_FALSE, glm::value_ptr(LightPosition));
	}
	glBindVertexArray(VAO[0]);
	glm::mat4 BaseObj = glm::mat4(1.0f);
	BaseObj = glm::rotate(BaseObj, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	BaseObj = glm::translate(BaseObj, glm::vec3(TransList.T_X, TransList.T_Y, TransList.T_z));
	BaseObj = glm::scale(BaseObj, glm::vec3(8.0f, 0.05f, 8.0f));
	unsigned int BaseobjLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(BaseobjLocation, 1, GL_FALSE, glm::value_ptr(BaseObj));
	glm::mat4 BaseObjNormal = glm::mat4(1.0f);
	BaseObjNormal = glm::rotate(BaseObjNormal, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int BaseObjNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(BaseObjNormalLocation, 1, GL_FALSE, glm::value_ptr(BaseObjNormal));
	unsigned int BaseobjfragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(BaseobjfragLocation, 0.214f, 0.225f, 0.326f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[0].size());

	Sierpinski(SierpinskiCount, Seperate, TransList.T_X, TransList.T_Y, TransList.T_z);

	glBindVertexArray(VAO[2]);
	glm::mat4 EarthShpere = glm::mat4(1.0f);
	EarthShpere = glm::rotate(EarthShpere, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	EarthShpere = glm::rotate(EarthShpere, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	EarthShpere = glm::translate(EarthShpere, glm::vec3(MainT_x, MainT_y, MainT_z));
	EarthShpere = glm::translate(EarthShpere, glm::vec3(mainTrans1_x, mainTrans1_y, mainTrans1_z));
	EarthShpere = glm::rotate(EarthShpere, glm::radians(mainAngle_x), glm::vec3(1.0f, 0.0f, 0.0f));
	EarthShpere = glm::rotate(EarthShpere, glm::radians(mainAngle_x), glm::vec3(0.0f, 1.0f, 0.0f));
	EarthShpere = glm::scale(EarthShpere, glm::vec3(0.3f, 0.3f, 0.3f));
	unsigned int EarthShpereLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(EarthShpereLocation, 1, GL_FALSE, glm::value_ptr(EarthShpere));
	unsigned int EarthShperefragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(EarthShperefragLocation, 0.3f, 0.3f, 0.7f);
	glm::mat4 EarthShpereNormal = glm::mat4(1.0f);
	EarthShpereNormal = glm::rotate(EarthShpereNormal, glm::radians(AngleList.angley), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int EarthShpereNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(EarthShpereNormalLocation, 1, GL_FALSE, glm::value_ptr(EarthShpereNormal));
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[2].size());

	glBindVertexArray(VAO[3]);
	glm::mat4 MercuryShpere = glm::mat4(1.0f);
	MercuryShpere = glm::rotate(MercuryShpere, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MercuryShpere = glm::rotate(MercuryShpere, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	MercuryShpere = glm::translate(MercuryShpere, glm::vec3(MainT_x, MainT_y, MainT_z));
	MercuryShpere = glm::translate(MercuryShpere, glm::vec3(mainTrans2_x, mainTrans2_y, mainTrans2_z));
	MercuryShpere = glm::rotate(MercuryShpere, glm::radians(mainAngle_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MercuryShpere = glm::rotate(MercuryShpere, glm::radians(mainAngle_y), glm::vec3(0.0f, 1.0f, 0.0f));
	MercuryShpere = glm::scale(MercuryShpere, glm::vec3(0.4f, 0.4f, 0.4f));
	unsigned int MercuryShpereLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(MercuryShpereLocation, 1, GL_FALSE, glm::value_ptr(MercuryShpere));
	unsigned int MercuryShperefragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(MercuryShperefragLocation, 0.60f, 0.76f, 0.92f);
	glm::mat4 MercuryShpereNormal = glm::mat4(1.0f);
	MercuryShpereNormal = glm::rotate(MercuryShpereNormal, glm::radians(AngleList.angley), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int MercuryShpereNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(MercuryShpereNormalLocation, 1, GL_FALSE, glm::value_ptr(MercuryShpereNormal));
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[3].size());

	glBindVertexArray(VAO[4]);
	glm::mat4 VenusSphere = glm::mat4(1.0f);
	VenusSphere = glm::rotate(VenusSphere, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	VenusSphere = glm::rotate(VenusSphere, glm::radians(MainA_y), glm::vec3(0.0f, 1.0f, 0.0f));
	VenusSphere = glm::translate(VenusSphere, glm::vec3(MainT_x, MainT_y, MainT_z));
	VenusSphere = glm::translate(VenusSphere, glm::vec3(mainTrans3_x, mainTrans3_y, mainTrans3_z));
	VenusSphere = glm::rotate(VenusSphere, glm::radians(mainAngle_x), glm::vec3(1.0f, 0.0f, 0.0f));
	VenusSphere = glm::rotate(VenusSphere, glm::radians(mainAngle_y), glm::vec3(0.0f, 1.0f, 0.0f));
	VenusSphere = glm::scale(VenusSphere, glm::vec3(0.5f, 0.5f, 0.5f));
	unsigned int VenusSphereLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(VenusSphereLocation, 1, GL_FALSE, glm::value_ptr(VenusSphere));
	unsigned int VenusSpherefragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(VenusSpherefragLocation, 0.8632f, 0.3543f, 0.4482f);
	glm::mat4 VenusSphereNormal = glm::mat4(1.0f);
	MercuryShpereNormal = glm::rotate(VenusSphereNormal, glm::radians(AngleList.angley), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int VenusSphereNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(VenusSphereNormalLocation, 1, GL_FALSE, glm::value_ptr(VenusSphereNormal));
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[4].size());

	glBindVertexArray(VAO[5]);
	glm::mat4 LightBox = glm::mat4(1.0f);
	LightBox = glm::rotate(LightBox, glm::radians(AngleList.LightRadian), glm::vec3(0.0f, 1.0f, 0.0f));
	LightBox = glm::translate(LightBox, glm::vec3(Scalepos.X, Scalepos.Y - 1.0f, Scalepos.Z - 0.5f));
	LightBox = glm::scale(LightBox, glm::vec3(0.5f, 0.5f, 0.5f));
	unsigned int LightBoxLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(LightBoxLocation, 1, GL_FALSE, glm::value_ptr(LightBox));
	glm::mat4 LightBoxNormalmodel = glm::mat4(1.0f);
	LightBoxNormalmodel = glm::rotate(LightBoxNormalmodel, glm::radians(AngleList.LightRadian), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int LightBoxNormalmodelLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(LightBoxNormalmodelLocation, 1, GL_FALSE, glm::value_ptr(LightBoxNormalmodel));
	unsigned int LightBoxColorLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(LightBoxColorLocation, 0.2f, 0.2f, 0.2f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[5].size());


	for (int i = 0; i < 100; i++)
	{
		srand(rand());
		glBindVertexArray(VAO[6]);
		glm::mat4 Snow = glm::mat4(1.0f);
		Snow = glm::translate(Snow, glm::vec3(TransList.snowx + rand() % 60 * 0.1 - 2.5f, TransList.snowy + rand() % 10, TransList.snowz + rand() % 50 * 0.1 - 3.0f));
		Snow = glm::scale(Snow, glm::vec3(0.05f, 0.05f, 0.05f));
		unsigned int SnowLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(SnowLocation, 1, GL_FALSE, glm::value_ptr(Snow));
		glm::mat4 SnowNormalmodel = glm::mat4(1.0f);
		SnowNormalmodel = glm::rotate(SnowNormalmodel, glm::radians(AngleList.LightRadian), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int SnowNormalmodelLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(SnowNormalmodelLocation, 1, GL_FALSE, glm::value_ptr(SnowNormalmodel));
		unsigned int SnowColorLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(SnowColorLocation, 0.958f, 0.958f, 0.958f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[6].size());
	}

	glBindVertexArray(VAO[7]);
	glm::mat4 MainCircle1 = glm::mat4(1.0f);
	MainCircle1 = glm::rotate(MainCircle1, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainCircle1 = glm::rotate(MainCircle1, glm::radians(MainA_y), glm::vec3(0.0f, 0.5, 0.0f));
	MainCircle1 = glm::translate(MainCircle1, glm::vec3(MainT_x, MainT_y, MainT_z));
	unsigned int MainLocation1 = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(MainLocation1, 1, GL_FALSE, glm::value_ptr(MainCircle1));
	unsigned int MainCircle1fragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(MainCircle1fragLocation, 0.6f, 0.6f, 0.5f);
	glLineWidth(1.0f);
	glDrawArrays(GL_LINE_STRIP, 0, maincircle1.size() / 6);


	glBindVertexArray(VAO[8]);
	glm::mat4 MainCircle2 = glm::mat4(1.0f);
	MainCircle2 = glm::rotate(MainCircle2, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainCircle2 = glm::rotate(MainCircle2, glm::radians(MainA_y), glm::vec3(0.0f, 0.3, 0.0f));
	MainCircle2 = glm::translate(MainCircle2, glm::vec3(MainT_x, MainT_y, MainT_z));
	unsigned int MainLocation2 = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(MainLocation2, 1, GL_FALSE, glm::value_ptr(MainCircle2));
	unsigned int MainCircle2fragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(MainCircle2fragLocation, 0.6f, 0.6f, 0.5f);
	glLineWidth(1.0f);
	glDrawArrays(GL_LINE_STRIP, 0, maincircle2.size() / 6);


	glBindVertexArray(VAO[9]);
	glm::mat4 MainCircle3 = glm::mat4(1.0f);
	MainCircle3 = glm::rotate(MainCircle3, glm::radians(MainA_x), glm::vec3(1.0f, 0.0f, 0.0f));
	MainCircle3 = glm::rotate(MainCircle3, glm::radians(MainA_y), glm::vec3(0.0f, 0.4, 0.0f));
	MainCircle3 = glm::translate(MainCircle3, glm::vec3(MainT_x, MainT_y, MainT_z));
	unsigned int MainLocation3 = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(MainLocation3, 1, GL_FALSE, glm::value_ptr(MainCircle3));
	unsigned int MainCircle3fragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(MainCircle3fragLocation, 0.6f, 0.6f, 0.5f);
	glLineWidth(1.0f);
	glDrawArrays(GL_LINE_STRIP, 0, maincircle3.size() / 6);

	glutSwapBuffers();

}

GLvoid KeyBoard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 's':
		snowcheck = true;
		break;
	case 'r':
		LightBoxRotateM = false;
		LightBoxRotateP = !LightBoxRotateP;
		break;
	case 'R':
		LightBoxRotateP = false;
		LightBoxRotateM = !LightBoxRotateM;
		break;
	case 'i':
		Scalepos.Z -= 0.1f;
		break;
	case 'o':
		Scalepos.Z += 0.1f;
		break;
	case '0':
		SierpinskiCount = 0;
		break;
	case '1':
		Seperate = -1.0f;
		TransList.T_y = 1.0f;
		SierpinskiCount = 1;
		Sierpinski(1, Seperate, TransList.T_x, TransList.T_y, TransList.T_z);
		break;
	case '2':
		Seperate = 0.0f;
		SierpinskiCount = 2;
		Sierpinski(SierpinskiCount, Seperate, TransList.T_x, TransList.T_y, TransList.T_z);
		break;
	case '3':
		Seperate = 1.0f;
		SierpinskiCount = 3;
		Sierpinski(SierpinskiCount, Seperate, TransList.T_x, TransList.T_y, TransList.T_z);
		break;
	case '4':
		Seperate = 2.0f;
		SierpinskiCount = 4;
		Sierpinski(SierpinskiCount, Seperate, TransList.T_x, TransList.T_y + 2.0f, TransList.T_z);
		break;
	case '5':
		Seperate = 3.0f;
		SierpinskiCount = 5;
		Sierpinski(SierpinskiCount, Seperate, TransList.T_x, TransList.T_y, TransList.T_z);
		break;
	case '6':
		Seperate = 4.0f;
		SierpinskiCount = 6;
		Sierpinski(SierpinskiCount, Seperate, TransList.T_x, TransList.T_y, TransList.T_z);
		break;
	case '7':
		Seperate = 5.0f;
		SierpinskiCount = 7;
		Sierpinski(SierpinskiCount, Seperate, TransList.T_x, TransList.T_y, TransList.T_z);
		break;
	case '+':
		LightColor += 0.1f;
		break;
	case '-':
		LightColor -= 0.1f;
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
		theta = 180;

		mainrotate = 0;
		mainrotate2 = 0;
		mainrotate3 = 0;


		MainA_y = 0.0f;
		MainA_x = 30.0f;
		MainA_z = 0.0f;
		MainT_x = 0.0f;
		MainT_y = 0.0f;
		MainT_z = 0.0f;

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("27");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "NOT INIT" << endl;
	}
	else
		cout << "INIT<<endl";

	readobjNomal("Model/26-27/cube.obj", ObjVertexVal[0], ObjNomarVal[0]);
	readobjNomal("Model/26-27/pyramid.obj", ObjVertexVal[1], ObjNomarVal[1]);
	readobjNomal("Model/26-27/Sphere2.obj", ObjVertexVal[2], ObjNomarVal[2]);
	readobjNomal("Model/26-27/Sphere2.obj", ObjVertexVal[3], ObjNomarVal[3]);
	readobjNomal("Model/26-27/Sphere2.obj", ObjVertexVal[4], ObjNomarVal[4]);
	readobjNomal("Model/26-27/cube.obj", ObjVertexVal[5], ObjNomarVal[5]);
	readobjNomal("Model/26-27/Sphere2.obj", ObjVertexVal[6], ObjNomarVal[6]);



	rotchk = true;
	makeShader(vn, fn, shaderID);
	InitBuffer();
	glutKeyboardFunc(KeyBoard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(120, timer, 1);
	glutReshapeFunc(Reshape);

	glutMainLoop();

	return 0;
}

