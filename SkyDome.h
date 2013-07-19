// SkyDome.h: interface for the SkyDome class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKYDOME_H__0CC0C7A0_AF8B_4E48_9AEF_9CA07DF49C9B__INCLUDED_)
#define AFX_SKYDOME_H__0CC0C7A0_AF8B_4E48_9AEF_9CA07DF49C9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define PI 3.1415926535897f
#define DTOR (PI/180.0f)
#define SQR(x) (x*x)


typedef struct
{
	float x,y,z;
	unsigned int color;
	float u,v;
}VERTEX_SKY;

class SkyDome  
{
public:
	SkyDome();
	virtual ~SkyDome();

	void Init();
	void GenerateDome(float radius, float dtheta, float dphi, float hTile, float vTile);
	int  RenderSkyDome();
	void ReleaseDome();
	
	int LoadTextures(char*filename,int id);
	AUX_RGBImageRec*LoadBMP(char*filename);
    



protected:
	
private:
	GLuint texture[2];
	VERTEX_SKY*Vertices;
	int NumVertices;
};


#endif // !defined(AFX_SKYDOME_H__0CC0C7A0_AF8B_4E48_9AEF_9CA07DF49C9B__INCLUDED_)
