// Menu.h: interface for the Menu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENU_H__C2B9C971_19FE_490B_BF74_495729B516D1__INCLUDED_)
#define AFX_MENU_H__C2B9C971_19FE_490B_BF74_495729B516D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Model.h"
class Menu  
{
public:
	Menu();
	virtual ~Menu();
	bool CheckZoom(double xpos, double ypos);
	bool CheckClicked(double xpos,double ypos);
	void ChangeStateOfVisible();	//�ı䰴ť�ɼ�״̬���ɼ���Ϊ���ɼ������ɼ���Ϊ�ɼ�
	void Hide();					//�ť���ɼ�
	void Show();					//�ť�ɼ�
	bool RenderMenu();	
	void Init(float xPos, float yPos, float zPos, float scale,
		int yrot,int zrot, long left, long right, long bottom, long top,int FLAG=1);
	void AnimateMenu();
	bool BuildTexture(char *szPathName, GLuint &textid);
	void Load(char *filename);
	//////////////////////////////////////////////////////////////////////////////////////
public:
	bool m_bMoving;
	int m_zrot;
	int m_yrot;
	float m_scale;
	float m_scale2;
	RECT m_clientRect;
	float m_xPos,m_yPos,m_zPos;
	bool m_bZoomByClick;
private:
	int m_listNum;
	bool m_bVisible;
	int m_flag;
	GLuint m_speed;
	GLuint m_xrot;
	float m_tempScale;


};

#endif // !defined(AFX_MENU_H__C2B9C971_19FE_490B_BF74_495729B516D1__INCLUDED_)
