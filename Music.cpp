// Music.cpp: implementation of the Music class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Music.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Music::Music()
{
	m_bMusicOn=true;
	strcpy(m_backgroudMusic,"Audio\\okClick_015.wav");
	m_bBkMusicOn=false;
	m_volume=1.0f;
}

Music::~Music()
{

}

//////////////////////////////////////////////////////////////////////////
//������StartBackgroundMusic()
//��������
//���ܣ�������������
//////////////////////////////////////////////////////////////////////////
void Music::StartBackgroundMusic()
{
	sndPlaySound(m_backgroudMusic,SND_ASYNC|SND_LOOP|SND_NODEFAULT);
	m_bBkMusicOn=true;
}


//////////////////////////////////////////////////////////////////////////
//������TurnOffBackgroundMusic()
//��������
//���ܣ��رձ�������
//////////////////////////////////////////////////////////////////////////
void Music::TurnOffBackgroundMusic()
{
	sndPlaySound(m_backgroudMusic,NULL);
	m_bBkMusicOn=false;
}

//////////////////////////////////////////////////////////////////////////
//������CheckBkMusicOn()
//��������
//���ܣ���鱳�������Ƿ���
//////////////////////////////////////////////////////////////////////////
bool Music::CheckBkMusicOn()
{
	return m_bBkMusicOn;
}

//////////////////////////////////////////////////////////////////////////
//������TurnOffMusic()
//��������
//���ܣ��ر�����
//////////////////////////////////////////////////////////////////////////
void Music::TurnOffMusic()
{
	m_bMusicOn=false;
	//m_volume = 0.00000f;
}

//////////////////////////////////////////////////////////////////////////
//����:CheckMusicOn()
//����:��
//����:��������Ƿ񱻿���
//////////////////////////////////////////////////////////////////////////
bool Music::CheckMusicOn()
{
	return m_bMusicOn;
}

//////////////////////////////////////////////////////////////////////////
//����:TurnOnMusic()
//����:��
//����:�ر�����
//////////////////////////////////////////////////////////////////////////
void Music::TurnOnMusic()
{
	m_bMusicOn=true;
}
//////////////////////////////////////////////////////////////////////////
//������OpenSoundFile()
//�������ļ�������·����
//���ܣ����ļ�
//////////////////////////////////////////////////////////////////////////
//void Music::OpenSoundFile(char *filename)
//{
//	LPVOID lpPtr1;							// ָ��1;
//	LPVOID lpPtr2;							// ָ��2;
//	HRESULT hResult;
//	DWORD dwLen1,dwLen2;
//	LPVOID m_pMemory;						// ָ��WAVE�ļ���ָ��
//	LPWAVEFORMATEX m_pFormat=NULL;			// LPWAVEFORMATEX����ָ�룻
//	LPVOID m_pData=NULL;					// ָ���������ݿ��ָ�룻
//	DWORD m_dwSize=0;						// WAVE�ļ����������ݿ�ĳ��ȣ�
//	FILE *filein;
//	DWORD dwSize;							// ���WAV�ļ����ȣ�
//	
//	
//	filein=fopen(filename, "rt");			// ��.wav�ļ���
//	
//	// fseek(): �� filein ��ָ�ļ���λ��ָ���ƶ����� 0 Ϊ��ַ��
//	// SEEK_END Ϊƫ������λ��
//	fseek(filein,0,SEEK_END);				// �ƶ���WAVE�ļ��д���ļ����ȵĵط�
//	dwSize = ftell(filein);					// ��ȡWAVE�ļ�����
//	
//	fseek(filein,0,SEEK_SET);				// ��λ���򿪵�WAVE�ļ��ļ�ͷ��
//	ftell(filein); 
//	
//	// Ϊm_pMemory�����ڴ棬�������WAVE�ļ��е����ݣ�
//	m_pMemory = GlobalAlloc (GMEM_FIXED, dwSize);
//	fread(m_pMemory, 1, dwSize, filein);	// ��ȡ�ļ��е����ݣ�
//	fclose(filein);
//	
//	LPDWORD pdw,pdwEnd;
//	DWORD dwRiff,dwType, dwLength;
//	
//	// �������ָ��ͱ����Ա�ʹ��
//	if (m_pFormat)							// ��ʽ��ָ��
//		m_pFormat = NULL;
//	if (m_pData)							// ���ݿ�ָ��,����:LPBYTE
//		m_pData = NULL;
//	if (m_dwSize)							// ���ݳ���,����:DWORD
//		m_dwSize = 0;
//	
//	pdw = (DWORD *) m_pMemory;
//	dwRiff = *pdw++;
//	dwLength = *pdw++;
//	dwType = *pdw++;
//	if (dwRiff != MAKEFOURCC ('R', 'I', 'F', 'F'))		// �ж��ļ�ͷ�Ƿ�Ϊ"RIFF"�ַ���
//		return ;
//	if (dwType != MAKEFOURCC ('W', 'A', 'V', 'E'))		// �ж��ļ���ʽ�Ƿ�Ϊ"WAVE"��
//		return ;
//	// Ѱ�Ҹ�ʽ��,���ݿ�λ�ü����ݳ���
//	pdwEnd = (DWORD *)((BYTE *) m_pMemory+dwLength -4);
//	bool m_bend=false;
//	while ((pdw < pdwEnd)&&(!m_bend))
//		// pdw�ļ�û��ָ���ļ�ĩβ����û�л�ȡ����������ʱ����;
//	{
//		dwType = *pdw++;
//		dwLength = *pdw++;
//		switch (dwType)
//		{
//		case MAKEFOURCC('f', 'm', 't', ' '):		// ���Ϊ"fmt"��־��
//			if (!m_pFormat)							// ��ȡLPWAVEFORMATEX�ṹ���ݣ�
//			{
//				if (dwLength < sizeof (WAVEFORMAT))
//					return ;
//				m_pFormat = (LPWAVEFORMATEX) pdw;
//			}
//			break;
//		case MAKEFOURCC('d', 'a', 't', 'a'):		// ���Ϊ"data"��־��
//			if (!m_pData || !m_dwSize)
//			{
//				m_pData = (LPBYTE) pdw;				// �õ�ָ���������ݿ��ָ�룻
//				m_dwSize = dwLength;				// ��ȡ�������ݿ�ĳ��ȣ�
//				if (m_pFormat)
//					m_bend=TRUE;
//			}
//			break;
//		}
//		pdw = (DWORD *)((BYTE *) pdw + ((dwLength + 1)&~1));// �޸�pdwָ�룬����ѭ����
//		
//	}
//	
//	DSBUFFERDESC BufferDesc;							// ����DSUBUFFERDESC�ṹ����
//	memset (&BufferDesc, 0, sizeof (BufferDesc));
//	BufferDesc.lpwfxFormat = (LPWAVEFORMATEX)m_pFormat;
//	BufferDesc.dwSize = sizeof (DSBUFFERDESC);
//	BufferDesc.dwBufferBytes = m_dwSize;
//	BufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;  
//	// �����������ݻ��壻
//	if (m_lpDirectSound->CreateSoundBuffer (&BufferDesc, &m_lpDSoundBuffer, 0) == DS_OK)
//		// �����������ݣ�����ʹ������ָ��lpPtr1,lpPtr2��ָ��DirectSoundBuffer�����������ݣ�����Ϊ�˴������WAVE�ļ�����Ƶġ�dwLen1,dwLen2�ֱ��Ӧ������ָ����ָ��Ļ������ĳ��ȡ�
//		hResult=m_lpDSoundBuffer->Lock(0,m_dwSize,&lpPtr1,&dwLen1,&lpPtr2,&dwLen2,0);
//	if (hResult == DS_OK)
//	{
//		memcpy (lpPtr1, m_pData, dwLen1);
//		if(dwLen2>0) 
//		{
//			BYTE *m_pData1=(BYTE*)m_pData+dwLen1;
//			m_pData=(void *)m_pData1;
//			memcpy(lpPtr2,m_pData, dwLen2);
//		}
//		m_lpDSoundBuffer->Unlock (lpPtr1, dwLen1, lpPtr2, dwLen2);
//	}
//	GlobalFree(m_pMemory);
//	m_pMemory=NULL;
//}


//////////////////////////////////////////////////////////////////////////
//������PlaySound()
//������Ҫ�����ļ����ļ�������·����,�Ƿ�ѭ�����ţ�trueѭ�����ţ�false��ѭ�����ţ�
//���ܣ������ļ�
//////////////////////////////////////////////////////////////////////////
//void Music::PlaySound(char *filename, bool bLoop)
//{
//	if(!m_bMusicOn)
//		return;
//	HRESULT hRes;
//	m_lpDirectSound=NULL;
//	m_lpDSoundBuffer=NULL;
//	hRes = ::DirectSoundCreate(0, &m_lpDirectSound, 0);	// ����DirectSound����
//	if( hRes != DS_OK )
//	{
//		return;
//	}
//	
//	m_bBkMusicOn = 1;
//	SetCooperativeLevel(m_hWnd);
//	// ���������豸���ȼ���Ϊ"NORMAL"��
//	OpenSoundFile(filename);
//	
//	if (bLoop)
//		m_lpDSoundBuffer->Play(0, 0, 1);
//	else
//		m_lpDSoundBuffer->Play(0,0,0);
//	/*m_lpDSoundBuffer->GetSize()*/
//					// ����WAVE��������
//	/*SetMusicVolume();*/
//}

//void Music::SetCooperativeLevel(HWND hWnd)
//{
//	//m_hWnd=hWnd;
//	m_lpDirectSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL);		// ���������豸���ȼ���Ϊ"NORMAL"��
//}

//////////////////////////////////////////////////////////////////////////
//������SetMusicVolume()
//��������
//���ܣ���������
//////////////////////////////////////////////////////////////////////////
//void Music::SetMusicVolume()
//{
//	if (m_volume < 0.00001f)							// m_volume��С��0
//	{
//		m_volume = 0.00001f;
//	}
//	// ����õ�����ֵת��Ϊ�ֱ�
//    LONG volume = (LONG)(100.0 * 20.0 * log10(m_volume));
//	
//    if (volume < DSBVOLUME_MIN) 
//	{
//		volume = DSBVOLUME_MIN;
//	}
//	else if (volume > DSBVOLUME_MAX) 
//	{
//		
//		LONG	volume = DSBVOLUME_MAX;
//	}
//	
//	m_lpDSoundBuffer->SetVolume(volume);
//	m_lpDSoundBuffer->Play(0, 0, 0);//dwFlag);
//}

//////////////////////////////////////////////////////////////////////////
//������PlayBuilding()
//��������ؽ�����ı�ʶ��
//���ܣ����Ž�������Ϣ
//////////////////////////////////////////////////////////////////////////
//void Music::PlayBuilding(int b)
//{
//	char filename[35];
//	sprintf(filename,"Audios/Buildings/%d\0",b);
//	char a[5]=".wav";
//	strcat(filename,a);
//	PlaySound(filename,false);
//}