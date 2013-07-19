// Plant.cpp: implementation of the Plant class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Plant.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Plant::Plant()
{

}

Plant::~Plant()
{

}

//////////////////////////////////////////////////////////////////////////
// 函数：DrawTree(float x,float y,float z,float h, float s,int textureID,bool tag)
// 参数：参数x,y,z为绘制位置,h、s分别为绘制的高度和缩放比例，textureID为纹理号,tag为标志位
// 功能：绘制花草树木
//////////////////////////////////////////////////////////////////////////
void Plant::DrawPlant(float x,float y,float z,float h, float s,int textureID,bool tag)
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ZERO);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	vector3_t X(mat[0], mat[4], mat[8]);
	vector3_t Z(mat[1], mat[5], mat[9]); 
	if(tag)
		glBindTexture(GL_TEXTURE_2D, m_treeTexture[textureID]);
	else glBindTexture(GL_TEXTURE_2D, m_grassTexture[textureID]);
	vector3_t pos(x,0.0,z);
	//pos.y = GetHeight(x, -z) + h + s;
	pos.y = y + h + s;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex3fv((pos+(X+Z)*-h).v);//左下点
	glTexCoord2f(1.0,0.0);glVertex3fv((pos+(X-Z)* h).v);//右下点
	glTexCoord2f(1.0,1.0);glVertex3fv((pos+(X+Z)* h).v);//右上点
	glTexCoord2f(0.0,1.0);glVertex3fv((pos+(Z-X)* h).v);//左上点
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}

//////////////////////////////////////////////////////////////////////////
// 函数：BuildTexture()
// 参数：参数szPathName为要载入的文件名,texid为纹理变量
// 功能：载入纹理
//////////////////////////////////////////////////////////////////////////

int Plant::BuildTexture(char *szPathName, GLuint &texid)
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
	
	hdcTemp = CreateCompatibleDC(GetDC(0));                // Create The Windows Compatible Device Context
	if(!hdcTemp)                            // Did Creation Fail?
	{
		pPicture->Release();                      // Decrements IPicture Reference Count
		return FALSE;                          // Return False (Failure)
	}
	
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
	
	SelectObject(hdcTemp, hbmpTemp);                  // Select Handle To Our Temp DC And Our Temp Bitmap Object
	
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
	
	DeleteObject(hbmpTemp);                        // Delete The Object
	DeleteDC(hdcTemp);                          // Delete The Device Context
	
	pPicture->Release();                        // Decrements IPicture Reference Count
	
	return TRUE;                            // Return True (All Good)
	
}

//////////////////////////////////////////////////////////////////////////
// 函数：LoadTree()
// 参数：NULL
// 功能：载入相关纹理
//////////////////////////////////////////////////////////////////////////

void Plant::LoadPlant()
{
	//树
	BuildTexture("CACTUS1.BMP",m_treeTexture[0]);
	BuildTexture("CACTUS2.BMP",m_treeTexture[1]);
	BuildTexture("CACTUS3.BMP",m_treeTexture[2]);
	BuildTexture("CACTUS5.BMP",m_treeTexture[3]);
	BuildTexture("CACTUS0.BMP",m_treeTexture[4]);
	BuildTexture("tree2.bmp",m_treeTexture[5]);
	BuildTexture("tree001.BMP",m_treeTexture[6]);
	BuildTexture("tree002.BMP",m_treeTexture[7]);
	BuildTexture("tree003.BMP",m_treeTexture[8]);
	BuildTexture("tree005.BMP",m_treeTexture[9]);
	//草
	BuildTexture("草1.BMP",m_grassTexture[0]);
	BuildTexture("草2.BMP",m_grassTexture[1]);
	BuildTexture("草3.BMP",m_grassTexture[2]);
	BuildTexture("草4.BMP",m_grassTexture[3]);
	//花
	BuildTexture("flower1.BMP",m_grassTexture[4]);
	BuildTexture("flower2.BMP",m_grassTexture[5]);
}