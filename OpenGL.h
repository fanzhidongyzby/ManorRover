
#pragma once

#include"Camera.h"
#include"Light.h"
#include "SkyDome.h"
#include "Scene.h"
#include "Interface.h"
#include "Whether.h"
#include "Music.h"
//////////////////////////////////////////OpenGL框架类///////////////////////////////////////////
class OpenGL  
{
public:	
	OpenGL();
	virtual ~OpenGL();
public:

	Interface * p_Interface;//用户界面

	Scene * p_Scene;//场景
	SkyDome *p_SkyDome;//天空

	Camera *p_Camera;//摄像机类
	Light * p_Light;//光源类
	Whether * p_Whether;//天气类

	Music * p_Music;//声音类

	HDC		hDC;		// GDI设备描述表
	HGLRC	hRC;		// 永久着色描述表
	BOOL	SetupPixelFormat(HDC hDC);
	void	init(int Width, int Height);
	void	Render();
	void	CleanUp();

};
