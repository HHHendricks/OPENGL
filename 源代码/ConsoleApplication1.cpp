#include"pch.h"
#pragma comment(lib, "glaux.lib")
#include <windows.h>
#include <gl\glaux.h>
#include <gl\glut.h>

GLuint g_texture = 0;
GLfloat xrot = 0.0f;
GLfloat yrot = 0.0f;
GLfloat zrot = 0.0f;                                    // Keep Going
GLfloat yOffset = 0.0f;
GLfloat xOffset = 0.0f;
GLfloat zoom = 1.0f;


//绘制一个立方体
int DrawCube(void)
{
	glBindTexture(GL_TEXTURE_2D, g_texture);        //使用贴图纹理

	glPushMatrix();        //压入变换矩阵

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);            //旋转矩阵，这里绕x轴旋转。
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);            //旋转矩阵，这里绕y轴旋转。
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);            //绕z轴旋转，这里zrot是角度制的度数。
	glTranslatef(xOffset, yOffset, 0.0f);
	glScalef(zoom, zoom, zoom);

	glBegin(GL_QUADS);  //启用四边形带绘制模式绘制

	// 绘制前面，这里开始确定纹理坐标，然后是确定点的位置
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	// 绘制后面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	// 上面
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	//底面
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	// 右面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	// 左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glEnd();

	glPopMatrix(); //弹出变换矩阵

	return 1;

}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // 清楚颜色数据和深度数据（清屏）
	glLoadIdentity();                                    // Reset The View
	glTranslatef(0.0f, 0.0f, -5.0f);

	DrawCube();

	glutSwapBuffers();            //交换缓冲区。显示图形
}

//载入一个.bmp格式的贴图纹理
int LoadGLTextures(GLuint& unTexture, const char* chFileName)
{
	AUX_RGBImageRec *TextureImage;                    //保存贴图数据的指针
	TextureImage = auxDIBImageLoad(L"1231.bmp"); //载入贴图数据

	glGenTextures(1, &unTexture);                    // 创建一个纹理，unTexture

	glBindTexture(GL_TEXTURE_2D, unTexture);        //绑定纹理，然后对该纹理区添加纹理数据

	//设置纹理的信息，
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //设置滤波为线性滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //线性滤波

	if (TextureImage)                //释放资源
	{
		if (TextureImage->data)
		{
			free(TextureImage->data);
		}
		free(TextureImage);
	}

	return 1;
}


//初始化
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);            //清理颜色，为黑色，（也可认为是背景颜色）

	glCullFace(GL_BACK);                        //背面裁剪(背面不可见)
	glEnable(GL_CULL_FACE);                        //启用裁剪
	glEnable(GL_TEXTURE_2D);
	LoadGLTextures(g_texture, "1231.bmp");            //载入纹理贴图
}

//当窗口大小改变时，会调用这个函数
void reshape(GLsizei w, GLsizei h)
{
	//这里小说明一下：矩阵模式是不同的，他们各自有一个矩阵。投影相关
	//只能用投影矩阵。(只是目前情况下哦，等我学多了可能就知道为什么了。)

	glViewport(0, 0, w, h);        //设置视口
	glMatrixMode(GL_PROJECTION);    //设置矩阵模式为投影变换矩阵，
	glLoadIdentity();                //变为单位矩阵
	gluPerspective(60, (GLfloat)w / h, 0, 1000);    //设置投影矩阵
	glMatrixMode(GL_MODELVIEW);        //设置矩阵模式为视图矩阵(模型)
	glLoadIdentity();                //变为单位矩阵
}


void SpecialKey(GLint key, GLint x, GLint  y)
{
	if (key == GLUT_KEY_UP)
	{
		yOffset += 0.1f;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		xOffset -= 0.1f;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		yOffset -= 0.1f;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		xOffset += 0.1f;
	}

	glutPostRedisplay();
}

void myKey(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
		xrot += 5;
	else if (key == 'w' || key == 'W')
		yrot += 5;
	else if (key == 'e' || key == 'E')
		zrot += 5;
	else if (key == 'r' || key == 'R')
		zoom += 0.1f;
	else if (key == 't' || key == 'T')
		zoom -= 0.1f;

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);        //Opnegl初始化
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //设置显示模式为双缓冲，RGEBA

	glutInitWindowSize(800, 600);            //窗口大小
	glutInitWindowPosition(100, 100);        //窗口位置
	glutCreateWindow("hello");                //创建一个标题为hello的窗口
	init();                                //初始化资源,这里一定要在创建窗口以后，不然会无效。
	glutDisplayFunc(display);                //窗口大小改变时的回调
	glutReshapeFunc(reshape);                //绘制图形时的回调
	//glutIdleFunc(MyIdle);
	glutSpecialFunc(&SpecialKey);
	glutKeyboardFunc(&myKey);
	glutMainLoop();                            //主循环。
	return 0;
}