#include "stdafx.h"

using namespace std;
void make_vertexShaders();
void make_fragmentShader();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char Key, int x, int y);
GLvoid SpecialKeyBoard(int key, int x, int y);
void timer(int value);

GLuint s_program;
GLuint VAO[3], VBO[6];
GLuint shaderID;
GLint width, height;
GLuint vertexShader;
GLuint fragmentShader;
int shapechk=0;
bool cullchk = false;
bool solidchk = false;
bool rotchkx = false;
bool rotchky = false;
float a_x = 30.0f;
float a_y= -30.0f;
float t_x = 0.0f;
float t_y = 0.0f;
float h_vertex = 0.3f;
float data_line[] = 
{             //사분면선
   0.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 
   0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

   -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f


};

float data_hexa[] = 
{    //육면체
   -h_vertex, h_vertex, h_vertex,		1.0f, 0.0f, 0.0f,
   h_vertex, h_vertex, h_vertex,			 0.0f, 1.0f, 0.0f,
   -h_vertex, h_vertex, -h_vertex,		0.5f, 0.5f, 0.5f,

   h_vertex, h_vertex, h_vertex,			 0.0f, 1.0f, 0.0f,
   h_vertex, h_vertex, -h_vertex,		0.0f, 0.0f, 1.0f,
   -h_vertex, h_vertex, -h_vertex,		0.5f, 0.5f, 0.5f,

   -h_vertex, -h_vertex, h_vertex,		1.0f, 1.0f, 1.0f,
   -h_vertex, -h_vertex, -h_vertex,		0.3f, 1.0f, 0.7f,
   h_vertex, -h_vertex, -h_vertex,		0.5f, 0.3f, 0.7f,

   -h_vertex, -h_vertex, h_vertex,		1.0f, 1.0f, 1.0f,
   h_vertex, -h_vertex, -h_vertex,		0.5f, 0.3f, 0.7f,
   h_vertex, -h_vertex, h_vertex,		0.0f, 1.0f, 1.0f,

   -h_vertex, -h_vertex, h_vertex,		0.0f, 0.0f, 1.0f,
   h_vertex, -h_vertex, h_vertex,		0.0f, 1.0f, 1.0f,
   -h_vertex, h_vertex, h_vertex,		1.0f, 0.0f, 0.0f,

   h_vertex, -h_vertex, h_vertex,		0.0f, 1.0f, 1.0f,
   h_vertex, h_vertex, h_vertex,			 0.0f, 1.0f, 0.0f,
   -h_vertex, h_vertex, h_vertex,		1.0f, 0.0f, 0.0f,

   h_vertex, -h_vertex, -h_vertex,		0.5f, 0.3f, 0.7f,
   -h_vertex, -h_vertex, -h_vertex,		0.3f, 0.0f, 0.7f,
   h_vertex, h_vertex, -h_vertex,		0.0f, 0.0f, 1.0f,

   -h_vertex, -h_vertex, -h_vertex,		0.3f, 0.0f, 0.7f,
   -h_vertex, h_vertex, -h_vertex,		0.5f, 0.5f, 0.5f,
   h_vertex, h_vertex, -h_vertex,		0.0f, 0.0f, 1.0f,

   -h_vertex, -h_vertex, -h_vertex,		0.3f, 0.0f, 0.3f,
   -h_vertex, h_vertex, h_vertex,		1.0f, 0.0f, 0.0f,
   -h_vertex, h_vertex, -h_vertex,		0.5f, 0.5f, 0.5f,

   -h_vertex, -h_vertex, -h_vertex,		0.3f, 0.0f, 0.4f,
   -h_vertex, -h_vertex, h_vertex,		 0.0f, 0.0f, 0.0f,
   -h_vertex, h_vertex, h_vertex,		1.0f, 0.0f, 0.0f,

  h_vertex, -h_vertex, h_vertex,			0.0f, 1.0f, 1.0f,
  h_vertex, -h_vertex, -h_vertex,		 0.5f, 0.3f, 0.7f,
  h_vertex, h_vertex, h_vertex,			0.0f, 1.0f, 0.0f,

  h_vertex, -h_vertex, -h_vertex,		0.5f, 0.3f, 0.7f,
  h_vertex, h_vertex, -h_vertex,			 0.0f, 0.0f, 1.0f,
  h_vertex, h_vertex, h_vertex,			0.0f, 1.0f, 0.0f
};

float data_quad[] = 
{   //사각뿔
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
	vertexSource = filetobuf("Shader/vertex.GLM");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

}

void make_fragmentShader()
{
	GLchar* fragmentSource;
	fragmentSource = filetobuf("Shader/fragment.GLM");
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
	glBindVertexArray(VAO[0]);
	glGenBuffers(2, &VBO[0]);

	//->vertex
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_line)  , data_line, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//->color
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_line), data_line, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//hexa
	glBindVertexArray(VAO[1]);
	glGenBuffers(2, &VBO[2]);
	//->vertex
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
	glBindVertexArray(VAO[2]);
	glGenBuffers(2, &VBO[4]);
	//->vertex
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
int check = 0;
void timer(int value)
{
	if (check==1)
	{
		
		a_y = -30.0f;
		if (rotchkx == true)
		{
			a_x += 2.0f;
		}
		else if (rotchkx == false)
			a_x -= 2.0f;
	}
	if (check == 2)
	{
		a_x = 30.0f;

		if (rotchky == true)
		{
			a_y += 2.0f;
		}
		else if (rotchky == false)
			a_y -= 2.0f;
	}
	glutPostRedisplay();
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
	glm::mat4 L_rotMatrix = glm::mat4(1.0f); // 단위 행렬로 초기화 
	L_rotMatrix = glm::rotate(L_rotMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int transformLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(L_rotMatrix));
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_LINES,0,4);

	if (shapechk == 1)//hexa
	{
		glm::mat4 H_Matrix = glm::mat4(1.0f); // 단위 행렬로 초기화 
		H_Matrix = glm::translate(H_Matrix, glm::vec3(t_x, t_y, 0.0f));
		H_Matrix = glm::rotate(H_Matrix, glm::radians(a_x), glm::vec3(1.0f, 0.0f, 0.0f));
		H_Matrix = glm::rotate(H_Matrix, glm::radians(a_y), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int transformLocation = glGetUniformLocation(s_program, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(H_Matrix));
		if (cullchk == true)
		{
			glEnable(GL_CULL_FACE);
		}
		else
			glDisable(GL_CULL_FACE);

		if (solidchk == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	

	if (shapechk == 2)//quad
	{
		glm::mat4 S_Matrix = glm::mat4(1.0f); // 단위 행렬로 초기화 
		S_Matrix = glm::translate(S_Matrix, glm::vec3(t_x, t_y, 0.0f));
		S_Matrix = glm::rotate(S_Matrix, glm::radians(a_x), glm::vec3(1.0f, 0.0f, 0.0f));
		S_Matrix = glm::rotate(S_Matrix, glm::radians(a_y), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int transformLocation = glGetUniformLocation(s_program, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(S_Matrix));
	

		if (cullchk == true)
		{
			glEnable(GL_CULL_FACE);
		}
		else
			glDisable(GL_CULL_FACE);

		if (solidchk == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, 18);

	}

	glutSwapBuffers();
	glutTimerFunc(150, timer, 1);
}

GLvoid KeyBoard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'c': //육면체
		shapechk = 1;
		drawScene();
		break;
	case 'p': // 사각뿔
		shapechk = 2;
		drawScene();
		break;
	case 'h': //은면
		cullchk = !cullchk;
		drawScene();
		break;
	case 'x': // x축 양/음 회전
		check = 1;
		rotchkx = !rotchkx;
		break;
	case 'X':
		rotchkx = !rotchkx;
		break;
	case 'y':  // y축 양/음 회전
		check = 2;
		rotchky = !rotchky;
		break;
	case 'Y':
		rotchky = !rotchky;
		break;
	case 'w': // 와이어 솔리드
		solidchk = !solidchk;
		drawScene();
		break;
	case 'W':
		solidchk = !solidchk;
		drawScene();
		break;
	case 's': //위치 리셋 자전도 멈춤
		check = 0;
		a_x = 30.0f;
		a_y = -30.0f;
		t_x = 0.0f;
		t_y = 0.0f;
		drawScene();
		break;

	}
}

GLvoid SpecialKeyBoard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		t_x -= 0.05f;
		drawScene();
		break;
	case GLUT_KEY_RIGHT:
		t_x += 0.05f;
		drawScene();
		break;
	case GLUT_KEY_UP:
		t_y += 0.05f;
		drawScene();
		break;
	case GLUT_KEY_DOWN:
		t_y -= 0.05f;
		drawScene();
		break;
	default:
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
	glutSpecialFunc(SpecialKeyBoard);
	glutKeyboardFunc(KeyBoard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, timer, 1);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

