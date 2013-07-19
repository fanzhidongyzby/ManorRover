// Plant.h: interface for the Plant class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLANT_H__4D08EE46_EA67_428F_8789_C20639A0381C__INCLUDED_)
#define AFX_PLANT_H__4D08EE46_EA67_428F_8789_C20639A0381C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "treeVector.h"

class Plant  
{
	int BuildTexture(char *szPathName, GLuint &texid);	//��������

	GLuint m_treeTexture[10];				//��ľ����
	GLuint m_grassTexture[6];				//��������
public:
	Plant();
	virtual ~Plant();
	void DrawPlant(float x,float y,float z,			//������ľ����
				  float h, float s,
				  int textureID,bool tag=true);
	void LoadPlant();								//������ľ����

};

#endif // !defined(AFX_PLANT_H__4D08EE46_EA67_428F_8789_C20639A0381C__INCLUDED_)
