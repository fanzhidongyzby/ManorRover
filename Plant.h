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
	int BuildTexture(char *szPathName, GLuint &texid);	//载入纹理

	GLuint m_treeTexture[10];				//树木纹理
	GLuint m_grassTexture[6];				//花草纹理
public:
	Plant();
	virtual ~Plant();
	void DrawPlant(float x,float y,float z,			//绘制树木花草
				  float h, float s,
				  int textureID,bool tag=true);
	void LoadPlant();								//载入树木纹理

};

#endif // !defined(AFX_PLANT_H__4D08EE46_EA67_428F_8789_C20639A0381C__INCLUDED_)
