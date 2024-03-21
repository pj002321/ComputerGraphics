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
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char Key, int x, int y);
GLvoid SpecialMove(int Key, int x, int y);

GLUquadricObj* qobj;
GLuint s_program;
GLuint VAO[4], VBO[8];
GLuint shaderID;
GLint width, height;
GLuint vertexShader;
GLuint fragmentShader;

bool rotlinechk = false;
bool check = false;
bool rotateline = false;
bool Linerotatestate = false;
bool Linestate = false;
float h_vertex = 0.07;
float rot = 0.0f;
float La_y = -30.0f;
float La_x = 30.0f;
float Ha_x = 0.0f;
float Ha_y = 0.0f;
float Qa_x = 0.0f;
float Qa_y = 0.0f;

float Ht_x = -0.7f;
float Ht_y = 0.1f;
float Ht_z = 0.0f;
float Qt_x = 0.7f;
float Qt_y = 0.1f;
float Qt_z = 0.0f;

float Sh_x = 1.0f;
float Sh_y = 1.0f;
float Sh_z = 1.0f;
float S_sq = 0.1f;

float Lt_x = 0.0f;
float Lt_y = 0.0f;
float Lt_z = 0.0f;

float r_color, g_color, b_color;
float r = 0.05;
float spin_x = 0.0;
float spin_z = 0.0;
int rotcount = 0;
int Lshape_count = 0;
int Rshape_count = 359;
int theta = 180;
float data_line[] =
{  //사분면선
   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,//y

  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //13
  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,//x //19

	0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f, // 21
   0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f //z //27
};


float data_hexa[] =
{    //육면체
   -h_vertex, h_vertex, h_vertex,   1.0f, 0.0f, 0.0f,
   h_vertex, h_vertex, h_vertex,      0.0f, 1.0f, 0.0f,
   -h_vertex, h_vertex, -h_vertex,  0.5f, 0.5f, 0.5f,

   h_vertex, h_vertex, h_vertex,     0.0f, 1.0f, 0.0f,
   h_vertex, h_vertex, -h_vertex,    0.0f, 0.0f, 1.0f,
   -h_vertex, h_vertex, -h_vertex,   0.5f, 0.5f, 0.5f,

   -h_vertex, -h_vertex, h_vertex,    1.0f, 1.0f, 1.0f,
   -h_vertex, -h_vertex, -h_vertex,   0.3f, 1.0f, 0.7f,
   h_vertex, -h_vertex, -h_vertex,		0.5f, 0.3f, 0.7f,

   -h_vertex, -h_vertex, h_vertex,		1.0f, 1.0f, 1.0f,
   h_vertex, -h_vertex, -h_vertex,		0.5f, 0.3f, 0.7f,
   h_vertex, -h_vertex, h_vertex,		0.0f, 1.0f, 1.0f,

   -h_vertex, -h_vertex, h_vertex,		0.0f, 0.0f, 1.0f,
   h_vertex, -h_vertex, h_vertex,		0.0f, 1.0f, 1.0f,
   -h_vertex, h_vertex, h_vertex,		1.0f, 0.0f, 0.0f,

   h_vertex, -h_vertex, h_vertex,		0.0f, 1.0f, 1.0f,
   h_vertex, h_vertex, h_vertex,		 0.0f, 1.0f, 0.0f,
   -h_vertex, h_vertex, h_vertex,		1.0f, 0.0f, 0.0f,

   h_vertex, -h_vertex, -h_vertex,		0.5f, 0.3f, 0.7f,
   -h_vertex, -h_vertex, -h_vertex,	0.3f, 0.0f, 0.7f,
   h_vertex, h_vertex, -h_vertex,		0.0f, 0.0f, 1.0f,

   -h_vertex, -h_vertex, -h_vertex,	0.3f, 0.0f, 0.7f,
   -h_vertex, h_vertex, -h_vertex,		0.5f, 0.5f, 0.5f,
   h_vertex, h_vertex, -h_vertex,		0.0f, 0.0f, 1.0f,

   -h_vertex, -h_vertex, -h_vertex,		0.3f, 0.0f, 0.3f,
   -h_vertex, h_vertex, h_vertex,		1.0f, 0.0f, 0.0f,
   -h_vertex, h_vertex, -h_vertex,		0.5f, 0.5f, 0.5f,

   -h_vertex, -h_vertex, -h_vertex,		0.3f, 0.0f, 0.4f,
   -h_vertex, -h_vertex, h_vertex,		 0.0f, 0.0f, 0.0f,
   -h_vertex, h_vertex, h_vertex,		1.0f, 0.0f, 0.0f,

  h_vertex, -h_vertex, h_vertex,		0.0f, 1.0f, 1.0f,
  h_vertex, -h_vertex, -h_vertex,		 0.5f, 0.3f, 0.7f,
  h_vertex, h_vertex, h_vertex,		0.0f, 1.0f, 0.0f,

  h_vertex, -h_vertex, -h_vertex,   0.5f, 0.3f, 0.7f,
  h_vertex, h_vertex, -h_vertex,		 0.0f, 0.0f, 1.0f,
  h_vertex, h_vertex, h_vertex,		0.0f, 1.0f, 0.0f
};


float data_quad[] =
{   //삼각뿔

-0.1f, -0.1f, -0.1f, 0.5f, 0.5f, 0.5f,
   0.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
   0.1f, -0.1f, -0.1f, 1.0f, 0.0f, 0.3f,

   0.1f, -0.1f, -0.1f, 1.0f, 0.0f, 0.3f,
   0.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
   0.1f, -0.1f, 0.1f, 0.0f, 0.7f, 1.0f,

   0.1f, -0.1f, 0.1f, 0.0f, 0.7f, 1.0f,
   0.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
   -0.1f, -0.1f, 0.1f, 1.0f, 1.0f, 0.12f,

   -0.1f, -0.1f, -0.1f, 0.5f, 0.5f, 0.5f,
   -0.1f, -0.1f, 0.1f, 1.0f, 1.0f, 0.12f,
   0.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,

   -0.1f, -0.1f, 0.1f, 1.0f, 1.0f, 0.12f,
   -0.1f, -0.1f, -0.1f, 0.5f, 0.5f, 0.5f,
   0.1f, -0.1f, -0.1f, 1.0f, 0.0f, 0.3f,

   -0.1f, -0.1f, 0.1f, 1.0f, 1.0f, 0.12f,
   0.1f, -0.1f, -0.1f, 1.0f, 0.0f, 0.3f,
   0.1f, -0.1f, 0.1f, 0.0f, 0.7f, 1.0f
};

vector<float>data_spin;

void dataspin()
{
	
	r_color = 1.0;
	g_color = 0.5;
	b_color = 1.0;
	
	float cx;
	float cz;
		while (rotcount < 8)
		{
			
			if (rotcount % 2 == 0) //위
			{
				cx = (r * cos(3.14 * theta / 180) + spin_x + r);
				cz = (r * sin(3.14 * theta / 180) + spin_z);
			}
			else if (rotcount % 2 == 1) //아래
			{
				cx = (r * cos(3.14 * theta / 180) + spin_x - r);
				cz = (r * sin(3.14 * theta / 180) + spin_z);
			}
			data_spin.push_back(cx);
			data_spin.push_back(0.0);
			data_spin.push_back(cz);
			data_spin.push_back(r_color);
			data_spin.push_back(g_color);
			data_spin.push_back(b_color);

			theta -= 1;
			if (theta % 180 == 0)
			{
				r *= 1.4;
				rotcount++;
				spin_x = cx;
				spin_z = cz;
			}
		}
		rotcount = 0;
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
	glGenVertexArrays(4, VAO);

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
	
	if (rotlinechk)
	{
	//vertex
	glBindVertexArray(VAO[3]);
	glGenBuffers(2, &VBO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* data_spin.size(), &data_spin[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//->color
	glBindBuffer(GL_ARRAY_BUFFER, VBO[7]); // 색상
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data_spin.size(), &data_spin[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	}
}


void timer(int value)
{
	if (check) {
		
		if (rotlinechk == true) {
			int speed = 24;
			Qt_x = data_spin[speed * Rshape_count];
			Qt_y = data_spin[speed * Rshape_count + 1];
			Qt_z = data_spin[speed * Rshape_count + 2];
			Ht_x = data_spin[speed * Lshape_count];
			Ht_y = data_spin[speed * Lshape_count + 1];
			Ht_z = data_spin[speed * Lshape_count + 2];
			Rshape_count--;
			Lshape_count++;

			if (Lshape_count == data_spin.size() / 24|| Rshape_count ==-1 ) {
				Lshape_count=0;
				Rshape_count = 359;
			}
		}
	}
	
		if (Linestate == true) {
			if (Linerotatestate == true) {
				La_y += 1.0f;
			}
			else if (Linerotatestate == false) {
				La_y += -1.0f;
			}
		}
	

		glutPostRedisplay();
		glutTimerFunc(10, timer, 1);
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
		L_Matrix = glm::translate(L_Matrix, glm::vec3(Lt_x, Lt_y, Lt_z));
		L_Matrix = glm::rotate(L_Matrix, glm::radians(La_x), glm::vec3(1.0f, 0.0f, 0.0f));
		L_Matrix = glm::rotate(L_Matrix, glm::radians(La_y), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int LinetransformLocation = glGetUniformLocation(s_program, "transform");
		glUniformMatrix4fv(LinetransformLocation, 1, GL_FALSE, glm::value_ptr(L_Matrix));
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_LINES, 0, 6);


		glm::mat4 H_Matrix = glm::mat4(1.0f);
		H_Matrix = glm::rotate(H_Matrix, glm::radians(La_x), glm::vec3(1.0f, 0.0f, 0.0f));
		H_Matrix = glm::rotate(H_Matrix, glm::radians(La_y), glm::vec3(0.0f, 1.0f, 0.0f));
		H_Matrix = glm::translate(H_Matrix, glm::vec3(Ht_x, Ht_y, Ht_z));
		H_Matrix = glm::rotate(H_Matrix, glm::radians(Ha_x), glm::vec3(1.0f, 0.0f, 0.0f));
		H_Matrix = glm::rotate(H_Matrix, glm::radians(Ha_y), glm::vec3(0.0f, 1.0f, 0.0f));
		H_Matrix = glm::scale(H_Matrix, glm::vec3(Sh_x, Sh_y, Sh_z));
		unsigned int HtransformLocation = glGetUniformLocation(s_program, "transform");
		glUniformMatrix4fv(HtransformLocation, 1, GL_FALSE, glm::value_ptr(H_Matrix));
		glBindVertexArray(VAO[1]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glm::mat4 Q_Matrix = glm::mat4(1.0f);
		Q_Matrix = glm::rotate(Q_Matrix, glm::radians(La_x), glm::vec3(1.0f, 0.0f, 0.0f));
		Q_Matrix = glm::rotate(Q_Matrix, glm::radians(La_y), glm::vec3(0.0f, 1.0f, 0.0f));
		Q_Matrix = glm::translate(Q_Matrix, glm::vec3(Qt_x, Qt_y, Qt_z));
		Q_Matrix = glm::rotate(Q_Matrix, glm::radians(Qa_x), glm::vec3(1.0f, 0.0f, 0.0f));
		Q_Matrix = glm::rotate(Q_Matrix, glm::radians(Qa_y), glm::vec3(0.0f, 1.0f, 0.0f));
		H_Matrix = glm::scale(H_Matrix, glm::vec3(1.0f, 1.0f, 1.0f));
		unsigned int QtransformLocation = glGetUniformLocation(s_program, "transform");
		glUniformMatrix4fv(QtransformLocation, 1, GL_FALSE, glm::value_ptr(Q_Matrix));
		glBindVertexArray(VAO[2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		qobj = gluNewQuadric();
		gluQuadricDrawStyle(qobj, GLU_LINE);
		gluSphere(qobj, S_sq, 15, 15);

		if (rotlinechk)
		{
			glm::mat4 R_Matrix = glm::mat4(1.0f); // 단위 행렬로 초기화 
			R_Matrix = glm::rotate(R_Matrix, glm::radians(La_x), glm::vec3(1.0f, 0.0f, 0.0f));
			R_Matrix = glm::rotate(R_Matrix, glm::radians(La_y), glm::vec3(0.0f, 1.0f, 0.0f));
			R_Matrix = glm::translate(R_Matrix, glm::vec3(Lt_x, Lt_y, Lt_z));
			R_Matrix = glm::rotate(R_Matrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			R_Matrix = glm::rotate(R_Matrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			unsigned int SpintransformLocation = glGetUniformLocation(s_program, "transform");
			glUniformMatrix4fv(SpintransformLocation, 1, GL_FALSE, glm::value_ptr(R_Matrix));
			glBindVertexArray(VAO[3]);
			glLineWidth(1.5f);
			glDrawArrays(GL_LINE_STRIP, 0, data_spin.size()/6);
		}
		

		glutSwapBuffers();
	}

	void checkcollec()
	{
	 rotlinechk = false;
	 check = false;
	 rotateline = false;
	 Linerotatestate = false;
	 Linestate = false;
	 h_vertex = 0.07;
	 rot = 0.0f;
	 La_y = -30.0f;
	 La_x = 30.0f;
	 Ha_x = 0.0f;
	 Ha_y = 0.0f;
	 Qa_x = 0.0f;
	 Qa_y = 0.0f;

	 Ht_x = -0.7f;
	 Ht_y = 0.1f;
	 Ht_z = 0.0f;
	 Qt_x = 0.7f;
	 Qt_y = 0.1f;
	 Qt_z = 0.0f;

	 Sh_x = 1.0f;
	 Sh_y = 1.0f;
	 Sh_z = 1.0f;
	 S_sq = 0.1f;

	 Lt_x = 0.0f;
	 Lt_y = 0.0f;
	 Lt_z = 0.0f;

	 r_color, g_color, b_color;
	 r = 0.05;
	 spin_x = 0.0;
	 spin_z = 0.0;
	 rotcount = 0;
	 Lshape_count = 0;
	 Rshape_count = 359;
	 theta = 180;
	}

	GLvoid KeyBoard(unsigned char Key, int x, int y)
	{
		switch (Key)
		{
		case 'h':
			Linestate = true;
			Linerotatestate = !Linerotatestate;
			break;
		case 'c':
			checkcollec();
			break;
		case 's':
			Ht_y -= 0.05f;
			break;
		case 'w':
			Ht_y += 0.05f;
			break;
		case 'd':
			Ht_x += 0.05f;
			break;
		case 'a':
			Ht_x -= 0.05f;
			break;
		case 'j':
			Qt_x -= 0.05f;
			break;
		case 'i':
			Qt_y += 0.05f;
			break;
		case 'k':
			Qt_y -= 0.05f;
			break;
		case 'l':
			Qt_x += 0.05f;
			break;

			// # 신축
		case 'q':
			Sh_x -= 0.05;
			Sh_y -= 0.05;
			Sh_z -= 0.05;
			S_sq += 0.01;
			break;
		case 'e':
			Sh_x += 0.05;
			Sh_y += 0.05;
			Sh_z += 0.05;
			S_sq -= 0.01;
			break;
		case '1':
			Sh_z -= 0.05;
			Sh_x -= 0.05;
			Sh_y -= 0.05;
			Ht_x += 0.07f;
			Ht_y -= 0.01f;;
			break;
		case '2':
			Sh_x += 0.05;
			Sh_y += 0.05;
			Sh_z += 0.05;
			Ht_x -= 0.07f;
			Ht_y += 0.01f;
			break;
		case '3':
			Qt_y -= 0.01;
			S_sq -= 0.005f;
			Qt_x -= 0.05f;
			break;
		case '4':
			Qt_y += 0.01;
			S_sq += 0.005f;
			Qt_x += 0.05f;
			break;
			// # z축이동
		case 'z':
			Ht_z += 0.05f;
			Qt_z += 0.05f;
			break;
		case 'm':
			Ht_z -= 0.05f;
			Qt_z -= 0.05f;
			break;
		case 'r':
			dataspin();
			check = true;
			rotlinechk = true;
			break;
		
		}
	}

	GLvoid SpecialMove(int Key, int x, int y)
	{
		switch (Key)
		{
		case GLUT_KEY_DOWN:
			Ht_y -= 0.05f;
			Qt_y -= 0.05f;
			data_line[13] -= 0.05f;
			data_line[19] -= 0.05f;
			data_line[25] -= 0.05f;
			data_line[31] -= 0.05f;
			break;
		case GLUT_KEY_UP:
			Ht_y += 0.05f;
			Qt_y += 0.05f;
			data_line[13] += 0.05f;
			data_line[19] += 0.05f;
			data_line[25] += 0.05f;
			data_line[31] += 0.05f;
			break;
		}
	}

	GLvoid Reshape(int w, int h)
	{
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

		InitShader();
		InitBuffer();
		glutSpecialFunc(SpecialMove);
		glutKeyboardFunc(KeyBoard);
		glutDisplayFunc(drawScene);
		glutTimerFunc(120, timer, 1);
		glutReshapeFunc(Reshape);

		glutMainLoop();

		return 0;
	}

