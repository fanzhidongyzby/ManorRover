// Camera.cpp: implementation of the Camera class.
//
//////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include "Camera.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Camera::Camera()
{
	g_eye[0]= AppSettings::p_Position->x;//
	g_eye[1]=AppSettings::p_Position->y;
	g_eye[2]=AppSettings::p_Position->z;//
	g_look[0]=AppSettings::p_Position->x+AppSettings::p_Direction->x;
	g_look[1]=AppSettings::p_Position->y+AppSettings::p_Direction->y;
	g_look[2]=AppSettings::p_Position->z+AppSettings::p_Direction->z;
	
	g_Angle=0;//��λ��
	g_elev=0;//������

	gluLookAt(g_eye[0],g_eye[1],g_eye[2],g_look[0],g_look[1],g_look[2],0.0,1.0,0.0);
}

Camera::~Camera()
{

}

bool Camera:: WalkingThroughCamera()//�������
{
	float speed=10.0f;							//����

	if(!KEY_DOWN(VK_LEFT)&&!KEY_DOWN(VK_RIGHT)&&!KEY_DOWN(33)&&!KEY_DOWN(34)&&AppSettings::AllowMouseControlScene)
	{
		//ShowCursor(FALSE);
		//�������ӽ�
		POINT mousePos;
		int midX=(int) AppSettings::p_ScrSize->x/2;
		int midY=(int) AppSettings::p_ScrSize->y/2;

		GetCursorPos(&mousePos);
		SetCursorPos(midX,midY);

		g_Angle+=(float)((mousePos.x-midX))/10.0f;
		g_elev+=(float)((-mousePos.y+midY))/10.0f;
	}




	if (KEY_DOWN(VK_SHIFT))  speed   =speed*4;//��SHIFTʱ�ļ���

	if (KEY_DOWN(VK_LEFT))   g_Angle-=speed*2;//��ת
	else  if (KEY_DOWN('A'))  //����
	{
		g_eye[2]-=(float)cos(rad_xz)*speed;		//�ӵ��z����
		g_eye[0]+=(float)sin(rad_xz)*speed;		//�ӵ��x����
	}

	if (KEY_DOWN(VK_RIGHT))  g_Angle+=speed*2;//��ת
	else if(KEY_DOWN('D'))//����
	{
		g_eye[2]+=(float)cos(rad_xz)*speed;		//�ӵ��z����
		g_eye[0]-=(float)sin(rad_xz)*speed;		//�ӵ��x����
	}
	rad_xz = float (3.13149* g_Angle/180.0f);	//����������ת�Ƕ�
	if (KEY_DOWN(33)) g_elev +=0.2f;	//Page UP  ��
	if (KEY_DOWN(34)) g_elev -=0.2f;	//Page Down��
	if (g_elev<-100)	g_elev  =-100;	//������
	if (g_elev> 100)	g_elev  = 100;	//������
	if (KEY_DOWN(VK_UP)||KEY_DOWN('W'))				//ǰ��
	{ g_eye[2]+=sin(rad_xz)*speed;
	g_eye[0]+=cos(rad_xz)*speed;
	}
	if (KEY_DOWN(VK_DOWN)||KEY_DOWN('S'))			//����
	{ g_eye[2]-=sin(rad_xz)*speed;
	g_eye[0]-=cos(rad_xz)*speed;
	}
	if (KEY_DOWN(VK_HOME))//����
	{
		g_eye[1]+=speed;
	}

	if (KEY_DOWN(VK_END))//�½�
	{
		g_eye[1]-=speed;
	}


	//���Ƶ���������뿪����
	/*  if(g_eye[0]<  MAP_SCALE*2)		 g_eye[0]=  MAP_SCALE*2;
	if(g_eye[0]> (MAP_W-3)*MAP_SCALE) g_eye[0]= (MAP_W-3)*MAP_SCALE;
	if(g_eye[2]<-(MAP_W-3)*MAP_SCALE) g_eye[2]=-(MAP_W-3)*MAP_SCALE;
	if(g_eye[2]> -MAP_SCALE*2)		 g_eye[2]= -MAP_SCALE*2;*/


//	if (g_eye[0]<-(MAP*2-20))	g_eye[0]= -(MAP*2-20); //�ӵ��X��������
//	if (g_eye[0]<-(MAP*2-20))	g_eye[0]= -(MAP*2-20); //�ӵ��X��������
//	if (g_eye[0]> (MAP*2-20))	g_eye[0]=  (MAP*2-20);
//	if (g_eye[2]<-(MAP*2-20))	g_eye[2]= -(MAP*2-20); //�ӵ��Z��������
//	if (g_eye[2]> (MAP*2-20))	g_eye[2]=  (MAP*2-20);



	//������ķ���
	g_look[0] = float(g_eye[0] + 100*cos(rad_xz));
	g_look[2] = float(g_eye[2] + 100*sin(rad_xz));
	g_look[1] = g_eye[1];
	//����modelview������
	gluLookAt(g_eye[0],g_eye[1],g_eye[2],g_look[0],g_look[1]+g_elev,g_look[2],0.0,1.0,0.0);
	AppSettings::p_Position->Init((float)g_eye[0],(float)g_eye[1],(float)g_eye[2]);
	AppSettings::p_Direction->Init((float)(g_look[0]-g_eye[0]),(float)g_elev,(float)(g_look[2]-g_eye[2]));
	return TRUE;



}
