#include "stdafx.h"
#include "OpenGL.h"
int i=0;
//////////////////////////////////////////////////////////////////////
OpenGL::OpenGL()
{
}
OpenGL::~OpenGL()
{	
	CleanUp();
}
BOOL OpenGL::SetupPixelFormat(HDC hDC0)//��ⰲװOpenGL
{	
	int nPixelFormat;					  // ���ص��ʽ
	hDC=hDC0;
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
		1,                                // �汾�� 
		PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
		PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
		PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
		PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
		16,                               // 24 λ��ɫ��� 
		0, 0, 0, 0, 0, 0,                 // ������ɫλ 
		0,                                // û�з�͸���Ȼ��� 
		0,                                // ������λλ 
		0,                                // ���ۼӻ��� 
		0, 0, 0, 0,                       // �����ۼ�λ 
		16,                               // 32 λ��Ȼ���     
		0,                                // ��ģ�建�� 
		0,                                // �޸������� 
		PFD_MAIN_PLANE,                   // ���� 
		0,                                // ���� 
		0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	}; 
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		MessageBox(NULL,"û�ҵ����ʵ���ʾģʽ","Error",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	SetPixelFormat(hDC,nPixelFormat,&pfd);//���õ�ǰ�豸�����ص��ʽ
	hRC = wglCreateContext(hDC);          //��ȡ��Ⱦ�������
	wglMakeCurrent(hDC, hRC);             //������Ⱦ�������

	//������������ģ�ͣ���ʾ�ƹ�
	p_SkyDome=new SkyDome();
	p_Camera= new Camera();
	p_Light=new Light();
	p_Light->Light0();

	p_Scene=new  Scene();
	p_Scene->Load();

	p_Whether=new Whether();
	p_Whether->Fog();

	p_Music=new Music();

	p_Interface=new  Interface();
	p_Interface->Load();
	return TRUE;
}
void OpenGL::init(int Width, int Height)
{	
	glViewport(0,0,Width,Height);			// ����OpenGL�ӿڴ�С��	
	glMatrixMode(GL_PROJECTION);			// ���õ�ǰ����ΪͶӰ����
	glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
	gluPerspective							// ����͸��ͼ
		( 54.0f,							// ͸�ӽ�����Ϊ 45 ��
		(GLfloat)Width/(GLfloat)Height,	// ���ڵĿ���߱�
		0.1f,								// ��Ұ͸�����:����1.0f
		3000.0f							// ��Ұ͸�����:ʼ��0.1fԶ��1000.0f
		);
	// �������������ƣ���һ���������þ�ͷ��Ƕȣ��ڶ��������ǳ���ȣ�������Զ�����С�
	glMatrixMode(GL_MODELVIEW);				// ���õ�ǰ����Ϊģ����ͼ����
	glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
	//====================================================
}
void OpenGL::Render()//OpenGLͼ�δ���
{
	int wid=AppSettings::p_ScrSize->x;
	int hei=AppSettings::p_ScrSize->y;
	glViewport(0,0,wid,hei);
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();
	
	gluPerspective(45.0f,(GLfloat)wid/(GLfloat)hei,0.1f,6000.0f);
	glMatrixMode(GL_MODELVIEW);	
	
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);			 // ����ˢ�±���ɫ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// ˢ�±���
	glLoadIdentity();								 // ���õ�ǰ��ģ�͹۲����


	//�������
	p_Camera->WalkingThroughCamera();
//	glEnable(GL_DEPTH_TEST);//������Ȳ���


	//��Ⱦ���
	p_SkyDome->Init();
	p_SkyDome->RenderSkyDome();

	
	//��Ⱦ����
	p_Scene->Render();



	//��Ⱦ�û�����
	glViewport(0,0,wid,hei);
	p_Interface->RenderInterface();

	glFlush();										 // ���´���
	SwapBuffers(hDC);								 // �л�������
}
void OpenGL::CleanUp()//���OpenGL
{	
	ShowCursor(TRUE);	                             //�����
	wglMakeCurrent(hDC, NULL);                       //���OpenGL
	wglDeleteContext(hRC);                           //���OpenGL
}
