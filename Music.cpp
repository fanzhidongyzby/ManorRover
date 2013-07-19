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
//函数：StartBackgroundMusic()
//参数：无
//功能：开启背景音乐
//////////////////////////////////////////////////////////////////////////
void Music::StartBackgroundMusic()
{
	sndPlaySound(m_backgroudMusic,SND_ASYNC|SND_LOOP|SND_NODEFAULT);
	m_bBkMusicOn=true;
}


//////////////////////////////////////////////////////////////////////////
//函数：TurnOffBackgroundMusic()
//参数：无
//功能：关闭背景音乐
//////////////////////////////////////////////////////////////////////////
void Music::TurnOffBackgroundMusic()
{
	sndPlaySound(m_backgroudMusic,NULL);
	m_bBkMusicOn=false;
}

//////////////////////////////////////////////////////////////////////////
//函数：CheckBkMusicOn()
//参数：无
//功能：检查背景音乐是否开启
//////////////////////////////////////////////////////////////////////////
bool Music::CheckBkMusicOn()
{
	return m_bBkMusicOn;
}

//////////////////////////////////////////////////////////////////////////
//函数：TurnOffMusic()
//参数：无
//功能：关闭声音
//////////////////////////////////////////////////////////////////////////
void Music::TurnOffMusic()
{
	m_bMusicOn=false;
	//m_volume = 0.00000f;
}

//////////////////////////////////////////////////////////////////////////
//函数:CheckMusicOn()
//参数:无
//功能:检查音乐是否被开启
//////////////////////////////////////////////////////////////////////////
bool Music::CheckMusicOn()
{
	return m_bMusicOn;
}

//////////////////////////////////////////////////////////////////////////
//函数:TurnOnMusic()
//参数:无
//功能:关闭声音
//////////////////////////////////////////////////////////////////////////
void Music::TurnOnMusic()
{
	m_bMusicOn=true;
}
//////////////////////////////////////////////////////////////////////////
//函数：OpenSoundFile()
//参数：文件名（含路径）
//功能：打开文件
//////////////////////////////////////////////////////////////////////////
//void Music::OpenSoundFile(char *filename)
//{
//	LPVOID lpPtr1;							// 指针1;
//	LPVOID lpPtr2;							// 指针2;
//	HRESULT hResult;
//	DWORD dwLen1,dwLen2;
//	LPVOID m_pMemory;						// 指向WAVE文件的指针
//	LPWAVEFORMATEX m_pFormat=NULL;			// LPWAVEFORMATEX类型指针；
//	LPVOID m_pData=NULL;					// 指向语音数据块的指针；
//	DWORD m_dwSize=0;						// WAVE文件中语音数据块的长度；
//	FILE *filein;
//	DWORD dwSize;							// 存放WAV文件长度；
//	
//	
//	filein=fopen(filename, "rt");			// 打开.wav文件；
//	
//	// fseek(): 将 filein 所指文件的位置指针移动到以 0 为基址，
//	// SEEK_END 为偏移量的位置
//	fseek(filein,0,SEEK_END);				// 移动到WAVE文件中存放文件长度的地方
//	dwSize = ftell(filein);					// 获取WAVE文件长度
//	
//	fseek(filein,0,SEEK_SET);				// 定位到打开的WAVE文件文件头；
//	ftell(filein); 
//	
//	// 为m_pMemory分配内存，用来存放WAVE文件中的数据；
//	m_pMemory = GlobalAlloc (GMEM_FIXED, dwSize);
//	fread(m_pMemory, 1, dwSize, filein);	// 读取文件中的数据；
//	fclose(filein);
//	
//	LPDWORD pdw,pdwEnd;
//	DWORD dwRiff,dwType, dwLength;
//	
//	// 首先清空指针和变量以备使用
//	if (m_pFormat)							// 格式块指针
//		m_pFormat = NULL;
//	if (m_pData)							// 数据块指针,类型:LPBYTE
//		m_pData = NULL;
//	if (m_dwSize)							// 数据长度,类型:DWORD
//		m_dwSize = 0;
//	
//	pdw = (DWORD *) m_pMemory;
//	dwRiff = *pdw++;
//	dwLength = *pdw++;
//	dwType = *pdw++;
//	if (dwRiff != MAKEFOURCC ('R', 'I', 'F', 'F'))		// 判断文件头是否为"RIFF"字符；
//		return ;
//	if (dwType != MAKEFOURCC ('W', 'A', 'V', 'E'))		// 判断文件格式是否为"WAVE"；
//		return ;
//	// 寻找格式块,数据块位置及数据长度
//	pdwEnd = (DWORD *)((BYTE *) m_pMemory+dwLength -4);
//	bool m_bend=false;
//	while ((pdw < pdwEnd)&&(!m_bend))
//		// pdw文件没有指到文件末尾并且没有获取到声音数据时继续;
//	{
//		dwType = *pdw++;
//		dwLength = *pdw++;
//		switch (dwType)
//		{
//		case MAKEFOURCC('f', 'm', 't', ' '):		// 如果为"fmt"标志；
//			if (!m_pFormat)							// 获取LPWAVEFORMATEX结构数据；
//			{
//				if (dwLength < sizeof (WAVEFORMAT))
//					return ;
//				m_pFormat = (LPWAVEFORMATEX) pdw;
//			}
//			break;
//		case MAKEFOURCC('d', 'a', 't', 'a'):		// 如果为"data"标志；
//			if (!m_pData || !m_dwSize)
//			{
//				m_pData = (LPBYTE) pdw;				// 得到指向声音数据块的指针；
//				m_dwSize = dwLength;				// 获取声音数据块的长度；
//				if (m_pFormat)
//					m_bend=TRUE;
//			}
//			break;
//		}
//		pdw = (DWORD *)((BYTE *) pdw + ((dwLength + 1)&~1));// 修改pdw指针，继续循环；
//		
//	}
//	
//	DSBUFFERDESC BufferDesc;							// 定义DSUBUFFERDESC结构对象；
//	memset (&BufferDesc, 0, sizeof (BufferDesc));
//	BufferDesc.lpwfxFormat = (LPWAVEFORMATEX)m_pFormat;
//	BufferDesc.dwSize = sizeof (DSBUFFERDESC);
//	BufferDesc.dwBufferBytes = m_dwSize;
//	BufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;  
//	// 创建声音数据缓冲；
//	if (m_lpDirectSound->CreateSoundBuffer (&BufferDesc, &m_lpDSoundBuffer, 0) == DS_OK)
//		// 载入声音数据，这里使用两个指针lpPtr1,lpPtr2来指向DirectSoundBuffer缓冲区的数据，这是为了处理大型WAVE文件而设计的。dwLen1,dwLen2分别对应这两个指针所指向的缓冲区的长度。
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
//函数：PlaySound()
//参数：要播放文件的文件名（含路径）,是否循环播放（true循环播放，false不循环播放）
//功能：播放文件
//////////////////////////////////////////////////////////////////////////
//void Music::PlaySound(char *filename, bool bLoop)
//{
//	if(!m_bMusicOn)
//		return;
//	HRESULT hRes;
//	m_lpDirectSound=NULL;
//	m_lpDSoundBuffer=NULL;
//	hRes = ::DirectSoundCreate(0, &m_lpDirectSound, 0);	// 创建DirectSound对象；
//	if( hRes != DS_OK )
//	{
//		return;
//	}
//	
//	m_bBkMusicOn = 1;
//	SetCooperativeLevel(m_hWnd);
//	// 设置声音设备优先级别为"NORMAL"；
//	OpenSoundFile(filename);
//	
//	if (bLoop)
//		m_lpDSoundBuffer->Play(0, 0, 1);
//	else
//		m_lpDSoundBuffer->Play(0,0,0);
//	/*m_lpDSoundBuffer->GetSize()*/
//					// 播放WAVE声音数据
//	/*SetMusicVolume();*/
//}

//void Music::SetCooperativeLevel(HWND hWnd)
//{
//	//m_hWnd=hWnd;
//	m_lpDirectSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL);		// 设置声音设备优先级别为"NORMAL"；
//}

//////////////////////////////////////////////////////////////////////////
//函数：SetMusicVolume()
//参数：无
//功能：设置音量
//////////////////////////////////////////////////////////////////////////
//void Music::SetMusicVolume()
//{
//	if (m_volume < 0.00001f)							// m_volume不小于0
//	{
//		m_volume = 0.00001f;
//	}
//	// 将获得的线性值转换为分贝
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
//函数：PlayBuilding()
//参数：相关建筑物的标识号
//功能：播放建筑物信息
//////////////////////////////////////////////////////////////////////////
//void Music::PlayBuilding(int b)
//{
//	char filename[35];
//	sprintf(filename,"Audios/Buildings/%d\0",b);
//	char a[5]=".wav";
//	strcat(filename,a);
//	PlaySound(filename,false);
//}