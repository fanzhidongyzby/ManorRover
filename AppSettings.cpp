// AppSettings.cpp: implementation of the AppSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppSettings.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////全局变量的初始化
CVector2* AppSettings::p_ScrSize=new CVector2( GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
CVector3* AppSettings::p_Position=new CVector3(0.0f,1.8f,0.0f);
CVector3* AppSettings::p_Direction=new CVector3(1.0f,0.0f,1.0f);

bool AppSettings::AllowMouseControlScene=false;
char * AppSettings::ProgramePath=new char [256];
DataBase * AppSettings::p_DataBase=new DataBase();
