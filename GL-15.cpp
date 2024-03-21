#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <gl/freeglut.h>

using namespace std;
void timer(int value);
void make_vertexShaders();
void make_fragmentShader();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char Key, int x, int y);

GLUquadricObj* qobj;
GLuint s_program;
GLuint VAO[3], VBO[6];
GLuint shaderID;
GLint width, height;
GLuint vertexShader;
GLuint fragmentShader;

int Leftshapestate = 0;
int Rightshapestate = 0;

bool Linerotatestate = false;
bool Linestate = false;
bool rotchkx = false;
bool rotchky = false;
bool shapechange = true;

float Ha_x = 0.0f;
float Ha_y = 0.0f;
float Qa_x = 0.0f;
float Qa_y = 0.0f;
float Ht_x = -0.5f;
float Ht_y = 0.25f;
float Qt_x = 0.5f;
float Qt_y = 0.18f;
float La_x = 30.0f;
float La_y = -30.0f;
float h_vertex = 0.2f;
float data_line[] =
{  //사분면선
   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,//y

   -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
   1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,//x

	0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f //z
};


float data_hexa[] =
{    //육면체
	-h_vertex, h_vertex, h_vertex,   0.0f, 0.0f, 0.0f,
	h_vertex, h_vertex, h_vertex,     0.0f, 1.0f, 0.0f,
	-h_vertex, h_vertex, -h_vertex,  0.5f, 0.5f, 0.5f,

	h_vertex, h_vertex, h_vertex,     0.0f, 1.0f, 0.0f,
	h_vertex, h_vertex, -h_vertex,   0.0f, 0.0f, 1.0f,
	-h_vertex, h_vertex, -h_vertex,  0.5f, 0.5f, 0.5f,

	-h_vertex, -h_vertex, h_vertex,  1.0f, 1.0f, 1.0f,
	-h_vertex, -h_vertex, -h_vertex, 0.3f, 1.0f, 0.7f,
	h_vertex, -h_vertex, -h_vertex,	 0.5f, 0.3f, 0.7f,

	-h_vertex, -h_vertex, h_vertex,	1.0f, 1.0f, 1.0f,
	h_vertex, -h_vertex, -h_vertex,	0.5f, 0.3f, 0.7f,
	h_vertex, -h_vertex, h_vertex,	0.0f, 1.0f, 1.0f,

	-h_vertex, -h_vertex, h_vertex,	0.0f, 0.0f, 1.0f,
	h_vertex, -h_vertex, h_vertex,	0.0f, 1.0f, 1.0f,
	-h_vertex, h_vertex, h_vertex,	1.0f, 0.0f, 0.0f,

	h_vertex, -h_vertex, h_vertex,	0.0f, 1.0f, 1.0f,
	h_vertex, h_vertex, h_vertex,		 0.0f, 1.0f, 0.0f,
	-h_vertex, h_vertex, h_vertex,	1.0f, 0.0f, 0.0f,

	h_vertex, -h_vertex, -h_vertex,	0.5f, 0.3f, 0.7f,
	-h_vertex, -h_vertex, -h_vertex,	0.3f, 0.0f, 0.7f,
	h_vertex, h_vertex, -h_vertex,	0.0f, 0.0f, 1.0f,

	-h_vertex, -h_vertex, -h_vertex,	0.3f, 0.0f, 0.7f,
	-h_vertex, h_vertex, -h_vertex,	0.5f, 0.5f, 0.5f,
	h_vertex, h_vertex, -h_vertex,	0.0f, 0.0f, 1.0f,

	-h_vertex, -h_vertex, -h_vertex,	0.3f, 0.0f, 0.3f,
	-h_vertex, h_vertex, h_vertex,	1.0f, 0.0f, 0.0f,
	-h_vertex, h_vertex, -h_vertex,	0.5f, 0.5f, 0.5f,

	-h_vertex, -h_vertex, -h_vertex,		0.3f, 0.0f, 0.4f,
	-h_vertex, -h_vertex, h_vertex,	 0.0f, 0.0f, 0.0f,
	-h_vertex, h_vertex, h_vertex,	1.0f, 0.0f, 0.0f,

   h_vertex, -h_vertex, h_vertex,		0.0f, 1.0f, 1.0f,
   h_vertex, -h_vertex, -h_vertex,	 0.5f, 0.3f, 0.7f,
   h_vertex, h_vertex, h_vertex,		0.0f, 1.0f, 0.0f,

   h_vertex, -h_vertex, -h_vertex,   0.5f, 0.3f, 0.7f,
   h_vertex, h_vertex, -h_vertex,		 0.0f, 0.0f, 1.0f,
   h_vertex, h_vertex, h_vertex,		0.0f, 1.0f, 0.0f
};


float data_quad[] =
{   //삼각뿔

-0.3f, -0.3f, -0.3f, 0.5f, 0.5f, 0.5f,
   0.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
   0.3f, -0.3f, -0.3f, 1.0f, 0.0f, 0.3f,

   0.3f, -0.3f, -0.3f, 1.0f, 0.0f, 0.3f,
   0.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
   0.3f, -0.3f, 0.3f, 0.0f, 0.7f, 1.0f,

   0.3f, -0.3f, 0.3f, 0.0f, 0.7f, 1.0f,
   0.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
   -0.3f, -0.3f, 0.3f, 1.0f, 1.0f, 0.12f,

   -0.3f, -0.3f, -0.3f, 0.5f, 0.5f, 0.5f,
   -0.3f, -0.3f, 0.3f, 1.0f, 1.0f, 0.12f,
   0.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,

   -0.3f, -0.3f, 0.3f, 1.0f, 1.0f, 0.12f,
   -0.3f, -0.3f, -0.3f, 0.5f, 0.5f, 0.5f,
   0.3f, -0.3f, -0.3f, 1.0f, 0.0f, 0.3f,

   -0.3f, -0.3f, 0.3f, 1.0f, 1.0f, 0.12f,
   0.3f, -0.3f, -0.3f, 1.0f, 0.0f, 0.3f,
   0.3f, -0.3f, 0.3f, 0.0f, 0.7f, 1.0f
};


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
	vertexSource = filetobuf("vertex.GLM");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

}


void make_fragmentShader()
{
	GLchar* fragmentSource;
	fragmentSource = filetobuf("fragment.GLM");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

}


void InitShader()
{
	make_vertexShaders();
	make_fragmentShader();

	s_program = glCreateProgram();

	glAttachShader(s_program, vertexShader);
	glAttachShader(s_program, fragmentShader);
	glLinkProgram(s_program);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR :  fragment Shader Fail Compile \n" << errorLog << endl;
		exit(-1);
	}

	else
		cout << "good";
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(s_program);
}


GLvoid InitBuffer()
{
	glGenVertexArrays(3, VAO);

	//line
	//->vertex
	glBindVertexArray(VAO[0]);
	glGenBuffers(2, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_line), data_line, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//->color
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_line), data_line, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//hexa
	//->vertex
	glBindVertexArray(VAO[1]);
	glGenBuffers(2, &VBO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_hexa), data_hexa, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//->color
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_hexa), data_hexa, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//quad
	//->vertex
	glBindVertexArray(VAO[2]);
	glGenBuffers(2, &VBO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_quad), data_quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//->color
	glBindBuffer(GL_ARRAY_BUFFER, VBO[5]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_quad), data_quad, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}


void timer(int value)
{
	if (Linestate == true) {
		if (Linerotatestate == true) {
			La_y += 1.0f;
		}
		else if (Linerotatestate == false) {
			La_y -= -1.0f;
		}
	}

	if (Leftshapestate == 1) {
		Ha_y = 0.0f;
		if (rotchkx == true) {

			Ha_x += 2.0f;
		}
		else if (rotchkx == false) {
			Ha_x -= 2.0f;

		}
	}

	if (Leftshapestate == 2) {
		Ha_x = 0.0f;
		if (rotchky == true)
		{

			Ha_y += -2.0f;
		}
		else if (rotchky == false) {

			Ha_y -= -2.0f;
		}
	}

	if (Rightshapestate == 1) {
		Qa_y = 0.0f;
		if (rotchkx == true) {

			Qa_x += 2.0f;;
		}
		else if (rotchkx == false) {

			Qa_x -= 2.0f;
		}
	}

	if (Rightshapestate == 2) {
		Qa_x = 0.0f;
		if (rotchky == true)
		{

			Qa_y += -2.0f;;
		}
		else if (rotchky == false) {

			Qa_y -= -2.0f;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(150, timer, 1);
}
void drawScene()
{
	GLfloat rColor = 0.2;
	GLfloat gColor = 0.2;
	GLfloat bColor = 0.2;
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //깊이 체크 (컬링)

	InitBuffer(); //순서
	glUseProgram(s_program);
	//line
	glm::mat4 L_Matrix = glm::mat4(1.0f); // 단위 행렬로 초기화 
	L_Matrix = glm::rotate(L_Matrix, glm::radians(La_x), glm::vec3(1.0f, 0.0f, 0.0f));
	L_Matrix = glm::rotate(L_Matrix, glm::radians(La_y), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int LinetransformLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(LinetransformLocation, 1, GL_FALSE, glm::value_ptr(L_Matrix));
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_LINES, 0, 6);

	glm::mat4 H_Matrix = glm::mat4(1.0f);
	H_Matrix = glm::rotate(H_Matrix, glm::radians(La_x), glm::vec3(1.0f, 0.0f, 0.0f));
	H_Matrix = glm::rotate(H_Matrix, glm::radians(La_y), glm::vec3(0.0f, 1.0f, 0.0f));
	H_Matrix = glm::translate(H_Matrix, glm::vec3(Ht_x, Ht_y, 0.0f));
	H_Matrix = glm::rotate(H_Matrix, glm::radians(Ha_x), glm::vec3(1.0f, 0.0f, 0.0f));
	H_Matrix = glm::rotate(H_Matrix, glm::radians(Ha_y), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int HtransformLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(HtransformLocation, 1, GL_FALSE, glm::value_ptr(H_Matrix));
	glBindVertexArray(VAO[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (shapechange == true) {
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	if (shapechange == false) {
		qobj = gluNewQuadric(); // 객체 생성하기
		gluQuadricDrawStyle(qobj, GLU_LINE); // 도형 스타일
		gluSphere(qobj, 0.25, 50, 50);
	}

	glm::mat4 Q_Matrix = glm::mat4(1.0f);
	Q_Matrix = glm::rotate(Q_Matrix, glm::radians(La_x), glm::vec3(1.0f, 0.0f, 0.0f));
	Q_Matrix = glm::rotate(Q_Matrix, glm::radians(La_y), glm::vec3(0.0f, 1.0f, 0.0f));
	Q_Matrix = glm::translate(Q_Matrix, glm::vec3(Qt_x, Qt_y, 0.0f));
	Q_Matrix = glm::rotate(Q_Matrix, glm::radians(Qa_x), glm::vec3(1.0f, 0.0f, 0.0f));
	Q_Matrix = glm::rotate(Q_Matrix, glm::radians(Qa_y), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int QtransformLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(QtransformLocation, 1, GL_FALSE, glm::value_ptr(Q_Matrix));
	glBindVertexArray(VAO[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (shapechange == true) {
		glDrawArrays(GL_TRIANGLES, 0, 18);
	}
	if (shapechange == false) {
		qobj = gluNewQuadric();
		gluQuadricDrawStyle(qobj, GLU_LINE);
		gluCylinder(qobj, 0.05, 0.05, 0.5, 30, 1);
	}

	glutSwapBuffers();
}

void checkcollec()
{
	Leftshapestate = 0;
	Rightshapestate = 0;
	Linerotatestate = false;
	Linestate = false;
	rotchkx = false;
	rotchky = false;
	shapechange = true;
	Ha_x = 0.0f;
	Ha_y = 0.0f;
	Qa_x = 0.0f;
	Qa_y = 0.0f;
	Ht_x = -0.5f;
	Ht_y = 0.25f;
	Qt_x = 0.5f;
	Qt_y = 0.18f;
	La_x = 30.0f;
	La_y = -30.0f;
}

GLvoid KeyBoard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'x':
		shapechange = true;
		Leftshapestate = 1;
		rotchkx = !rotchkx;
		break;
	case 'X':
		shapechange = true;
		Leftshapestate = 1;
		rotchkx = !rotchkx;
		break;
	case 'y':
		shapechange = true;
		Leftshapestate = 2;
		rotchky = !rotchky;
		break;
	case 'Y':
		shapechange = true;
		Leftshapestate = 2;
		rotchky = !rotchky;
		break;
	case 'a':
		shapechange = true;
		Rightshapestate = 1;
		rotchkx = !rotchkx;
		break;
	case 'A':
		shapechange = true;
		Rightshapestate = 1;
		rotchkx = !rotchkx;
		break;
	case 'b':
		shapechange = true;
		Rightshapestate = 2;
		rotchkx = !rotchkx;
		break;
	case 'B':
		shapechange = true;
		Rightshapestate = 2;
		rotchkx = !rotchkx;
		break;
	case 'r':
		Linestate = !Linestate;
		break;
	case 'R':
		Linestate = !Linestate;
		break;
	case 'c':
		shapechange = !shapechange;
		break;
	case 's':
		checkcollec();
		break;
	}
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void main(int argc, char** argv)
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

	InitShader();
	InitBuffer();
	glutKeyboardFunc(KeyBoard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(120, timer, 1);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

