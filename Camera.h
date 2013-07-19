// Camera.h: interface for the Camera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__E33A23F7_4E8B_4D23_AC79_F5F2612BF38E__INCLUDED_)
#define AFX_CAMERA_H__E33A23F7_4E8B_4D23_AC79_F5F2612BF38E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////摄像机////////////////////////////////////////////////////////////////////
class Camera  
{
	
	GLdouble	 g_eye[3];		//视点
	GLdouble	 g_look[3];		//焦点

	float		rad_xz;			//角度
	float		g_Angle;		//左右转
	float		g_elev;			//仰俯角
public:
	Camera();
	bool  WalkingThroughCamera();//穿行相机
	bool  CollisiomDetection();
	bool  Tips();
	virtual ~Camera();
	
};

#endif // !defined(AFX_CAMERA_H__E33A23F7_4E8B_4D23_AC79_F5F2612BF38E__INCLUDED_)
