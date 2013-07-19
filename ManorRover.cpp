// ManorRover.cpp : Defines the entry point for the application.
//
/////////////////////////////////////////////WindowsӦ�ó�����///////////////////////////////////////////
#include "stdafx.h"
#include "DataBase.h"
#include "OpenGL.h"


OpenGL* m_OpenGL;
HDC		hDC;		// GDI�豸���,���������ӵ� GDI( ͼ���豸�ӿ�)
HGLRC	hRC=NULL;	// ��Ⱦ�������,��OpenGL�������ӵ��豸������ 
HWND	hWnd=NULL;	// ���� Windows ���������Ĵ��ھ��
int		Width = GetSystemMetrics(SM_CXSCREEN);// ���ڿ�
int		Height= GetSystemMetrics(SM_CYSCREEN);// ���ڸ�
int		bits  = 16;	// ��ɫ���

void MsgLoop()
{   
	MSG msg; 
	BOOL fMessage;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
	while(msg.message != WM_QUIT)	// ��Ϣѭ��
	{   
		fMessage = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);
		if(fMessage)				//����Ϣ
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else  m_OpenGL->Render();	//����Ϣ
	}
}
LRESULT WINAPI MsgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam )// ��Ϣ����
{	
	bool ON=false;
	
	int midX=Width>>1;//�������㣬�൱�ڳ���2
	int midY=Height>>1;
	
	POINT p;
	GetCursorPos(&p);
	int mouse_x=p.x;
	int mouse_y=p.y;
	
	CString s;
	switch(message)
	{	
	case WM_CREATE:						// ��������
		hDC = GetDC(hWnd);				// ��ȡ��ǰ���ڵ��豸���
		m_OpenGL->SetupPixelFormat(hDC);// ������ʾģʽ��װ����
		return 0;		break;
	case WM_CLOSE:						// �رմ���
		m_OpenGL->CleanUp();			// ��������
		PostQuitMessage(0);
		return 0;		break;
	case WM_SIZE:						// ���ڳߴ�仯
		Height = HIWORD(lParam);		// ���ڵĸ�
		Width  = LOWORD(lParam);		// ���ڵĿ�
		if (Height==0)	Height=1;		// ��ֹ��0 ��
		m_OpenGL->init(Width,Height);
		return 0;		break;
	case WM_DESTROY:					// �˳���Ϣ
		PostQuitMessage(0);
		return 0;		break;
	case WM_KEYUP:						// ��ESC�˳���ȫ��ģʽ����Ҫ������˳���ʽ��
		switch (wParam)
		{ 
		case VK_ESCAPE:
			m_OpenGL->CleanUp();	// ��������
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

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,LPSTR CmdLine, int iCmdShow)// WinMain�������
{ 
	GetCurrentDirectory(256,AppSettings::ProgramePath);//��¼�����Ŀ¼
	
	// ע�ᴰ����
	bool fullScreen =TRUE;
	DWORD	dwExStyle;		// Window ��չ���
	DWORD	dwStyle;		// Window ���ڷ��
	RECT	windowRect;		// ���ڳߴ�
	int		nX=0,nY=0;
	dwExStyle=WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;	// ʹ���ھ���3D���
	dwStyle=WS_OVERLAPPEDWINDOW;				// ʹ�ñ�׼����
	//WS_OVERLAPPEDWINDOW���б�����,���ڲ˵�,���С����ť�Ϳɵ����ߴ�Ĵ���
	int wid=Width;		// ��ȡ��ǰ��Ļ��
	int hei=Height;		// ��ȡ��ǰ��Ļ��
	nX=(wid-Width)/2;nY=(hei-Height)/2;			// ���㴰�ھ�����
	//-------------------------------------------------------------------
	AdjustWindowRectEx(&windowRect,dwStyle,FALSE,dwExStyle);
	//���ݴ��ڷ�����������ڳߴ�ﵽҪ��Ĵ�С
	//char cc[]="tml";
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"tml", NULL };
	RegisterClassEx( &wc );
	m_OpenGL=new OpenGL();//
	//hWnd = CreateWindowEx(NULL,"tml","ManorRover",dwStyle|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,10, 10,800, 600,NULL,NULL,hInst,NULL);	// ��������
	hWnd = CreateWindowEx(NULL,"tml","ManorRover",
		WS_POPUP | WS_CLIPSIBLINGS | WS_VISIBLE,0, 0,
		Width,Height,NULL,NULL,hInst,NULL);	// ��������
	ShowWindow( hWnd, SW_SHOWDEFAULT );				// ��ʾ����
	UpdateWindow( hWnd );							// ˢ�´���
	MsgLoop();										// ������Ϣѭ��
	return 0;
}


