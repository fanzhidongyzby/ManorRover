// Menu.cpp: implementation of the Menu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Menu.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Menu::Menu()
{
	m_yrot=0;
	m_zrot=0;
	m_xrot=0;
	m_speed=0;
	m_bMoving=false;
	m_bVisible=false;
}

Menu::~Menu()
{

}


//////////////////////////////////////////////////////////////////////////
//函数：Load()
//参数：3ds文件名
//功能：加载3ds文件
//////////////////////////////////////////////////////////////////////////
void Menu::Load(char *filename)
{
	Model model;
	model.Clear();
	model.Import3DS(filename);
	m_listNum=glGenLists(1);
	glNewList(m_listNum,GL_COMPILE);
	glPushMatrix();
	model.DrawModel();
	glPopMatrix();
	glEndList();
	model.Clear();

}

//////////////////////////////////////////////////////////////////////////
//函数：BuildTexture()
//参数：szPathName纹理路径，纹理ID
//功能：加载纹理
//////////////////////////////////////////////////////////////////////////
bool Menu::BuildTexture(char *szPathName, GLuint &texid)
{
	HDC      hdcTemp;                        // The DC To Hold Our Bitmap
	HBITMAP    hbmpTemp;                        // Holds The Bitmap Temporarily
	IPicture  *pPicture;                        // IPicture Interface
	OLECHAR    wszPath[MAX_PATH+1];                  // Full Path To Picture (WCHAR)
	char    szPath[MAX_PATH+1];                    // Full Path To Picture
	long    lWidth;                          // Width In Logical Units
	long    lHeight;                        // Height In Logical Units
	long    lWidthPixels;                      // Width In Pixels
	long    lHeightPixels;                      // Height In Pixels
	GLint    glMaxTexDim ;                      // Holds Maximum Texture Size
	
	if (strstr(szPathName, "http://"))                  // If PathName Contains http:// Then...
	{
		strcpy(szPath, szPathName);                    // Append The PathName To szPath
	}
	else                                // Otherwise... We Are Loading From A File
	{
		GetCurrentDirectory(MAX_PATH, szPath);              // Get Our Working Directory
		strcat(szPath, "\\Image\\"); 
		//strcat(szPath, "\\");                      // Append "\" After The Working Directory
		
		strcat(szPath, szPathName);                    // Append The PathName
	}
	
	MultiByteToWideChar(CP_ACP, 0, szPath, -1, wszPath, MAX_PATH);    // Convert From ASCII To Unicode
	HRESULT hr = OleLoadPicturePath(wszPath, 0, 0, 0, IID_IPicture, (void**)&pPicture);
	
	if(FAILED(hr))                            // If Loading Failed
		return FALSE;                          // Return False
	HDC tempDC=GetDC(0);
	hdcTemp = CreateCompatibleDC(tempDC);                // Create The Windows Compatible Device Context
	if(!hdcTemp)                            // Did Creation Fail?
	{
		pPicture->Release();                      // Decrements IPicture Reference Count
		return FALSE;                          // Return False (Failure)
	}
	ReleaseDC(NULL,tempDC);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);          // Get Maximum Texture Size Supported
	
	pPicture->get_Width(&lWidth);                    // Get IPicture Width (Convert To Pixels)
	lWidthPixels  = MulDiv(lWidth, GetDeviceCaps(hdcTemp, LOGPIXELSX), 2540);
	pPicture->get_Height(&lHeight);                    // Get IPicture Height (Convert To Pixels)
	lHeightPixels  = MulDiv(lHeight, GetDeviceCaps(hdcTemp, LOGPIXELSY), 2540);
	
	// Resize Image To Closest Power Of Two
	if (lWidthPixels <= glMaxTexDim) // Is Image Width Less Than Or Equal To Cards Limit
		lWidthPixels = 1 << (int)floor((log((double)lWidthPixels)/log(2.0f)) + 0.5f); 
	else // Otherwise Set Width To "Max Power Of Two" That The Card Can Handle
		lWidthPixels = glMaxTexDim;
	
	if (lHeightPixels <= glMaxTexDim) // Is Image Height Greater Than Cards Limit
		lHeightPixels = 1 << (int)floor((log((double)lHeightPixels)/log(2.0f)) + 0.5f);
	else // Otherwise Set Height To "Max Power Of Two" That The Card Can Handle
		lHeightPixels = glMaxTexDim;
	
	//  Create A Temporary Bitmap
	BITMAPINFO  bi = {0};                        // The Type Of Bitmap We Request
	DWORD    *pBits = 0;                        // Pointer To The Bitmap Bits
	
	bi.bmiHeader.biSize      = sizeof(BITMAPINFOHEADER);        // Set Structure Size
	bi.bmiHeader.biBitCount    = 32;                  // 32 Bit
	bi.bmiHeader.biWidth    = lWidthPixels;              // Power Of Two Width
	bi.bmiHeader.biHeight    = lHeightPixels;            // Make Image Top Up (Positive Y-Axis)
	bi.bmiHeader.biCompression  = BI_RGB;                // RGB Encoding
	bi.bmiHeader.biPlanes    = 1;                  // 1 Bitplane
	
	//  Creating A Bitmap This Way Allows Us To Specify Color Depth And Gives Us Imediate Access To The Bits
	hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);
	
	if(!hbmpTemp)                            // Did Creation Fail?
	{
		DeleteDC(hdcTemp);                        // Delete The Device Context
		pPicture->Release();                      // Decrements IPicture Reference Count
		return FALSE;                          // Return False (Failure)
	}
	
	HGDIOBJ old;
	old=SelectObject(hdcTemp, hbmpTemp);                  // Select Handle To Our Temp DC And Our Temp Bitmap Object
	
	// Render The IPicture On To The Bitmap
	pPicture->Render(hdcTemp, 0, 0, lWidthPixels, lHeightPixels, 0, lHeight, lWidth, -lHeight, 0);
	
	// Convert From BGR To RGB Format And Add An Alpha Value Of 255
	for(long i = 0; i < lWidthPixels * lHeightPixels; i++)        // Loop Through All Of The Pixels
	{
		BYTE* pPixel  = (BYTE*)(&pBits[i]);              // Grab The Current Pixel
		BYTE temp    = pPixel[0];                  // Store 1st Color In Temp Variable (Blue)
		pPixel[0]    = pPixel[2];                  // Move Red Value To Correct Position (1st)
		pPixel[2]    = temp;                      // Move Temp Value To Correct Blue Position (3rd)
		
		// This Will Make Any Black Pixels, Completely Transparent    (You Can Hardcode The Value If You Wish)
		if ((pPixel[0]==0) && (pPixel[1]==0) && (pPixel[2]==0))      // Is Pixel Completely Black
			pPixel[3]  = 0;                      // Set The Alpha Value To 0
		else                              // Otherwise
			pPixel[3]  = 255;                      // Set The Alpha Value To 255
	}
	
	glGenTextures(1, &texid);                      // Create The Texture
	
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid);                // Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    // (Modify This For The Type Of Filtering You Want)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // (Modify This For The Type Of Filtering You Want)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lWidthPixels, lHeightPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);  // (Modify This If You Want Mipmaps)
	SelectObject(hdcTemp,old);
	DeleteObject(hbmpTemp);                        // Delete The Object
	DeleteDC(hdcTemp);                          // Delete The Device Context
	
	pPicture->Release();                        // Decrements IPicture Reference Count
	
	return TRUE;                            // Return True (All Good)
	


}


//////////////////////////////////////////////////////////////////////////
//函数：AnimateMenu()
//参数：无
//功能：触发按钮动作
//////////////////////////////////////////////////////////////////////////
void Menu::AnimateMenu()
{
	switch (m_flag)
	{
	case 1:
	case 2:
	case 3:	
		m_speed=45;	
		//m_pAudioManager->PlaySound("Audios/Buttons/暴力Click_004.wav",false);
		break;
	case 4:	
		m_tempScale=m_scale/2;
		//m_pAudioManager->PlaySound("Audios/Buttons/okClick_015.wav",false);
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
//函数：Init()
//参数：float xPos, float yPos, float zPos,				按钮位置
//		float scale,									缩放
//		int yrot,int zrot,								角度
//		long left, long right, long bottom, long top,	屏幕响应区域
//		int FLAG										响应方式
//功能：初始化按钮变量
//////////////////////////////////////////////////////////////////////////
void Menu::Init(float xPos, float yPos, float zPos, float scale,int yrot,int zrot,
					   long left, long right, long bottom, long top,int FLAG)
{
	m_flag=FLAG;
	m_zrot=zrot;
	m_yrot=yrot;
	m_xPos=xPos;
	m_yPos=yPos;
	m_zPos=zPos;
	m_tempScale=m_scale=scale;
	m_clientRect.left=left;
	m_clientRect.right=right;
	m_clientRect.bottom=bottom;
	m_clientRect.top=top;
	m_scale2=m_scale;
}

//////////////////////////////////////////////////////////////////////////
//函数：RenderMenu()
//参数：无
//功能：绘制按钮
//////////////////////////////////////////////////////////////////////////
bool Menu::RenderMenu()
{
	if( !m_bVisible )
		return false;
	//float zrot;
	switch (m_flag)
	{
	case 1:
		glTranslatef(m_xPos,m_yPos,m_zPos);
		glScalef(m_scale,m_scale,m_scale);
		glRotatef((GLfloat)m_xrot,1.0f,0.0f,0.0f);
		glRotatef((GLfloat)m_yrot,0.0f,1.0f,0.0f);
		glRotatef((GLfloat)m_zrot,0.0f,0.0f,1.0f);
		glCallList(m_listNum);
		
		m_xrot+=m_speed;
		if(int(m_xrot - m_speed)%360==0 && m_bMoving==true)
		{
			m_xrot-=m_speed;
			m_speed=0;
			m_bMoving=false;
			return true;
		}
		if (m_speed==0)
			m_bMoving=false;
		else	m_bMoving=true;
		return false;
	case 2:
		glTranslatef(m_xPos,m_yPos,m_zPos);
		glScalef(m_scale,m_scale,m_scale);
		glRotatef((GLfloat)m_xrot,1.0f,0.0f,0.0f);
		glRotatef((GLfloat)m_yrot,0.0f,1.0f,0.0f);
		glRotatef((GLfloat)m_zrot,0.0f,0.0f,1.0f);
		
		glCallList(m_listNum);
		m_zrot+=m_speed;
		if(int(m_zrot - m_speed)%360==0 && m_bMoving==true)
		{
			m_zrot-=m_speed;
			m_speed=0;
			m_bMoving=false;
			return true;
		}
		if (m_speed==0)
			m_bMoving=false;
		else	m_bMoving=true;
		return false;
	case 3:
		glTranslatef(m_xPos,m_yPos,m_zPos);
		glScalef(m_scale,m_scale,m_scale);
		glRotatef((GLfloat)m_xrot,1.0f,0.0f,0.0f);
		glRotatef((GLfloat)m_yrot,0.0f,1.0f,0.0f);
		glRotatef((GLfloat)m_zrot,0.0f,0.0f,1.0f);
		
		glCallList(m_listNum);
		m_yrot+=m_speed;
		if(int(m_yrot - m_speed)%180==0 && m_bMoving==true)
		{
			m_yrot-=m_speed;
			m_speed=0;
			m_bMoving=false;
			return true;
		}
		if (m_speed==0)
			m_bMoving=false;
		else	m_bMoving=true;
		return false;
	case 4:
		if (m_tempScale!=m_scale)
			m_bMoving=true;
		if (m_tempScale<m_scale)
			m_tempScale+=m_scale/2/5;
		else
			m_tempScale=m_scale;
		glTranslatef(m_xPos,m_yPos,m_zPos);
		glScalef(m_tempScale,m_tempScale,m_tempScale);
		glRotatef((GLfloat)m_xrot,1.0f,0.0f,0.0f);
		glRotatef((GLfloat)m_yrot,0.0f,1.0f,0.0f);
		glRotatef((GLfloat)m_zrot,0.0f,0.0f,1.0f);
		glCallList(m_listNum);
		if (m_tempScale==m_scale && m_bMoving==true && m_bZoomByClick)
		{
			m_bMoving=false;
			m_bZoomByClick=false;
			return true;
		}
		
		return false;
//	case 5:	//速度指针
//		glTranslatef(m_xPos,m_yPos,m_zPos);
//		glScalef(m_scale,m_scale,m_scale);
//		zrot=m_zrot-fabs(m_pPlayer->GetSpeed())/160*180;
//		glRotatef((GLfloat)m_xrot,1.0f,0.0f,0.0f);
//		glRotatef((GLfloat)m_yrot,0.0f,1.0f,0.0f);
//		glRotatef((GLfloat)zrot,0.0f,0.0f,1.0f);
//		glCallList(m_listNum);
//		return false;
//	case 6://方向盘
//		glTranslatef(m_xPos,m_yPos,m_zPos);
//		glScalef(m_scale,m_scale,m_scale);
//		glRotatef((GLfloat)m_xrot,1.0f,0.0f,0.0f);
//		glRotatef((GLfloat)m_yrot,0.0f,1.0f,0.0f);
//		glRotatef((GLfloat)m_zrot,0.0f,0.0f,1.0f);
//		glCallList(m_listNum);
//		return false;
	case 7:
		glTranslatef(m_xPos,m_yPos,m_zPos);
		glScalef(m_scale,m_scale,m_scale);
		glRotatef((GLfloat)m_xrot,1.0f,0.0f,0.0f);
		glRotatef((GLfloat)m_yrot,0.0f,1.0f,0.0f);
		glRotatef((GLfloat)m_zrot,0.0f,0.0f,1.0f);
		
		glCallList(m_listNum);
		m_zrot+=2;
		if (m_zrot>=360)
			m_zrot-=360;
		return false;
	default:
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
//函数：Show()
//参数：无
//功能：使按钮可见
//////////////////////////////////////////////////////////////////////////
void Menu::Show()
{
	m_bVisible=true;
}

//////////////////////////////////////////////////////////////////////////
//函数：Hide()
//参数：无
//功能：使按钮不可见
//////////////////////////////////////////////////////////////////////////
void Menu::Hide()
{
	m_bVisible=false;
}

//////////////////////////////////////////////////////////////////////////
//函数：ChangeStateOfVisible()
//参数：无
//功能：改变按钮可见状态
//////////////////////////////////////////////////////////////////////////
void Menu::ChangeStateOfVisible()
{
	m_bVisible=!m_bVisible;
}

//////////////////////////////////////////////////////////////////////////
//函数：CheckClicked()
//参数：鼠标点击位置坐标
//功能：检查鼠标点击是否触发本按钮
//////////////////////////////////////////////////////////////////////////
bool Menu::CheckClicked(double xpos, double ypos)
{
	if(!m_bVisible)
		return false;
	if(xpos<=m_clientRect.right && xpos>=m_clientRect.left && 
		ypos<=m_clientRect.bottom && ypos>=m_clientRect.top)
		return true;
	return false;
}


//////////////////////////////////////////////////////////////////////////
//函数：CheckZoom
//参数：鼠标点击位置坐标
//功能：检查鼠标是否触发本按钮zoom效果
//////////////////////////////////////////////////////////////////////////
bool Menu::CheckZoom(double xpos, double ypos)
{
	if(!m_bVisible)
		return false;
	if(xpos<=m_clientRect.right && xpos>=m_clientRect.left && 
		ypos<=m_clientRect.bottom && ypos>=m_clientRect.top)
		return true;
	return false;
}
