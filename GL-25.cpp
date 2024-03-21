#include "stdafx.h"
#include "readobjNomal.h"

using namespace std;
char vn[64] = "Shader/vertexlighting.glsl";
char fn[64] = "Shader/fragmentlighting.glsl";

void initbuffer();
void timer(int value);
void drawscene();
void MakeCircle();
void RandomLightColor();
GLvoid Viewport(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);

int LightboxRotate = 0;
int LightRandom = 0;
float SquareRotate = 0.0f;
float LightRaidian = 0.0f;
bool CameraRotateP = false;
bool CameraRotateM = false;
bool ObjRotate2 = false;
bool SquareRotatecheck1 = false;
bool SquareRotatecheck2 = false;
bool LightBoxRotateM = false;
bool LightRotateB = false;
bool Shapechange = true;

struct Camera {
	float C_x = 2.0f;
	float C_y = 3.0f;
	float C_z = 6.0f;
}Camerapos;
struct LightObital {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

}BoxRotate;

struct Angle
{
	float anglecamera = 0.0f;
	float anglecamera2 = 0.0f;
	float ObjAngle = 20.0f;
	float LightAngle = 10.0f;
}AngleList;



struct Scale
{
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 5.0f;

	float x = 1.2f;
	float y = 1.2f;
	float z = 1.2f;
}Scalepos;


GLuint VAO[4], VBO[8];
GLuint shaderID;
GLuint qobjshader;
GLuint vertexshader;
GLuint fragmentshader;


vector<vector<glm::vec4>>ObjVertexVal;
vector<vector<glm::vec4>>ObjNomalVal;
vector<float>CircleVal;
vector<float>BoxCircleVal;
glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);

void drawscene() {

	glBindVertexArray(VAO[0]);
	glm::mat4 MainSphere = glm::mat4(1.0f);
	MainSphere = glm::rotate(MainSphere, glm::radians(SquareRotate), glm::vec3(0.0f, 1.0f, 0.0f));
	MainSphere = glm::scale(MainSphere, glm::vec3(1.0f, 1.0f, 1.0f));
	unsigned int MainSphereLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(MainSphereLocation, 1, GL_FALSE, glm::value_ptr(MainSphere));
	glm::mat4 MainSphereNormal = glm::mat4(1.0f);
	MainSphereNormal = glm::rotate(MainSphereNormal, glm::radians(SquareRotate), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int MainSphereNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(MainSphereNormalLocation, 1, GL_FALSE, glm::value_ptr(MainSphereNormal));
	unsigned int MainSpherefargLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(MainSpherefargLocation, 1.01f, 0.22f, 0.23f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[0].size());


	glBindVertexArray(VAO[1]);
	glm::mat4 MidSphere = glm::mat4(1.0f);
	MidSphere = glm::rotate(MidSphere, glm::radians(SquareRotate), glm::vec3(0.0f, 1.0f, 0.0f));
	MidSphere = glm::translate(MidSphere, glm::vec3(-1.75f, 0.0f, 0.0f));
	MidSphere = glm::scale(MidSphere, glm::vec3(0.5f, 0.5f, 0.5f));
	unsigned int MidSphereLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(MidSphereLocation, 1, GL_FALSE, glm::value_ptr(MidSphere));
	glm::mat4 MidSphereNormal = glm::mat4(1.0f);
	MidSphereNormal = glm::rotate(MidSphereNormal, glm::radians(SquareRotate), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int MidSphereNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(MidSphereNormalLocation, 1, GL_FALSE, glm::value_ptr(MidSphereNormal));
	unsigned int MidSpherefragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(MidSpherefragLocation, 0.34f, 0.52f, 0.33f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[1].size());


	glBindVertexArray(VAO[2]);
	glm::mat4 MiniSphere = glm::mat4(1.0f);
	MiniSphere = glm::rotate(MiniSphere, glm::radians(SquareRotate), glm::vec3(0.0f, 1.0f, 0.0f));
	MiniSphere = glm::translate(MiniSphere, glm::vec3(-2.5f, 0.0f, 0.0f));
	MiniSphere = glm::scale(MiniSphere, glm::vec3(0.25f, 0.25f, 0.25f));
	unsigned int MiniSphereLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(MiniSphereLocation, 1, GL_FALSE, glm::value_ptr(MiniSphere));
	glm::mat4 MiniShpereNormal = glm::mat4(1.0f);
	MiniShpereNormal = glm::rotate(MiniShpereNormal, glm::radians(SquareRotate), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int MiniShpereNormalLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(MiniShpereNormalLocation, 1, GL_FALSE, glm::value_ptr(MiniShpereNormal));
	unsigned int MiniSpherefragLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(MiniSpherefragLocation, 0.62f, 0.55f, 0.32f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[2].size());


	glBindVertexArray(VAO[3]);
	glm::mat4 LightBox = glm::mat4(1.0f);
	LightBox = glm::rotate(LightBox, glm::radians(LightRaidian), glm::vec3(0.0f, 1.0f, 0.0f));
	LightBox = glm::translate(LightBox, glm::vec3(Scalepos.X, Scalepos.Y, Scalepos.Z - 1.0f));
	LightBox = glm::scale(LightBox, glm::vec3(0.3f, 0.3f, 0.3f));
	unsigned int LightBoxLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(LightBoxLocation, 1, GL_FALSE, glm::value_ptr(LightBox));
	glm::mat4 LightBoxNormalmodel = glm::mat4(1.0f);
	LightBoxNormalmodel = glm::rotate(LightBoxNormalmodel, glm::radians(LightRaidian), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int LightBoxNormalmodelLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(LightBoxNormalmodelLocation, 1, GL_FALSE, glm::value_ptr(LightBoxNormalmodel));
	unsigned int LightBoxColorLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(LightBoxColorLocation, 0.2f, 0.2f, 0.2f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[3].size());

}

GLvoid Viewport() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
		Proj = glm::perspective(glm::radians(60.0f), (float)FRAME_WIDTH / FRAME_HEIGHT, 0.1f, 100.0f);
		unsigned int ModelProjLocation = glGetUniformLocation(shaderID, "projectiontransform");
		glUniformMatrix4fv(ModelProjLocation, 1, GL_FALSE, &Proj[0][0]);
	}

	{//--------조명
		glm::mat4 LightPosition = glm::mat4(1.0f);
		LightPosition = glm::rotate(LightPosition, glm::radians(LightRaidian), glm::vec3(0.0f, 1.0f, 0.0f));
		LightPosition = glm::translate(LightPosition, glm::vec3(Scalepos.X, Scalepos.Y, Scalepos.Z));
		unsigned int lightPosLocation = glGetUniformLocation(shaderID, "LightPos");
		glUniform3fv(lightPosLocation, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
		unsigned int lightColorLocation = glGetUniformLocation(shaderID, "LightColor");
		glUniform3fv(lightColorLocation, 1, glm::value_ptr(LightColor));
		unsigned int LightTransformLocation = glGetUniformLocation(shaderID, "LightTransform");
		glUniformMatrix4fv(LightTransformLocation, 1, GL_FALSE, glm::value_ptr(LightPosition));
	}
	drawscene();

	glutSwapBuffers();
}


void initbuffer() {
	glGenVertexArrays(4, VAO);

	for (int i = 0; i < 4; i++) {
		glBindVertexArray(VAO[i]);
		glGenBuffers(2, &VBO[2 * i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjVertexVal[i].size(), &ObjVertexVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0); //--- 위치 속성
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2 * i + 1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjNomalVal[i].size(), &ObjNomalVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);
	}
}
void RandomLightColor()
{
	if (LightRandom % 3 == 0)
	{
		LightColor.x = 1.0f;
		LightColor.y = 0.8f;
		LightColor.z = 0.5f;
	}

	else if (LightRandom % 3 == 1)
	{
		LightColor.x = 0.4f;
		LightColor.y = 1.0f;
		LightColor.z = 0.4f;
	}

	else if (LightRandom % 3 == 2)
	{
		LightColor.x = 0.1f;
		LightColor.y = 0.3f;
		LightColor.z = 1.0f;
	}
}
GLvoid keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y':
		CameraRotateP = !CameraRotateP;
		CameraRotateM = false;
		break;
	case 'Y':
		CameraRotateM = !CameraRotateM;
		CameraRotateP = false;
		break;
	case 'z':
		Scalepos.Z += 0.2f;
		break;
	case 'Z':
		Scalepos.Z -= 0.2f;
		break;
	case 'm':
		LightColor.x = 0.2f;
		LightColor.y = 0.2f;
		LightColor.z = 0.2f;
		break;
	case 'M':
		LightColor.x = 1.0f;
		LightColor.y = 1.0f;
		LightColor.z = 1.0f;
		break;
	case 't':
		SquareRotatecheck1 = !SquareRotatecheck1;
		SquareRotatecheck2 = false;
		break;
	case 'T':
		SquareRotatecheck2 = !SquareRotatecheck2;
		SquareRotatecheck1 = false;
		break;
	case 'r':
		LightBoxRotateM = !LightBoxRotateM;
		LightRotateB = false;
		break;
	case 'R':
		LightRotateB = !LightRotateB;
		LightBoxRotateM = false;
		break;
	case 'c':
		RandomLightColor();
		LightRandom++;
		break;
	case 'C':
		LightColor.x = 1.0f;
		LightColor.y = 1.0f;
		LightColor.z = 1.0f;
		LightRandom = 0;
		break;
	case 'q':
		exit(0);
		break;

	}
	glutPostRedisplay();
}

void timer(int value) {
	if (LightBoxRotateM)
		LightRaidian -= 1.5f;
	if (LightRotateB)
		LightRaidian += 1.5f;
	if (CameraRotateP)
		AngleList.anglecamera += 2.0;
	if (CameraRotateM)
		AngleList.anglecamera -= 2.0;
	if (SquareRotatecheck1)
		SquareRotate += 1.0f;
	if (SquareRotatecheck2)
		SquareRotate -= 1.0f;
	glutPostRedisplay();
	glutTimerFunc(1, timer, 1);
}
void ReadModel()
{
	vector<glm::vec4> objTmp;
	vector<glm::vec4> normalTmp;
	for (int i = 0; i < 3; i++) {
		readobjNomal("Model/24-25/pyramid.obj", objTmp, normalTmp);
		ObjVertexVal.push_back(objTmp);
		ObjNomalVal.push_back(normalTmp);
		objTmp.resize(0);
		normalTmp.resize(0);

	}
	readobjNomal("Model/24-25/cube.obj", objTmp, normalTmp);

	ObjVertexVal.push_back(objTmp);
	ObjNomalVal.push_back(normalTmp);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("25");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cerr << "Unable to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		cout << "GLEW initialized" << endl;
	}

	ReadModel();
	makeShader(vn,fn,shaderID);
	initbuffer();
	glutDisplayFunc(Viewport);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1, timer, 1);
	glutReshapeFunc(::Resize);
	glutMainLoop();
}
