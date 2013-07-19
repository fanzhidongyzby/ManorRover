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
//////////////////////////��¼���е�ȫ�ֱ���////////////////

class AppSettings  
{
public:
	static bool AllowMouseControlScene;//�����������ӽ�
	static char * ProgramePath;//��¼�����Ŀ¼
	static DataBase * p_DataBase;//ȫ�����ݿ�
	static CVector2 *p_ScrSize;//���ڴ�С
	static CVector3 *p_Position;//�ӵ��λ��
	static CVector3 *p_Direction;//�ӵ�look����
};

#endif // !defined(AFX_APPSETTINGS_H__5C84808D_D7BE_4A26_8521_60A0760B8E00__INCLUDED_)
