// Camera.h: interface for the Camera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__E33A23F7_4E8B_4D23_AC79_F5F2612BF38E__INCLUDED_)
#define AFX_CAMERA_H__E33A23F7_4E8B_4D23_AC79_F5F2612BF38E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////�����////////////////////////////////////////////////////////////////////
class Camera  
{
	
	GLdouble	 g_eye[3];		//�ӵ�
	GLdouble	 g_look[3];		//����

	float		rad_xz;			//�Ƕ�
	float		g_Angle;		//����ת
	float		g_elev;			//������
public:
	Camera();
	bool  WalkingThroughCamera();//�������
	bool  CollisiomDetection();
	bool  Tips();
	virtual ~Camera();
	
};

#endif // !defined(AFX_CAMERA_H__E33A23F7_4E8B_4D23_AC79_F5F2612BF38E__INCLUDED_)
