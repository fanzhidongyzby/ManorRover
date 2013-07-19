// MP3.h: interface for the MP3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MP3_H__F5F658AD_47E4_4CCF_BD94_1AF8D2D78026__INCLUDED_)
#define AFX_MP3_H__F5F658AD_47E4_4CCF_BD94_1AF8D2D78026__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MP3  
{
public:
	MP3();
	virtual ~MP3();
	public:
	BOOL Stop();
	BOOL Pause();
	BOOL Play(CString& strPath);
private:
	HWND m_hVideo;
	BOOL m_bPause;

};

#endif // !defined(AFX_MP3_H__F5F658AD_47E4_4CCF_BD94_1AF8D2D78026__INCLUDED_)
