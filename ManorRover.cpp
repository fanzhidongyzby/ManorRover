// ManorRover.cpp : Defines the entry point for the application.
//
/////////////////////////////////////////////Windows应用程序框架///////////////////////////////////////////
#include "stdafx.h"
#include "DataBase.h"
#include "OpenGL.h"


OpenGL* m_OpenGL;
HDC		hDC;		// GDI设备句柄,将窗口连接到 GDI( 图形设备接口)
HGLRC	hRC=NULL;	// 渲染描述句柄,将OpenGL调用连接到设备描述表 
HWND	hWnd=NULL;	// 保存 Windows 分配给程序的窗口句柄
int		Width = GetSystemMetrics(SM_CXSCREEN);// 窗口宽
int		Height= GetSystemMetrics(SM_CYSCREEN);// 窗口高
int		bits  = 16;	// 颜色深度

void MsgLoop()
{   
	MSG msg; 
	BOOL fMessage;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
	while(msg.message != WM_QUIT)	// 消息循环
	{   
		fMessage = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);
		if(fMessage)				//有消息
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else  m_OpenGL->Render();	//无消息
	}
}
LRESULT WINAPI MsgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam )// 消息处理
{	
	bool ON=false;
	
	int midX=Width>>1;//右移运算，相当于除以2
	int midY=Height>>1;
	
	POINT p;
	GetCursorPos(&p);
	int mouse_x=p.x;
	int mouse_y=p.y;
	
	CString s;
	switch(message)
	{	
	case WM_CREATE:						// 建立窗口
		hDC = GetDC(hWnd);				// 获取当前窗口的设备句柄
		m_OpenGL->SetupPixelFormat(hDC);// 调用显示模式安装功能
		return 0;		break;
	case WM_CLOSE:						// 关闭窗口
		m_OpenGL->CleanUp();			// 结束处理
		PostQuitMessage(0);
		return 0;		break;
	case WM_SIZE:						// 窗口尺寸变化
		Height = HIWORD(lParam);		// 窗口的高
		Width  = LOWORD(lParam);		// 窗口的宽
		if (Height==0)	Height=1;		// 防止被0 除
		m_OpenGL->init(Width,Height);
		return 0;		break;
	case WM_DESTROY:					// 退出消息
		PostQuitMessage(0);
		return 0;		break;
	case WM_KEYUP:						// 按ESC退出，全屏模式必需要加入的退出方式。
		switch (wParam)
		{ 
		case VK_ESCAPE:
			m_OpenGL->CleanUp();	// 结束处理
			PostQuitMessage(0);
			return 0;   break;
		case VK_SPACE:
			AppSettings::AllowMouseControlScene=!AppSettings::AllowMouseControlScene;			
			//ShowCursor(TRUE);			
			SetCursorPos(midX,midY);
			break;
		} 		
		break;
		case WM_LBUTTONUP:
		
			ON=!ON;
			if (ON)
			{
				m_OpenGL->p_Music->TurnOffBackgroundMusic();
			}
			else
			{
				m_OpenGL->p_Music->TurnOffBackgroundMusic();
			}
			
			//AppSettings::p_DataBase->Open();
			//AppSettings::p_DataBase->Close();
			
			//		m_OpenGL->p_DynamicObj->scrtoxyz(mouse_x,mouse_y);
			//		s.Format("x=%f,y=%f,z=%f"
			//			,m_OpenGL->p_DynamicObj->xyz.x
			//			,m_OpenGL->p_DynamicObj->xyz.y
			//			,m_OpenGL->p_DynamicObj->xyz.z);
			//		AfxMessageBox(s);
			
			break;
		default:			break;
	}
	m_OpenGL->p_Interface->Proc(message, wParam, lParam);
	return (DefWindowProc(hWnd, message, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,LPSTR CmdLine, int iCmdShow)// WinMain程序入口
{ 
	GetCurrentDirectory(256,AppSettings::ProgramePath);//记录程序根目录
	
	// 注册窗口类
	bool fullScreen =TRUE;
	DWORD	dwExStyle;		// Window 扩展风格
	DWORD	dwStyle;		// Window 窗口风格
	RECT	windowRect;		// 窗口尺寸
	int		nX=0,nY=0;
	dwExStyle=WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;	// 使窗口具有3D外观
	dwStyle=WS_OVERLAPPEDWINDOW;				// 使用标准窗口
	//WS_OVERLAPPEDWINDOW是有标题栏,窗口菜单,最大、小化按钮和可调整尺寸的窗口
	int wid=Width;		// 获取当前屏幕宽
	int hei=Height;		// 获取当前屏幕高
	nX=(wid-Width)/2;nY=(hei-Height)/2;			// 计算窗口居中用
	//-------------------------------------------------------------------
	AdjustWindowRectEx(&windowRect,dwStyle,FALSE,dwExStyle);
	//根据窗口风格来调整窗口尺寸达到要求的大小
	//char cc[]="tml";
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"tml", NULL };
	RegisterClassEx( &wc );
	m_OpenGL=new OpenGL();//
	//hWnd = CreateWindowEx(NULL,"tml","ManorRover",dwStyle|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,10, 10,800, 600,NULL,NULL,hInst,NULL);	// 创建窗口
	hWnd = CreateWindowEx(NULL,"tml","ManorRover",
		WS_POPUP | WS_CLIPSIBLINGS | WS_VISIBLE,0, 0,
		Width,Height,NULL,NULL,hInst,NULL);	// 创建窗口
	ShowWindow( hWnd, SW_SHOWDEFAULT );				// 显示窗口
	UpdateWindow( hWnd );							// 刷新窗口
	MsgLoop();										// 进入消息循环
	return 0;
}


