// Whether.cpp: implementation of the Whether class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Whether.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Whether::Whether()
{

}

Whether::~Whether()
{

}
void Whether::Fog()
{
	float start=100.0;//500.0;
	float end=4000.0;
	GLfloat fogDensity=0.0005f;	// 雾的浓度

	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();	
	
	GLuint	fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };						// 储存雾的3种类型
	GLuint	fogfilter = 2;
	//GLfloat	fogColor[4] = { 0.6f, 0.6f, 0.6f, 0.6f };						// 雾的颜色	

	GLfloat fogColor[4]= {0.2f, 0.2f, 0.2f, 0.4f};	

	glFogi(GL_FOG_MODE,fogMode[fogfilter]);							// 雾的类型(new)
	glFogfv(GL_FOG_COLOR, fogColor);                  					// 雾的颜色(new)
	glFogf(GL_FOG_DENSITY, fogDensity);                 						// 雾的浓度(new)
	glHint(GL_FOG_HINT, GL_DONT_CARE);                   				// 雾的渲染方式(new)
//	glTranslatef(m_pPlayer->GetPosition().x,0,m_pPlayer->GetPosition().z);
	glFogf(GL_FOG_START, start);                          				// 雾的开始深度(new)
	glFogf(GL_FOG_END,end);                            				// 雾的终止深度(new)
	glHint(GL_FOG_HINT,GL_FASTEST);//GL_NICEST);
	
	glEnable(GL_FOG);
	glPopMatrix();
	glPopAttrib();
}