
#pragma once

#include"Camera.h"
#include"Light.h"
#include "SkyDome.h"
#include "Scene.h"
#include "Interface.h"
#include "Whether.h"
#include "Music.h"
//////////////////////////////////////////OpenGL�����///////////////////////////////////////////
class OpenGL  
{
public:	
	OpenGL();
	virtual ~OpenGL();
public:

	Interface * p_Interface;//�û�����

	Scene * p_Scene;//����
	SkyDome *p_SkyDome;//���

	Camera *p_Camera;//�������
	Light * p_Light;//��Դ��
	Whether * p_Whether;//������

	Music * p_Music;//������

	HDC		hDC;		// GDI�豸������
	HGLRC	hRC;		// ������ɫ������
	BOOL	SetupPixelFormat(HDC hDC);
	void	init(int Width, int Height);
	void	Render();
	void	CleanUp();

};
