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
	void AddMenu(char *filename,								//��ť��Ӧ3ds�ļ���
		float xPos=-209.0f,float yPos=10.0f,float zPos=-6.0f,	//��ťλ��
		float scale=22.0f,int yrot=0,int zrot=0,				//��ť��С����ʼ�Ƕ�
		float perX1=0.9f,float perX2=1.0f,float perY1=0.675676f,float perY2=0.621622f,	//��ť��Ӧ���η�Χ
		int flag=1);		
	void Load();
	void RenderInterface();										//���ƽ������棨���ǲ��õ�3d����ӿڣ��������л��ƣ�
	void Proc(UINT uMsg,WPARAM wParam,LPARAM lParam);
private:
	bool m_keys[256];
	int m_nMenus;
	Menu m_menus[MAX_NUMBER_OF_MENUS];

};

#endif // !defined(AFX_INTERFACE_H__E182468C_5D48_4027_98C5_9D15019605E8__INCLUDED_)
