// MP3.cpp: implementation of the MP3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MP3.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MP3::MP3()
{
	m_hVideo = NULL;
}

MP3::~MP3()
{
	if(m_hVideo !=NULL)
	{
		MCIWndDestroy(m_hVideo);
	}
}

BOOL MP3::Play(CString &strPath)
{
	m_hVideo = NULL;
	if(m_hVideo == NULL)
	{
		m_hVideo = MCIWndCreate(AfxGetMainWnd()->GetSafeHwnd(),
		  AfxGetInstanceHandle(),
		   WS_CHILD |MCIWNDF_NOMENU,strPath);	
	}
	else
	{
		MCIWndHome(m_hVideo);
	}
	MCIWndPlay(m_hVideo);
	m_bPause = FALSE;
	return TRUE;
}

BOOL MP3::Pause()
{
	if(m_bPause)
	{
		MCIWndResume(m_hVideo);
		m_bPause = FALSE;
	}
	else
	{
		MCIWndPause(m_hVideo);
		m_bPause = TRUE;
	}

	return m_bPause;
}

BOOL MP3::Stop()
{
	MCIWndStop(m_hVideo);
	if(m_hVideo !=NULL)
	{
		MCIWndDestroy(m_hVideo);
	
	}

	return TRUE;
}
