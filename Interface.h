// Interface.h: interface for the Interface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERFACE_H__E182468C_5D48_4027_98C5_9D15019605E8__INCLUDED_)
#define AFX_INTERFACE_H__E182468C_5D48_4027_98C5_9D15019605E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Menu.h"
#define MAX_NUMBER_OF_MENUS 50

class Interface  
{
public:
	Interface();
	virtual ~Interface();
	void AddMenu(char *filename,								//按钮对应3ds文件名
		float xPos=-209.0f,float yPos=10.0f,float zPos=-6.0f,	//按钮位置
		float scale=22.0f,int yrot=0,int zrot=0,				//按钮大小及初始角度
		float perX1=0.9f,float perX2=1.0f,float perY1=0.675676f,float perY2=0.621622f,	//按钮响应矩形范围
		int flag=1);		
	void Load();
	void RenderInterface();										//绘制交互界面（我们采用的3d界面接口，所以自行绘制）
	void Proc(UINT uMsg,WPARAM wParam,LPARAM lParam);
private:
	bool m_keys[256];
	int m_nMenus;
	Menu m_menus[MAX_NUMBER_OF_MENUS];

};

#endif // !defined(AFX_INTERFACE_H__E182468C_5D48_4027_98C5_9D15019605E8__INCLUDED_)
