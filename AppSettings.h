// AppSettings.h: interface for the AppSettings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPSETTINGS_H__5C84808D_D7BE_4A26_8521_60A0760B8E00__INCLUDED_)
#define AFX_APPSETTINGS_H__5C84808D_D7BE_4A26_8521_60A0760B8E00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DataBase.h"
#include "Vector.h"
//////////////////////////记录所有的全局变量////////////////

class AppSettings  
{
public:
	static bool AllowMouseControlScene;//允许鼠标控制视角
	static char * ProgramePath;//记录程序根目录
	static DataBase * p_DataBase;//全局数据库
	static CVector2 *p_ScrSize;//窗口大小
	static CVector3 *p_Position;//视点的位置
	static CVector3 *p_Direction;//视点look方向
};

#endif // !defined(AFX_APPSETTINGS_H__5C84808D_D7BE_4A26_8521_60A0760B8E00__INCLUDED_)
