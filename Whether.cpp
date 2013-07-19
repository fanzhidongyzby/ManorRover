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
	GLfloat fogDensity=0.0005f;	// ���Ũ��

	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();	
	
	GLuint	fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };						// �������3������
	GLuint	fogfilter = 2;
	//GLfloat	fogColor[4] = { 0.6f, 0.6f, 0.6f, 0.6f };						// �����ɫ	

	GLfloat fogColor[4]= {0.2f, 0.2f, 0.2f, 0.4f};	

	glFogi(GL_FOG_MODE,fogMode[fogfilter]);							// �������(new)
	glFogfv(GL_FOG_COLOR, fogColor);                  					// �����ɫ(new)
	glFogf(GL_FOG_DENSITY, fogDensity);                 						// ���Ũ��(new)
	glHint(GL_FOG_HINT, GL_DONT_CARE);                   				// �����Ⱦ��ʽ(new)
//	glTranslatef(m_pPlayer->GetPosition().x,0,m_pPlayer->GetPosition().z);
	glFogf(GL_FOG_START, start);                          				// ��Ŀ�ʼ���(new)
	glFogf(GL_FOG_END,end);                            				// �����ֹ���(new)
	glHint(GL_FOG_HINT,GL_FASTEST);//GL_NICEST);
	
	glEnable(GL_FOG);
	glPopMatrix();
	glPopAttrib();
}