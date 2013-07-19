// Music.h: interface for the Music class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSIC_H__7E3D2249_7B9B_4E54_B1FB_7B2B0E625FBD__INCLUDED_)
#define AFX_MUSIC_H__7E3D2249_7B9B_4E54_B1FB_7B2B0E625FBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Music  
{
	bool m_bMusicOn;
	bool m_bBkMusicOn;
	char m_backgroudMusic[20];
	float m_volume;
	
	HWND hWnd;
public:
	Music();
	virtual ~Music();	
	void TurnOffBackgroundMusic();		//πÿ±’±≥æ∞“Ù¿÷
	void StartBackgroundMusic();		//ø™∆Ù±≥æ∞“Ù¿÷
	bool CheckBkMusicOn();				//ºÏ≤È±≥æ∞“Ù¿÷ «∑Òø™∆Ù

	void SetCooperativeLevel(HWND hWnd);
	void OpenSoundFile(char *filename);
	void PlaySound(char *filename, bool bLoop);

	void TurnOnMusic();
	bool CheckMusicOn();							//ºÏ≤È“Ù¿÷ «∑Ò±ªø™∆Ù
	void TurnOffMusic();

	void SetMusicVolume();//…Ë÷√“Ù¡ø

	void PlayBuilding(int b);
};

#endif // !defined(AFX_MUSIC_H__7E3D2249_7B9B_4E54_B1FB_7B2B0E625FBD__INCLUDED_)
