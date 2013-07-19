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
	::CoInitialize(NULL);//��ʼ��OLE/COM�⻷��
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");   //�������Ӷ���ʵ��

		char dir[256];
		strcpy(dir,AppSettings::ProgramePath);
		strcat(dir,"/DataBase");
		SetCurrentDirectory(dir);		
		_bstr_t strConnect="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Data.mdb;Persist Security Info=False";
		m_pConnection->Open(strConnect,"","",0);   //�����ݿ�
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
				AfxMessageBox("��������Ϊ��");
				return;
			}
			
			// ������и��ֶβ������б����
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
		//AfxMessageBox("���ݿ����ӹر�");
	}
	::CoUninitialize(); 
}

void DataBase ::Execute(_bstr_t sqlstring)
{
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pCommand.CreateInstance(__uuidof(Command));
	m_pCommand->ActiveConnection = m_pConnection; // �������Ӹ�����
	m_pCommand->CommandText =sqlstring; // SQL���
	m_pRecordset = m_pCommand->Execute(NULL, NULL,adCmdText); // ִ��SQL��䣬���ؼ�¼�� 

}