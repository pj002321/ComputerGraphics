#include "stdafx.h"
#include "readobjNomal.h"
using namespace std;

char vn[64] = "Shader/vertexlighting.glsl";
char fn[64] = "Shader/fragmentlighting.glsl";

GLvoid Viewport(GLvoid);
GLvoid keyboard(unsigned char key, int x, int y);

void initbuffer();
void timer(int value);
void drawscene();
void MakeCircle();

GLuint VAO[4], VBO[8];
GLuint shaderID;

vector<float>CircleVal;
vector<float>BoxCircleVal;
vector<glm::vec4>ObjVertexVal[3];
vector<glm::vec4>ObjNomarVal[3];
glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);

int LightboxRotate = 0;
bool CameraRotateP = false;
bool ObjRotate2 = false;
bool makecircle = true;
bool CameraRotate1 = false;
bool CameraRotate2 = false;
bool SquareRotatecheck1 = false;
bool SquareRotatecheck2 = false;
bool LightBoxRotateP = false;
bool LightBoxRotateM = false;
bool LightRotateB = false;
bool Shapechange = true;

struct Camera {
	float C_x = -2.0f;
	float C_y = 3.0f;
	float C_z = 6.0f;

}Camerapos;

struct Angle
{
	float anglecamera = 0.0f;
	float anglecamera2 = 0.0f;
	float ObjAngle = 20.0f;
	float LightAngle = 10.0f;
}AngleList;

struct Light {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

}BoxRotate;

struct Scale
{
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 3.0f;

	float x = 1.2f;
	float y = 1.2f;
	float z = 1.2f;
}Scalepos;


void drawscene() {

	if (Shapechange) {
		glBindVertexArray(VAO[0]);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(AngleList.ObjAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(Scalepos.x, Scalepos.y, Scalepos.z));
		unsigned int modelLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glm::mat4 Normalmodel = glm::mat4(1.0f);
		Normalmodel = glm::rotate(Normalmodel, glm::radians(AngleList.ObjAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int NormalmodelLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(NormalmodelLocation, 1, GL_FALSE, glm::value_ptr(Normalmodel));
		unsigned int objColorLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(objColorLocation, 0.62f, 0.55f, 0.32f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[0].size());
	}
	else {

		glBindVertexArray(VAO[1]);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(AngleList.ObjAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(Scalepos.x, Scalepos.y, Scalepos.z));
		unsigned int modelLocation = glGetUniformLocation(shaderID, "modeltransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glm::mat4 Normalmodel = glm::mat4(1.0f);
		Normalmodel = glm::rotate(Normalmodel, glm::radians(AngleList.ObjAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int NormalmodelLocation = glGetUniformLocation(shaderID, "normaltransform");
		glUniformMatrix4fv(NormalmodelLocation, 1, GL_FALSE, glm::value_ptr(Normalmodel));
		unsigned int objColorLocation = glGetUniformLocation(shaderID, "objColor");
		glUniform3f(objColorLocation, 0.62f, 0.60f, 0.38f);
		glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[1].size());
	}



	glBindVertexArray(VAO[2]);
	glm::mat4 LightBox = glm::mat4(1.0f);
	LightBox = glm::rotate(LightBox, glm::radians(AngleList.LightAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	LightBox = glm::translate(LightBox, glm::vec3(0.0f, 0.0f, Scalepos.Z));
	LightBox = glm::scale(LightBox, glm::vec3(1.0f, 1.0f, 1.0f));
	unsigned int LightBoxLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(LightBoxLocation, 1, GL_FALSE, glm::value_ptr(LightBox));
	glm::mat4 LightBoxNormalmodel = glm::mat4(1.0f);
	LightBoxNormalmodel = glm::rotate(LightBoxNormalmodel, glm::radians(AngleList.LightAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int LightBoxNormalmodelLocation = glGetUniformLocation(shaderID, "normaltransform");
	glUniformMatrix4fv(LightBoxNormalmodelLocation, 1, GL_FALSE, glm::value_ptr(LightBoxNormalmodel));
	unsigned int LightBoxColorLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(LightBoxColorLocation, 0.4f, 0.2f, 0.1f);
	glDrawArrays(GL_TRIANGLES, 0, ObjVertexVal[2].size());


	glBindVertexArray(VAO[3]);
	glm::mat4 OrbitalModel = glm::mat4(1.0f);
	OrbitalModel = glm::scale(OrbitalModel, glm::vec3(Scalepos.Z, 0.0f, Scalepos.Z));
	unsigned int OrbitalModelModelLocation = glGetUniformLocation(shaderID, "modeltransform");
	glUniformMatrix4fv(OrbitalModelModelLocation, 1, GL_FALSE, glm::value_ptr(OrbitalModel));
	unsigned int OrbitalModelLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3f(OrbitalModelLocation, 0.6f, 0.6f, 0.5f);
	glLineWidth(2.0f);
	glDrawArrays(GL_LINE_STRIP, 0, CircleVal.size() / 6);




}
void MakeCircle()
{
	float c_x, c_z;
	for (int i = 0; i < 360; i++)
	{
		float r = 1.0;
		c_x = r * cos(3.14 * i / 180);
		c_z = r * sin(3.14 * i / 180);

		CircleVal.push_back(c_x);
		CircleVal.push_back(0.0f);
		CircleVal.push_back(c_z);
		CircleVal.push_back(0.0f);
		CircleVal.push_back(1.0f);
		CircleVal.push_back(0.0f);
	}
	for (int i = 0; i < 360; i++)
	{
		float r = 1.0;
		c_x = r * cos(3.14 * i / 180);
		c_z = r * sin(3.14 * i / 180);

		BoxCircleVal.push_back(c_x);
		BoxCircleVal.push_back(0.0f);
		BoxCircleVal.push_back(c_z);
		BoxCircleVal.push_back(0.0f);
		BoxCircleVal.push_back(1.0f);
		BoxCircleVal.push_back(0.0f);
	}
}
GLvoid Viewport()
{
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

		LightPosition = glm::rotate(LightPosition, glm::radians(AngleList.LightAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		LightPosition = glm::translate(LightPosition, glm::vec3(Scalepos.X, Scalepos.Y, Scalepos.Z - 1.0f));
		glm::vec4 LightPosDis = glm::vec4(1.0f);
		LightPosDis = LightPosition * LightPosDis;
		glm::vec3 LightPos
			= glm::vec3(LightPosDis.x, LightPosDis.y, LightPosDis.z);
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

	for (int i = 0; i < 3; i++)
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

	if (makecircle)
	{
		MakeCircle();
		makecircle = false;
	}
	glBindVertexArray(VAO[3]);
	glGenBuffers(2, &VBO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * CircleVal.size(), &CircleVal[0], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * CircleVal.size(), &CircleVal[0], GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'n':
		Shapechange = !Shapechange;
		break;
	case 'y':
		CameraRotateP = !CameraRotateP;
		ObjRotate2 = false;
		break;
	case 'Y':
		ObjRotate2 = !ObjRotate2;
		CameraRotateP = false;
		break;
	case 'z':
		Scalepos.Z += 0.3f;
		makecircle = true;
		break;
	case 'Z':
		Scalepos.Z -= 0.3f;
		makecircle = true;
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
	case '1':
		CameraRotate1 = true;
		break;
	case '2':
		CameraRotate2 = true;
		break;
	case 'r':
		LightBoxRotateM = false;
		LightBoxRotateP = !LightBoxRotateP;
		break;
	case 'R':
		LightBoxRotateP = false;
		LightBoxRotateM = !LightBoxRotateM;
		break;
	case 'c':
		CameraRotateP = false;
		ObjRotate2 = false;
		makecircle = true;
		CameraRotate1 = false;
		CameraRotate2 = false;
		SquareRotatecheck1 = false;
		SquareRotatecheck2 = false;
		LightBoxRotateM = false;
		LightRotateB = false;
		Shapechange = true;
		Camerapos.C_x = -2.0f;
		Camerapos.C_y = 3.0f;
		Camerapos.C_z = 6.0f;
		AngleList.LightAngle = 10.0f;
		AngleList.anglecamera = 0.0f;
		AngleList.anglecamera2 = 0.0f;
		AngleList.ObjAngle = 20.0f;
		Scalepos.X = 0.0f;
		Scalepos.Y = 0.0f;
		Scalepos.Z = 3.0f;
		Scalepos.x = 1.2f;
		Scalepos.y = 1.2f;
		Scalepos.z = 1.2f;
		break;
	case 'q':
		exit(0);
		break;
	}
	glutPostRedisplay();
}
void timer(int value) {
	if (CameraRotateP) {
		AngleList.ObjAngle++;
	}
	if (ObjRotate2) {
		AngleList.ObjAngle--;
	}
	if (LightBoxRotateP)
	{
		BoxRotate.x = BoxCircleVal[6 * LightboxRotate];
		BoxRotate.y = BoxCircleVal[6 * LightboxRotate + 1];
		BoxRotate.z = BoxCircleVal[6 * LightboxRotate + 2];

		LightboxRotate++;
		AngleList.LightAngle -= 1.0f;
		if (LightboxRotate == 360)
		{
			LightboxRotate = 0;
		}
	}

	if (LightBoxRotateM)
	{
		BoxRotate.x = BoxCircleVal[6 * LightboxRotate];
		BoxRotate.y = BoxCircleVal[6 * LightboxRotate + 1];
		BoxRotate.z = BoxCircleVal[6 * LightboxRotate + 2];

		LightboxRotate++;
		AngleList.LightAngle += 1.0f;
		if (LightboxRotate == 360)
		{
			LightboxRotate = 0;
		}
	}

	if (CameraRotate1 == true)
	{
		AngleList.anglecamera += 2.0f;
	}
	if (CameraRotate2 == true)
	{
		AngleList.anglecamera2 += 2.0f;
	}


	glutPostRedisplay();
	glutTimerFunc(10, timer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);

	glutCreateWindow("opengl24");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cerr << "Unable to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		cout << "GLEW initialized" << endl;
	}
	readobjNomal("Model/24-25/cube.obj", ObjVertexVal[0], ObjNomarVal[0]);
	readobjNomal("Model/24-25/pyramid.obj", ObjVertexVal[1], ObjNomarVal[1]);
	readobjNomal("Model/24-25/cube.obj", ObjVertexVal[2], ObjNomarVal[2]);


	makeShader(vn,fn,shaderID);
	initbuffer();
	glutDisplayFunc(Viewport);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1, timer, 1);
	glutReshapeFunc(Resize);
	glutMainLoop();
}