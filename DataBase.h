// DataBase.h: interface for the DataBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASE_H__F1EABA11_13BA_4884_88CF_1164804C3A57__INCLUDED_)
#define AFX_DATABASE_H__F1EABA11_13BA_4884_88CF_1164804C3A57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StdAfx.h"
class DataBase  
{
public:
	_ConnectionPtr m_pConnection; //连接数据库的智能指针
    _RecordsetPtr	m_pRecordset;//结果记录集指针
	_CommandPtr     m_pCommand;//执行对象指针
	DataBase();
	virtual ~DataBase();
	void Open();
	void Close();
	void Execute(_bstr_t sqlstring);//执行语句


};

#endif // !defined(AFX_DATABASE_H__F1EABA11_13BA_4884_88CF_1164804C3A57__INCLUDED_)
