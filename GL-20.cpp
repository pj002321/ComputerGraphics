#include "stdafx.h"
#include "readobjNomal.h"

char vn[32] = "Shader/vertex.glsl";
char fn[32] = "Shader/fragment.glsl";

void initbuffer();
void timer(int value);
GLvoid drawscene();
GLvoid keyboard(unsigned char key, int x, int y);
GLvoid ViewPort();

vector<vector<glm::vec4>>ObjVertexVal;
vector<vector<glm::vec4>>ObjNomalVal;
GLuint VAO[6], VBO[6];
GLuint shaderID[2];
GLuint trishaderID;
GLuint qobjshader;
GLuint vertexshader;
GLuint fragmentshader;

bool TransZ = false;
bool movecheck = false;
bool Rotatecheck = false;
bool ArmRotatechk = false;
bool Rotatechangechk = false;
bool check = false;
bool checkx = false;
bool Pausecheck = false;

struct Camerachk
{
	bool z;
	bool y;
	bool x;

}CameraCheck;
struct Camera
{
	float C_x = 2.0f;
	float C_y = 2.0f;
	float C_z = 5.0f;

}Camerapos;

struct Angle
{
	float angle = 20.0f;
	float anglex = 0.0f;
	float angley = 0.0f;
	float angleLeft = 0.0f;
	float angleRight = 0.0f;
	float anglecamera = 0.0f;
	float anglecamera2 = 0.0f;
	float CameraAngle = 0.0f;
	float CameraAngle2 = 0.0f;
}AngleList;
struct Transration
{

	float T_x = 0.0f;
	float T_y = 0.0f;
	float T_z = 0.0f;
	float T_bodyx = -0.25f;
	float T_bodyy = 0.3f;
	float T_bodyz = 0.0f;
	float T_Rarmx = 0.00f;
	float T_Larmx = 0.20f;
	float T_army = 0.3f;
	float T_armz = 0.0f;
}TransList;
void initbuffer()
{
	glGenVertexArrays(5, VAO);

	for (int i = 0; i <= 4; i++)
	{
		glBindVertexArray(VAO[i]);
		glGenBuffers(1, &VBO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * ObjVertexVal[i].size(), &ObjVertexVal[i][0], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(0);

	}
}
GLvoid ViewPort()
{
	glClearColor(0.2, 0.2, 0.2, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	initbuffer();
	glUseProgram(shaderID[1]);

	
	glViewport(0, FRAME_WIDTH / 4, FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
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


	glm::mat4 O_proj = glm::mat4(1.0f);
	O_proj = glm::perspective(glm::radians(40.0f), (float)FRAME_WIDTH / FRAME_HEIGHT, 0.5f, 70.0f);
	unsigned int ObjectLocation = glGetUniformLocation(shaderID[1], "projectiontransform");
	glUniformMatrix4fv(ObjectLocation, 1, GL_FALSE, &O_proj[0][0]);
	glm::mat4 ObjView = glm::mat4(1.0f);
	ObjView = glm::lookAt(Cameraposdir, RotateobjSpacedir, Cross);
	unsigned int ObjcameraViewLocation = glGetUniformLocation(shaderID[1], "viewtransform");
	glUniformMatrix4fv(ObjcameraViewLocation, 1, GL_FALSE, glm::value_ptr(ObjView));

	drawscene();

	
	glViewport(FRAME_WIDTH / 2, FRAME_HEIGHT / 2, FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
	glm::vec3 PlainCameraPos = glm::vec3(0.0f, 2.0f, 0.0f);
	glm::vec3 PlainCameraDirection = glm::vec3(0.0f, 0.0f, 1.0f) - PlainCameraPos;
	glm::vec3 PlainViewUp = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::mat4 PlainView = glm::mat4(1.0f);
	glm::mat4 PlainOrtho = glm::mat4(1.0f);
	unsigned int PlainViewLocation = glGetUniformLocation(shaderID[1], "viewtransform");
	unsigned int PlainOrthoLocation = glGetUniformLocation(shaderID[1], "projectiontransform");
	PlainView = glm::lookAt(PlainCameraPos, PlainCameraDirection, PlainViewUp);
	PlainOrtho = glm::ortho(-2.0f, 2.0f, -1.0f, 2.0f, 0.5f, 16.0f);
	glUniformMatrix4fv(PlainViewLocation, 1, GL_FALSE, glm::value_ptr(PlainView));
	glUniformMatrix4fv(PlainOrthoLocation, 1, GL_FALSE, glm::value_ptr(PlainOrtho)); 
	drawscene();


	glViewport(FRAME_WIDTH / 2, 0, FRAME_WIDTH / 2, FRAME_HEIGHT/ 2);
	glm::vec3 FrontCameraPos = glm::vec3(0.0f, 0.0f, Camerapos.C_z); 
	glm::vec3 FrontCameraDirection = glm::vec3(0.0f, 0.0f, 0.0f) - FrontCameraPos;
	glm::vec3 FrontViewUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 FrontView = glm::mat4(1.0f);
	glm::mat4 FrontOrtho = glm::mat4(1.0f);
	unsigned int FrontViewLocation = glGetUniformLocation(shaderID[1], "viewtransform");
	unsigned int FrontOrthoLocation = glGetUniformLocation(shaderID[1], "projectiontransform");
	FrontOrtho = glm::ortho(-2.0f, 2.0f, -1.0f, 2.0f, 0.5f, 16.0f);
	FrontView = glm::lookAt(FrontCameraPos, FrontCameraDirection, FrontViewUp);
	glUniformMatrix4fv(FrontViewLocation, 1, GL_FALSE, glm::value_ptr(FrontView));
	glUniformMatrix4fv(FrontOrthoLocation, 1, GL_FALSE, glm::value_ptr(FrontOrtho)); 
	drawscene();

	glutSwapBuffers();
}
GLvoid drawscene()
{
    glEnable(GL_DEPTH_TEST);
	initbuffer();
    glUseProgram(shaderID[1]);

    glBindVertexArray(VAO[0]);
    glm::mat4 BaseObj = glm::mat4(1.0f);
    BaseObj = glm::rotate(BaseObj, glm::radians(AngleList.angle), glm::vec3(0.0f, 1.0f, 0.0f)); // edit
    BaseObj = glm::scale(BaseObj, glm::vec3(8.0f, 8.0f, 8.0f));
    unsigned int BaseobjLocation = glGetUniformLocation(shaderID[1], "modeltransform");
    unsigned int BaseobjfragLocation = glGetUniformLocation(shaderID[1], "vColor");
    glUniformMatrix4fv(BaseobjLocation, 1, GL_FALSE, glm::value_ptr(BaseObj));
    glUniform3f(BaseobjfragLocation, 0.5f, 0.75f, 0.27f);
    glDrawArrays(GL_QUADS, 0, ObjVertexVal[0].size());

    glBindVertexArray(VAO[2]);
    glm::mat4 ObjLeg = glm::mat4(1.0f);
    ObjLeg = glm::translate(ObjLeg, glm::vec3(TransList.T_x, TransList.T_y, TransList.T_z));
    ObjLeg = glm::scale(ObjLeg, glm::vec3(0.7f, 0.6f, 0.7f));
    unsigned int ObjLegLocation = glGetUniformLocation(shaderID[1], "modeltransform");
    unsigned int ObjLegfragLocation = glGetUniformLocation(shaderID[1], "vColor");
    glUniformMatrix4fv(ObjLegLocation, 1, GL_FALSE, glm::value_ptr(ObjLeg));
    glUniform3f(ObjLegfragLocation, 0.2f, 0.1f, 0.1f);
    glDrawArrays(GL_QUADS, 0, 24);

    glBindVertexArray(VAO[1]);
    glm::mat4 ObjMain = glm::mat4(1.0f);
    ObjMain = glm::rotate(ObjMain, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    ObjMain = glm::rotate(ObjMain, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    ObjMain = glm::translate(ObjMain, glm::vec3(TransList.T_x, TransList.T_y + 0.1, TransList.T_z));
    ObjMain = glm::rotate(ObjMain, glm::radians(AngleList.angley), glm::vec3(0.0f, 1.0f, 0.0f));
    ObjMain = glm::scale(ObjMain, glm::vec3(0.35f, 0.15f, 0.35f));
    unsigned int ObjMainLocation = glGetUniformLocation(shaderID[1], "modeltransform");
    unsigned int ObjMainfragLocation = glGetUniformLocation(shaderID[1], "vColor");
    glUniformMatrix4fv(ObjMainLocation, 1, GL_FALSE, glm::value_ptr(ObjMain));
    glUniform3f(ObjMainfragLocation, 0.5f, 0.1f, 0.5f);
    glDrawArrays(GL_QUADS, 0, 24);


    glBindVertexArray(VAO[3]);
    glm::mat4 ObjLeftArm = glm::mat4(1.0f);
    ObjLeftArm = glm::rotate(ObjLeftArm, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    ObjLeftArm = glm::rotate(ObjLeftArm, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    ObjLeftArm = glm::translate(ObjLeftArm, glm::vec3(TransList.T_x + 0.06, TransList.T_y + 0.15, TransList.T_z));
    if (Rotatechangechk == false) {
        ObjLeftArm = glm::rotate(ObjLeftArm, glm::radians(AngleList.angley), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (Rotatechangechk == true) {
        ObjLeftArm = glm::rotate(ObjLeftArm, glm::radians(AngleList.angley), glm::vec3(0.0f, 1.0f, 0.0f));
        ObjLeftArm = glm::rotate(ObjLeftArm, glm::radians(AngleList.angleLeft), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    ObjLeftArm = glm::scale(ObjLeftArm, glm::vec3(0.3f, 0.25f, 0.3f));
    unsigned int ObjLeftArmLocation = glGetUniformLocation(shaderID[1], "modeltransform");
    unsigned int ObjLeftfragLocation = glGetUniformLocation(shaderID[1], "vColor");
    glUniformMatrix4fv(ObjLeftArmLocation, 1, GL_FALSE, glm::value_ptr(ObjLeftArm));
    glUniform3f(ObjLeftfragLocation, 0.32f, 0.22f, 0.92f);
    glDrawArrays(GL_QUADS, 0, 24);

    glBindVertexArray(VAO[4]);
    glm::mat4 ObjRightArm = glm::mat4(1.0f);
    ObjRightArm = glm::rotate(ObjRightArm, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    ObjRightArm = glm::rotate(ObjRightArm, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    ObjRightArm = glm::translate(ObjRightArm, glm::vec3(TransList.T_x - 0.06, TransList.T_y + 0.15, TransList.T_z));

    if (Rotatechangechk == false)
        ObjRightArm = glm::rotate(ObjRightArm, glm::radians(AngleList.angley), glm::vec3(0.0f, 1.0f, 0.0f));
    if (Rotatechangechk == true) {
        ObjRightArm = glm::rotate(ObjRightArm, glm::radians(AngleList.angley), glm::vec3(0.0f, 1.0f, 0.0f));
        ObjRightArm = glm::rotate(ObjRightArm, glm::radians(AngleList.angleRight), glm::vec3(0.0f, 0.0, 1.0f));
    }

    ObjRightArm = glm::scale(ObjRightArm, glm::vec3(0.3f, 0.25f, 0.3f));
    unsigned int ObjRightArmLocation = glGetUniformLocation(shaderID[1], "modeltransform");
    unsigned int ObjRightArmfragLocation = glGetUniformLocation(shaderID[1], "vColor");
    glUniformMatrix4fv(ObjRightArmLocation, 1, GL_FALSE, glm::value_ptr(ObjRightArm));
    glUniform3f(ObjRightArmfragLocation, 0.32f, 0.22f, 0.92f);
    glDrawArrays(GL_QUADS, 0, 24);

    
}
void timer(int value)
{
	if (movecheck == true) {
		if (TransZ == true) {
			TransList.T_z += 0.02;
			TransList.T_armz += 0.02;
			TransList.T_bodyz += 0.02;
		}
		if (TransZ == false) {
			TransList.T_z -= 0.02;
			TransList.T_armz -= 0.02;
			TransList.T_bodyz -= 0.02;
		}
	}

	if (check == true) {
		if (Rotatecheck == true)
			AngleList.angley++;
		else
			AngleList.angley--;
	}


	if (Rotatechangechk == true) {
		if (ArmRotatechk == true) {

			AngleList.angleLeft--;
			AngleList.angleRight++;
			if (AngleList.angleLeft <= -60.0f && AngleList.angleRight >= 60.0f)
				ArmRotatechk = false;
		}
		else if (ArmRotatechk == false) {

			AngleList.angleLeft++;
			AngleList.angleRight--;
			if (AngleList.angleLeft > 0.0f && AngleList.angleRight < 0.0f)
				ArmRotatechk = true;
		}
	}

	glutTimerFunc(100, timer, 1);
	glutPostRedisplay();
}
GLvoid keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'b':
		movecheck = true;
		TransZ = !TransZ;
		break;
	case 'm':
		check = true;
		Rotatecheck = !Rotatecheck;
		break;
	case 't':
		Rotatechangechk = !Rotatechangechk;
		break;
	case 'z':
		Camerapos.C_z += 0.2;
		break;
	case 'Z':
		Camerapos.C_z -= 0.2;
		break;
	case 'y':
		Camerapos.C_y += 0.2;
		break;
	case 'Y':
		Camerapos.C_y -= 0.2;
		break;
	case 'x':
		Camerapos.C_x += 0.2;
		break;
	case 'X':
		Camerapos.C_x -= 0.2;
		break;
	case 'r':
		AngleList.anglecamera++;
		break;
	case 'a':
		AngleList.anglecamera2--;
		break;
	case 'c':
		TransList.T_x = 0.0f;
		TransList.T_y = 0.0f;
		TransList.T_z = 0.0f;
		TransList.T_bodyx = -0.25f;
		TransList.T_bodyy = 0.3f;
		TransList.T_bodyz = 0.0f;
		TransList.T_Rarmx = 0.00f;
		TransList.T_Larmx = 0.20f;
		TransList.T_army = 0.3f;
		TransList.T_armz = 0.0f;
		AngleList.angle = 20.0f;
		AngleList.anglex = 0.0f;
		AngleList.angley = 0.0f;
		AngleList.angleLeft = 0.0f;
		AngleList.angleRight = 0.0f;
		Camerapos.C_x = 2.0f;
		Camerapos.C_y = 2.0f;
		Camerapos.C_z = 5.0f;
		TransZ = false;
		movecheck = false;
		Rotatecheck = false;
		ArmRotatechk = false;
		Rotatechangechk = false;
		check = false;
		checkx = false;
		break;
	case 's':
		TransZ = false;
		movecheck = false;
		Rotatecheck = false;
		ArmRotatechk = false;
		Rotatechangechk = false;
		check = false;
		checkx = false;
		break;
	case 'q':
		exit(-1);
		break;
	}
}
void ReadObj()
{
	vector<glm::vec4> objTmp;
	vector<glm::vec4> normalTmp;
	readobjNomal("Model/19-20/plane.obj", objTmp, normalTmp);
	readobjNomal("Model/19-20/cube.obj", objTmp, normalTmp);
	readobjNomal("Model/19-20/test.obj", objTmp, normalTmp);
	readobjNomal("Model/19-20/crainArm.obj", objTmp, normalTmp);
	readobjNomal("Model/19-20/crainArm.obj", objTmp, normalTmp);
	ObjVertexVal.push_back(objTmp);
	ObjNomalVal.push_back(normalTmp);
}
int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("20");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cerr << "fail Initialize" << endl;
	else cout << "Initialize" << endl;
	ReadObj();
	makeShader(vn,fn,shaderID[0]);
	initbuffer();
	glutDisplayFunc(ViewPort);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, timer, 1);
	glutReshapeFunc(Resize);
	glutMainLoop();
}