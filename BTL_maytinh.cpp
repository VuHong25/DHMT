
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
//
#include <GL/glew.h>
#include <GL/freeglut.h>
//
#include <Vector_Matrix.h>


using namespace std;

typedef struct
{
	float xyzw[4];
	//float rgba[4];
	float normal[4];
} Vertex;
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
	// Mảng dữ liệu
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },/*{ 1.0f, 1.0f, 0.0f, 1.0f },*/{ 0, 0, 1, 0 } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },/*{ 1.0f, 1.0f, 0.0f, 1.0f },*/{ 0, 0, 1, 0 } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },/*{ 1.0f, 1.0f, 0.0f, 1.0f },*/{ 0, 0, 1, 0 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1, 0, 0, 0 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } }
};
// ----------------------------------------

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) /*+ sizeof(Vertices[1].rgba)*/;

int CurrentWidth = 800,
CurrentHeight = 800;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };


bool
translated = false,
rotated = false,
scaled = false;
// ------------------------------------------
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}
//
//// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);	// position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); //color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); //normal

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
//// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
//// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
//
//
//// máy tính
mat4 model_mt;
void manmt()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.81, -0.54)) * scale(vec3(1.2, 1.5, 0.12));
	mat4 model_base = model_mt * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//model_mat_cpp = mvstack.pop();
}
void chanmt()
{

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.12, 0.8, 0.12));
	mat4 model_chan = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chan.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//model_mat_cpp = mvstack.pop();
}
void mt() {
	manmt();
	chanmt();

}
//
//
void DisplayFunc(void)
{
	
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	//ban100(0,0,0);
	mt();
	GLuint vertex_color_location = glGetUniformLocation(ProgramId, "vertex_color");
	glUniform4f(vertex_color_location, 0.0f, 0.0f, 1.0f, 1.0f);
	glUniform4f(vertex_color_location, 1.0f, 0.0f, 0.0f, 1.0f);


	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------
//
//
//	
//// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Blinn");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}

































































//#include <iostream>
//#include <fstream>
//#include <string>
//#include <assert.h>
//
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//
//#include <Vector_Matrix.h>


//using namespace std;
//
//typedef struct
//{
//	float XYZW[4];
//	float RGBA[4];
//} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
//Vertex Vertices[] =
//{
//	// v0-v1-v2 (front)
//	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
//	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
//	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
//	// v2-v3-v0
//	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
//	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
//	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
//
//	// v0-v3-v4 (right)
//	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
//	{ { 0.5f,	-0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
//	{ { 0.5f,	-0.5f,  -0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
//	// v4-v5-v0
//	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
//	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
//	{ { 0.5f,	 0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
//
//	// v0-v5-v6 (top)
//	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	// v6-v1-v0
//	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//
//	// v1-v6-v7 (left)
//	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	// v7-v2-v1
//	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
//
//	// v7-v4-v3 (bottom)
//	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
//	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
//	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
//	// v3-v2-v7
//	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
//	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
//	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
//
//	// v4-v7-v6 (back)
//	{ { 0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
//	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
//	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
//	// v6-v5-v4
//	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
//	{ { 0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
//	{ { 0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } }
//};
//
//const size_t BufferSize = sizeof(Vertices);
//const size_t VertexSize = sizeof(Vertices[0]);
//const size_t RgbOffset = sizeof(Vertices[0].XYZW);
//
//// định nghĩa stack cho ma trận
//class MatrixStack {
//	int    index;
//	int    size;
//	mat4* matrices;
//
//public:
//	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
//	{
//		matrices = new mat4[numMatrices];
//	}

//	~MatrixStack()
//	{
//		delete[]matrices;
//	}
//
//	// phép toán đẩy vào
//	mat4& push(const mat4& m) {
//		assert(index + 1 < size);
//		matrices[index++] = m;
//		return matrices[index];
//	}
//
//	// phép toán lấy ra
//	mat4& pop(void) {
//		assert(index - 1 >= 0);
//		index--;
//		return matrices[index];
//	}
//};

//int
//CurrentWidth = 800,
//CurrentHeight = 600;
//
//GLuint
//VaoId,
//VboId,
//VertexShaderId,
//FragmentShaderId,
//ProgramId;
//
//MatrixStack  mvstack;
//
//mat4  model_mat_cpp;
//
//GLuint
//model_mat_location,
//projection_mat_location;

// kích thước các bộ phận robot
//#define TORSO_HEIGHT 5.0f
//#define TORSO_WIDTH 1.0f
//
//#define HEAD_HEIGHT 1.5f
//#define HEAD_WIDTH 0.8f
//
//
//#define UPPER_ARM_HEIGHT 3.0f
//#define UPPER_ARM_WIDTH  1.0f
//
//#define LOWER_ARM_HEIGHT 2.0f
//#define LOWER_ARM_WIDTH  0.5f
//
//#define UPPER_LEG_HEIGHT 3.0f
//#define UPPER_LEG_WIDTH  1.0f
//
//#define LOWER_LEG_HEIGHT 2.0f
//#define LOWER_LEG_WIDTH  0.5f

//	// thiết lập chỉ mục cho menu, 
//	// sử dụng các chỉ số này cho các joint angles
//enum {
//	Ghe,
//	Matghe,
//	Lungghe,
//	ChantraiT,
//	ChantraiS,
//	ChanphaiT,
//	ChanphaiS,
//	NumJointAngles,	//11
//	Quit			//12
//};

// giá trị ban đầu của các Joint angles
//GLfloat
//theta[NumJointAngles] = {
//	0.0,    // Torso
//	0.0,    // Head1
//	0.0,    // Head2
//	0.0,    // RightUpperArm
//	0.0,    // RightLowerArm
//	0.0,    // LeftUpperArm
//	0.0    // LeftLowerArm
//};
//
//// khởi tạo đối tượng quay
//GLint angle = Ghe;
//
//// ------------------------------------------
//	// Mặt ghê:
//void matghe()
//{
//	mvstack.push(model_mat_cpp);
//	mat4 instance = identity_mat4();
//	instance = scale(vec3(1.2, 0.12, 1.2));
//	mat4 model_matghe = model_mat_cpp * instance;
//	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_matghe.m);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	model_mat_cpp = mvstack.pop();
//}
	//Lưng ghế
//void lungghe()
//{
//	mvstack.push(model_mat_cpp);
//	mat4 instance = identity_mat4();
//	instance = translate(vec3(0, 0.81, -0.54)) * scale(vec3(1.2, 1.5, 0.12));
//	mat4 model_lungghe = model_mat_cpp * instance;
//	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_lungghe.m);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	model_mat_cpp = mvstack.pop();
//}
//	//chân ghế
//void chan()
//{
//	mvstack.push(model_mat_cpp);
//	mat4 instance = identity_mat4();
//	instance = scale(vec3(0.12, 1.5, 0.12));
//	mat4 model_chan = model_mat_cpp * instance;
//	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chan.m);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	model_mat_cpp = mvstack.pop();
//}
//
//void boghe()
//{
//	matghe();
//	lungghe();
//	//chân trái trước
//	mvstack.push(model_mat_cpp);
//	model_mat_cpp = model_mat_cpp * translate(vec3(-0.54, -0.81, 0.54));
//	chan();
//	model_mat_cpp = mvstack.pop();
//	//chân trái sau:
//	mvstack.push(model_mat_cpp);
//	model_mat_cpp = model_mat_cpp * translate(vec3(-0.54, -0.81, -0.54));
//	chan();
//	model_mat_cpp = mvstack.pop();
//	//chân phải trước:
//	mvstack.push(model_mat_cpp);
//	model_mat_cpp = model_mat_cpp * translate(vec3(0.54, -0.81, 0.54));
//	chan();
//	model_mat_cpp = mvstack.pop();
//	//chân phải sau:
//	mvstack.push(model_mat_cpp);
//	model_mat_cpp = model_mat_cpp * translate(vec3(0.54, -0.81, -0.54));
//	chan();
//	model_mat_cpp = mvstack.pop();
//}
//// ------------------------------------------
//string ReadShaderSourceFile(string fileName) {
//	fstream reader(fileName.c_str());
//	string line;
//	string code = "";
//	while (getline(reader, line)) {
//		code += line + "\n";
//	}
//	reader.close();
//	return code;
//}
//// ------------------------------------------
//void CreatVaoVbo()
//{
//	glGenVertexArrays(1, &VaoId);
//	glBindVertexArray(VaoId);
//
//	glGenBuffers(1, &VboId);
//	glBindBuffer(GL_ARRAY_BUFFER, VboId);
//	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);
//
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//}
// ------------------------------------------
//void CreatShaders()
//{
//	string vertexSrc = ReadShaderSourceFile("./vs.shader");
//	string fragmentSrc = ReadShaderSourceFile("./fs.shader");
//
//	const GLchar* VertexShader = vertexSrc.c_str();
//	const GLchar* FragmentShader = fragmentSrc.c_str();
//
//	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
//	glCompileShader(VertexShaderId);
//
//	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
//	glCompileShader(FragmentShaderId);
//
//	ProgramId = glCreateProgram();
//	glAttachShader(ProgramId, VertexShaderId);
//	glAttachShader(ProgramId, FragmentShaderId);
//	glLinkProgram(ProgramId);
//	glUseProgram(ProgramId);
//}
//// ------------------------------------------
//void CloseFunc()
//{
//	glUseProgram(0);
//
//	glDetachShader(ProgramId, VertexShaderId);
//	glDetachShader(ProgramId, FragmentShaderId);
//
//	glDeleteShader(FragmentShaderId);
//	glDeleteShader(VertexShaderId);
//
//	glDeleteProgram(ProgramId);
//
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glDeleteBuffers(1, &VboId);
//
//	glBindVertexArray(0);
//	glDeleteVertexArrays(1, &VaoId);
//}
//// ------------------------------------------
//void DisplayFunc(void)
//{
//	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
//	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
//
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glEnable(GL_DEPTH_TEST);
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	mvstack.push(model_mat_cpp);
//	model_mat_cpp = model_mat_cpp * rotate_y(theta[Ghe]);
//	boghe();
//	model_mat_cpp = mvstack.pop();
//
//	glutSwapBuffers();
//}
// ------------------------------------------
//void ReshapeFunc(int Width, int Height)
//{
//	CurrentWidth = Width;
//	CurrentHeight = Height;
//
//	glViewport(0, 0, CurrentWidth, CurrentHeight);
//
//	float  left = -10.0, right = 10.0;
//	float  bottom = -5.0, top = 15.0;
//	float  zNear = -10.0, zFar = 10.0;
//
//	float aspect = float(CurrentWidth) / CurrentHeight;
//
//	if (aspect > 1.0) {
//		left *= aspect;
//		right *= aspect;
//	}
//	else {
//		bottom /= aspect;
//		top /= aspect;
//	}
//
//	mat4 projection = ortho(left, right, bottom, top, zNear, zFar);
//	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection.m);
//
//	model_mat_cpp = identity_mat4();
//}
//// ------------------------------------------
//void IdleFunc(void)
//{
//	glutPostRedisplay();
//}
//// ------------------------------------------
//void KeyboardFunc(unsigned char key, int x, int y)
//{
//	switch (key) {
//	case 27:
//		exit(EXIT_SUCCESS); break;
//	}
//}
// ------------------------------------------
//void MouseFunc(int button, int state, int x, int y)
//{
//
//	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//		theta[Ghe] += 5.0;
//		if (theta[Ghe] > 360.0) { theta[Ghe] -= 360.0; }
//	}
//
//	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
//		theta[Ghe] -= 5.0;
//		if (theta[Ghe] < 0.0) { theta[Ghe] += 360.0; }
//	}
//
//	glutPostRedisplay();
//}
//// ------------------------------------------
//void menu(int option)
//{
//	if (option == Quit) {
//		exit(EXIT_SUCCESS);
//	}
//
//	angle = option;
//}
// ------------------------------------------
//int main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitContextVersion(4, 0);
//	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
//	glutInitContextProfile(GLUT_CORE_PROFILE);
//	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
//	glutInitWindowSize(CurrentWidth, CurrentHeight);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//	glutCreateWindow("Chair");
//
//	glewExperimental = GL_TRUE;
//	glewInit();
//
//	CreatVaoVbo();
//	CreatShaders();
//
//	glutDisplayFunc(DisplayFunc);
//	glutReshapeFunc(ReshapeFunc);
//	glutIdleFunc(IdleFunc);
//	glutKeyboardFunc(KeyboardFunc);
//	glutMouseFunc(MouseFunc);
//	glutCloseFunc(CloseFunc);
//
//	glutMainLoop();
//	return 0;
//}

