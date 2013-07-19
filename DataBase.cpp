// DataBase.cpp: implementation of the DataBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataBase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DataBase::DataBase()
{
	
	
}

DataBase::~DataBase()
{
	
}

void DataBase::Open()
{
	::CoInitialize(NULL);//初始化OLE/COM库环境
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");   //创建连接对象实例

		char dir[256];
		strcpy(dir,AppSettings::ProgramePath);
		strcat(dir,"/DataBase");
		SetCurrentDirectory(dir);		
		_bstr_t strConnect="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Data.mdb;Persist Security Info=False";
		m_pConnection->Open(strConnect,"","",0);   //打开数据库
		SetCurrentDirectory(AppSettings::ProgramePath);
		this->Execute("select ID as ID ,Name as Name from DataTest ");

		_variant_t var;
		CString strName,strAge,s;
		int Count=0;
		try
		{
			if(!m_pRecordset->BOF)
				m_pRecordset->MoveFirst();
			else
			{
				AfxMessageBox("表内数据为空");
				return;
			}
			
			// 读入库中各字段并加入列表框中
			while(!m_pRecordset->adoEOF)
			{
				var = m_pRecordset->GetCollect("ID");
				if(var.vt != VT_NULL)
					strName = (LPCSTR)_bstr_t(var);
				var = m_pRecordset->GetCollect("Name");
				if(var.vt != VT_NULL)
					strAge = (LPCSTR)_bstr_t(var);
				
				s+= strName + " --> "+strAge+'\n' ;
				Count++;
				m_pRecordset->MoveNext();
			}
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
		//s.Format("%d",Count);
		AfxMessageBox(s);
		
		m_pRecordset->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); 
		PostQuitMessage(0); 
	}
}


void DataBase::Close()
{
	if(m_pConnection->State)
	{
		m_pConnection->Close();
		//AfxMessageBox("数据库连接关闭");
	}
	::CoUninitialize(); 
}

void DataBase ::Execute(_bstr_t sqlstring)
{
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pCommand.CreateInstance(__uuidof(Command));
	m_pCommand->ActiveConnection = m_pConnection; // 将库连接赋于它
	m_pCommand->CommandText =sqlstring; // SQL语句
	m_pRecordset = m_pCommand->Execute(NULL, NULL,adCmdText); // 执行SQL语句，返回记录集 

}