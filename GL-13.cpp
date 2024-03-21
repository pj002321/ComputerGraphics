#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <gl/freeglut.h>

using namespace std;
void make_vertexShaders();
void make_fragmentShader();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char Key, int x, int y);


GLuint s_program;
GLuint VAO[3], VBO[6];
GLuint shaderID;
GLint width, height;
GLuint vertexShader;
GLuint fragmentShader;
int shapechk = 0;
int keychk = 0;
char alpachk = 0;
float a_x = 30.0f;
float a_y = -30.0f;
float t_x = 0.0f;
float t_y = 0.0f;


float data_line[] =
{  //사분면선
   0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
   0.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

   -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

float data_hexa[] =
{    //육면체
   -0.2f, 0.2f, 0.2f,   1.0f, 0.0f, 0.0f,
   0.2f,0.2f, 0.2f,      0.0f, 1.0f, 0.0f,
   -0.2f, 0.2f, -0.2f,  0.5f, 0.5f, 0.5f,

   0.2f, 0.2f, 0.2f,     0.0f, 1.0f, 0.0f,
   0.2f, 0.2f, -0.2f,    0.0f, 0.0f, 1.0f,
   -0.2f, 0.2f, -0.2f,   0.5f, 0.5f, 0.5f,

   -0.2f, -0.2f, 0.2f,    1.0f, 1.0f, 1.0f,
   -0.2f, -0.2f, -0.2f,   0.3f, 1.0f, 0.7f,
   0.2f, -0.2f, -0.2f,		0.5f, 0.3f, 0.7f,

   -0.2f, -0.2f, 0.2f,		1.0f, 1.0f, 1.0f,
   0.2f, -0.2f, -0.2f,		0.5f, 0.3f, 0.7f,
   0.2f, -0.2f, 0.2f,		0.0f, 1.0f, 1.0f,

   -0.2f, -0.2f, 0.2f,		0.0f, 0.0f, 1.0f,
   0.2f, -0.2f, 0.2f,		0.0f, 1.0f, 1.0f,
   -0.2f, 0.2f, 0.2f,		1.0f, 0.0f, 0.0f,

   0.2f, -0.2f, 0.2f,		0.0f, 1.0f, 1.0f,
   0.2f, 0.2f, 0.2f,		 0.0f, 1.0f, 0.0f,
   -0.2f, 0.2f, 0.2f,		1.0f, 0.0f, 0.0f,

   0.2f, -0.2f, -0.2f,		0.5f, 0.3f, 0.7f,
   -0.2f, -0.2f, -0.2f,	0.3f, 0.0f, 0.7f,
   0.2f, 0.2f, -0.2f,		0.0f, 0.0f, 1.0f,

   -0.2f, -0.2f, -0.2f,	0.3f, 0.0f, 0.7f,
   -0.2f, 0.2f, -0.2f,		0.5f, 0.5f, 0.5f,
   0.2f, 0.2f, -0.2f,		0.0f, 0.0f, 1.0f,

   -0.2f, -0.2f, -0.2f,	0.3f, 0.0f, 0.3f,
   -0.2f, 0.2f, 0.2f,		1.0f, 0.0f, 0.0f,
   -0.2f, 0.2f, -0.2f,		0.5f, 0.5f, 0.5f,

   -0.2f, -0.2f, -0.2f,		0.3f, 0.0f, 0.4f,
   -0.2f, -0.2f, 0.2f,		 0.0f, 0.0f, 0.0f,
   -0.2f, 0.2f, 0.2f,		1.0f, 0.0f, 0.0f,

   0.2f, -0.2f, 0.2f,		0.0f, 1.0f, 1.0f,
   0.2f, -0.2f, -0.2f,		 0.5f, 0.3f, 0.7f,
   0.2f, 0.2f, 0.2f,		0.0f, 1.0f, 0.0f,

   0.2f, -0.2f, -0.2f,   0.5f, 0.3f, 0.7f,
   0.2f, 0.2f, -0.2f,		 0.0f, 0.0f, 1.0f,
   0.2f, 0.2f, 0.2f,		0.0f, 1.0f, 0.0f
};

float data_quad[] =
{   //삼각뿔

	-0.3f, -0.3f, -0.3f, 0.5f, 0.5f, 0.5f, 
   -0.0f, 0.3f, 0.0f, 1.0f, 0.3f, 0.0f,  
   0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 0.3f,  

   0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 0.3f,  
   0.0f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,  
   0.3f, -0.3f, 0.3f, 0.0f, 0.0f, 0.1f,  

   0.3f, -0.3f, 0.3f, 0.0f, 0.5f, 0.3f,  
   0.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,  
   -0.3f, -0.3f, -0.3f, 0.3f, 0.5f, 0.5f,  

   -0.3f, -0.3f, -0.3f, 0.0f, 1.0f, 0.1f,
   0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 0.3f,  
   0.3f, -0.3f, 0.3f, 0.0f, 0.3f, 1.0f  
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
	glDrawArrays(GL_LINES, 0, 4);

	if (shapechk == 1)//hexa
	{
		glm::mat4 H_Matrix = glm::mat4(1.0f); // 단위 행렬로 초기화 
		H_Matrix = glm::translate(H_Matrix, glm::vec3(t_x, t_y, 0.0f));
		H_Matrix = glm::rotate(H_Matrix, glm::radians(a_x), glm::vec3(1.0f, 0.0f, 0.0f));
		H_Matrix = glm::rotate(H_Matrix, glm::radians(a_y), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int transformLocation = glGetUniformLocation(s_program, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(H_Matrix));
		glBindVertexArray(VAO[1]);
		
		if (keychk == 1) {
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		if (keychk == 2) {
			glDrawArrays(GL_TRIANGLES, 6,6 );
		}
		if (keychk==3){
			glDrawArrays(GL_TRIANGLES, 12,6 );
		}
		if (keychk == 4) {
			glDrawArrays(GL_TRIANGLES, 18, 6);
		}
		if (keychk == 5) {
			glDrawArrays(GL_TRIANGLES, 24, 6);
		}
		if (keychk == 6) {
			glDrawArrays(GL_TRIANGLES, 30, 6);
		}
		if (alpachk == 'a') {
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawArrays(GL_TRIANGLES, 6, 6);
		}
		if (alpachk == 'b') {
			glDrawArrays(GL_TRIANGLES, 12, 6);
			glDrawArrays(GL_TRIANGLES, 18, 6);
		}
		if (alpachk == 'c') {
			glDrawArrays(GL_TRIANGLES, 24, 6);
			glDrawArrays(GL_TRIANGLES, 30, 6);
		}
	}


	if (shapechk == 2)//quad
	{
		glm::mat4 S_Matrix = glm::mat4(1.0f); // 단위 행렬로 초기화 
		S_Matrix = glm::translate(S_Matrix, glm::vec3(t_x, t_y, 0.0f));
		S_Matrix = glm::rotate(S_Matrix, glm::radians(a_x), glm::vec3(1.0f, 0.0f, 0.0f));
		S_Matrix = glm::rotate(S_Matrix, glm::radians(a_y), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int transformLocation = glGetUniformLocation(s_program, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(S_Matrix));

		glBindVertexArray(VAO[2]);
		if (keychk == 7) {
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		if (keychk == 8) {
			glDrawArrays(GL_TRIANGLES, 3, 3);
		}
		if (keychk == 9) {
			glDrawArrays(GL_TRIANGLES, 6, 3);
		}
		if (keychk == 0) {
			glDrawArrays(GL_TRIANGLES, 9, 3);
		}
		if (alpachk == 'e') {
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawArrays(GL_TRIANGLES, 9, 3);
		}
		if (alpachk == 'f') {
			glDrawArrays(GL_TRIANGLES, 3, 3);
			glDrawArrays(GL_TRIANGLES, 9, 3);
		}
		if (alpachk == 'g') {
			glDrawArrays(GL_TRIANGLES,6, 3);
			glDrawArrays(GL_TRIANGLES, 9, 3);
		}
	}

	glutSwapBuffers();
}

GLvoid KeyBoard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case '1':
		alpachk = 0;
		shapechk = 1;
		keychk = 1;
		drawScene();
		break;
	case '2':
		alpachk = 0;
		shapechk = 1;
		keychk = 2;
		drawScene();
		break;
	case '3':
		alpachk = 0;
		shapechk = 1;
		keychk = 3;
		drawScene();
		break;
	case '4':
		alpachk = 0;
		shapechk = 1;
		keychk = 4;
		drawScene();
		break;
	case '5':
		alpachk = 0;
		shapechk = 1;
		keychk = 5;
		drawScene();
		break;
	case '6':
		alpachk = 0;
		shapechk = 1;
		keychk = 6;
		drawScene();
		break;
	case '7':
		alpachk = 0;
		shapechk = 2;
		keychk = 7;
		drawScene();
		break;
	case '8':
		alpachk = 0;
		shapechk = 2;
		keychk = 8;
		drawScene();
		break;
	case '9':
		alpachk = 0;
		shapechk = 2;
		keychk = 9;
		drawScene();
		break;
	case '0':
		alpachk = 0;
		shapechk = 2;
		keychk = 0;
		drawScene();
		break;
	case 'a':
		keychk = 0;
		shapechk = 1;
		alpachk = 'a';
		drawScene();
		break;
	case 'b':
		keychk = 0;
		shapechk = 1;
		alpachk = 'b';
		drawScene();
		break;
	case 'c':
		keychk = 0;
		shapechk = 1;
		alpachk = 'c';
		drawScene();
		break;
	case 'e':
		keychk = 0;
		shapechk = 2;
		alpachk = 'e';
		drawScene();
		break;
	case 'f':
		keychk = 0;
		shapechk = 2;
		alpachk = 'f';
		drawScene();
		break;
	case 'g':
		keychk = 0;
		shapechk = 2;
		alpachk = 'g';
		drawScene();
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
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

