// Light.cpp: implementation of the Light class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Light.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Light::Light()
{

}

Light::~Light()
{

}


void Light::Light0()
{	
	GLfloat light_position[]= {AppSettings::p_Position->x,6.0,AppSettings::p_Position->z,2.0};
	GLfloat light_ambient[]={0.8f,0.8f,0.8f,1.0f};
	GLfloat light_diffuse[]={1.0f,1.0f,1.0f,1.0f,1.0f};//{0.5,0.5,0.5,1.0};
	GLfloat light_specular[]={1.0f,1.0f,1.0f,1.0f};
	float light_direction[]={AppSettings::p_Direction->x,AppSettings::p_Direction->y,AppSettings::p_Direction->z};
	float angle=180.0;
	float kl=10.0;


	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,light_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,angle);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT,kl);
	glEnable(GL_LIGHT0);
}
