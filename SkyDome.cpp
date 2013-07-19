// SkyDome.cpp: implementation of the SkyDome class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkyDome.h"
#include <math.h>
#include <mmsystem.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SkyDome::SkyDome()
{
    Vertices=new VERTEX_SKY;
}

SkyDome::~SkyDome()
{
	ReleaseDome(); 
}


void SkyDome::Init()
{
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

//	//添加雾的效果
//	GLfloat fogColor[4]={0.9f,0.9f,0.9f,0.6f};
//	glFogi(GL_FOG_MODE,GL_LINEAR);
//	glFogfv(GL_FOG_COLOR,fogColor);
//	glFogf(GL_FOG_DENSITY,0.002f);
//	glFogf(GL_FOG_START,100.0f);
//	glFogf(GL_FOG_END,800.0f);
//	glHint(GL_FOG_HINT,GL_FASTEST);
    
	


	GenerateDome(3000.0f,2.0f,2.0f,1.0f,1.0f);

	char	dir[256];	
	strcpy(dir,AppSettings::ProgramePath);
	strcat(dir,"/Image/");
	SetCurrentDirectory(dir);
	LoadTextures("clouds2.bmp",0);
	SetCurrentDirectory(AppSettings::ProgramePath);
}
void SkyDome::GenerateDome(float radius, float dtheta, float dphi, float hTile, float vTile)
{
    int theta, phi;

   // Make sure our vertex array is clear
   if (Vertices) 
   {
   delete Vertices;
   Vertices = NULL;
   NumVertices = 0;
}

// Initialize our Vertex array初始化顶点序列
   NumVertices = (int)((360/dtheta)*(90/dphi)*4);
   Vertices = new VERTEX_SKY[NumVertices];
   ZeroMemory(Vertices, sizeof(VERTEX_SKY)*NumVertices);


// Used to calculate the UV coordinates用来计算UV坐标
  float vx, vy, vz, mag;

//生成拱形天空dome
   int n = 0;
  for (phi=0; phi <= 90 - dphi; phi += (int)dphi)
  {
   for (theta=0; theta <= 360 - dtheta; theta += (int)dtheta)
   {
    
	// Calculate the vertex at phi, theta计算顶点的phi,theta
    Vertices[n].x = radius * sinf(phi*DTOR) * cosf(DTOR*theta);
    Vertices[n].y = radius * sinf(phi*DTOR) * sinf(DTOR*theta);
    Vertices[n].z = radius * cosf(phi*DTOR);    // Create a vector from the origin to this vertex
   
	
	//计算从原点到该顶点的矢量
	vx = Vertices[n].x;
    vy = Vertices[n].y;
    vz = Vertices[n].z;   
	
	// Normalize the vector矢量正交化
    mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
    vx /= mag;
    vy /= mag;
    vz /= mag;  
	
	// Calculate the spherical texture coordinates计算球形纹理坐标
    Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
    Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;  
    n++;   
	
	// Calculate the vertex at phi+dphi, theta计算位置在phi+dphi,theta的顶点
    Vertices[n].x = radius * sinf((phi+dphi)*DTOR) * cosf(theta*DTOR);
    Vertices[n].y = radius * sinf((phi+dphi)*DTOR) * sinf(theta*DTOR);
    Vertices[n].z = radius * cosf((phi+dphi)*DTOR);
   
    // Calculate the texture coordinates计算纹理坐标
    vx = Vertices[n].x;
    vy = Vertices[n].y;
    vz = Vertices[n].z;   
	
	mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
    vx /= mag;
    vy /= mag;
    vz /= mag;    
	
	Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
    Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;  
    n++;    
	
	// Calculate the vertex at phi, theta+dtheta计算位于phi,theta+dtheta处的顶点坐标
    Vertices[n].x = radius * sinf(DTOR*phi) * cosf(DTOR*(theta+dtheta));
    Vertices[n].y = radius * sinf(DTOR*phi) * sinf(DTOR*(theta+dtheta));
    Vertices[n].z = radius * cosf(DTOR*phi);
   
    // Calculate the texture coordinates计算纹理坐标
    vx = Vertices[n].x;
    vy = Vertices[n].y;
    vz = Vertices[n].z;    
	
	
	mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
    vx /= mag;
    vy /= mag;
    vz /= mag;   
	Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
    Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;  
    n++;    
	
	if (phi > -90 && phi < 90)
    {
     // Calculate the vertex at phi+dphi, theta+dtheta计算位于phi+dphi, theta+dtheta处的顶点坐标
     Vertices[n].x = radius * sinf((phi+dphi)*DTOR) * cosf(DTOR*(theta+dtheta));
     Vertices[n].y = radius * sinf((phi+dphi)*DTOR) * sinf(DTOR*(theta+dtheta));
     Vertices[n].z = radius * cosf((phi+dphi)*DTOR);
    
     // Calculate the texture coordinates计算纹理坐标
     vx = Vertices[n].x;
     vy = Vertices[n].y;
     vz = Vertices[n].z;     
	 
	 mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
     vx /= mag;
     vy /= mag;
     vz /= mag;     
	 
	 Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
     Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;  
     n++;
    }
   }
}

/*//得到最低点
float minZ = Vertices[0].z;
for(int j=1;j<NumVertices;j++)
{
   Vertices[j].flag = 0;
   if(Vertices[j].z < minZ)    minZ = Vertices[j].z;
}
mY = minZ;
for(j=0;j<NumVertices;j++)
{
   if(Vertices[j].z == minZ)   Vertices[j].flag=1;
}
*/
// Fix the problem at the seam修改纹理坐标
for (int i=0; i < NumVertices-3; i++)
{
   if (Vertices[i].u - Vertices[i+1].u > 0.9f)
          Vertices[i+1].u += 1.0f;  
   if (Vertices[i+1].u - Vertices[i].u > 0.9f)
          Vertices[i].u += 1.0f;  
   if (Vertices[i].u - Vertices[i+2].u > 0.9f)
          Vertices[i+2].u += 1.0f;  
   if (Vertices[i+2].u - Vertices[i].u > 0.9f)
          Vertices[i].u += 1.0f;  
   if (Vertices[i+1].u - Vertices[i+2].u > 0.9f)
          Vertices[i+2].u += 1.0f;   
   if (Vertices[i+2].u - Vertices[i+1].u > 0.9f)
          Vertices[i+1].u += 1.0f;   
   if (Vertices[i].v - Vertices[i+1].v > 0.8f)
          Vertices[i+1].v += 1.0f;   
   if (Vertices[i+1].v - Vertices[i].v > 0.8f)
          Vertices[i].v += 1.0f;  
   if (Vertices[i].v - Vertices[i+2].v > 0.8f)
          Vertices[i+2].v += 1.0f;  
   if (Vertices[i+2].v - Vertices[i].v > 0.8f)
          Vertices[i].v += 1.0f;   
   if (Vertices[i+1].v - Vertices[i+2].v > 0.8f)
          Vertices[i+2].v += 1.0f;  
   if (Vertices[i+2].v - Vertices[i+1].v > 0.8f)
          Vertices[i+1].v += 1.0f;
}
}

int SkyDome::RenderSkyDome()
{
  
	float x=AppSettings::p_Position->x;
	float z=AppSettings::p_Position->z;
	glPushMatrix();
   
	glTranslatef(x, -10.0f, z);
 
	//glTranslatef(x, y-100, z);
   
	glRotatef(timeGetTime()/2000.0f,0.0f, 1.0f, 0.0f);
   glRotatef(270, 1.0f, 0.0f, 0.0f);

 //glColor4f(1,1,1,1);


   glBegin(GL_TRIANGLE_STRIP);

 //glBegin(GL_LINE_STRIP);
   for (int i=0; i < NumVertices; i++)
   {
   /*if(Vertices[i].flag==1) //最后一圈顶点
    //glColor3f(0.9f,0.9f,1.0f);
    glColor3f(0.95f,0.95f,1.0f);
   else*/
    //glColor3f(0.5f, 0.7f, 0.8f);
      glColor3f(1.0f, 1.0f, 1.0f);  
  
      glTexCoord2f(Vertices[i].u, Vertices[i].v);
      glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
   }

   glEnd();

/*闭合底部
glColor3f(0.9f,0.9f,1.0f);
glBegin(GL_POLYGON);
for(i=0;i<NumVertices;i++)
{
   if(Vertices[i].flag == 1)
   {
    glTexCoord2f(Vertices[i].u, Vertices[i].v);
    glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
   }
}
glEnd();*/

   glPopMatrix();
   return 1;
}

void SkyDome::ReleaseDome()
{
   if (Vertices)
   {
	   delete Vertices;
       Vertices = NULL;
   }
}

int SkyDome::LoadTextures(char*filename,int id)
{
    int Status=false;									// Status Indicator
    AUX_RGBImageRec *TextureImage=NULL;					// Create Storage Space For The Textures
    //memset(TextureImage,0,sizeof(void *)*6);			// Set The Pointer To NULL

	ZeroMemory(&TextureImage,sizeof(void *)*1);
    if (TextureImage=LoadBMP(filename))	
	{   
		Status=true;									// Set The Status To TRUE
		glGenTextures(1, &texture[id]);					// Create The Texture
		glBindTexture(GL_TEXTURE_2D, texture[id]);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	
	if(TextureImage)				// If Texture Exists
	{
		if (TextureImage->data)			// If Texture Image Exists
		   free(TextureImage->data);		// Free The Texture Image Memory
		
		free(TextureImage);				// Free The Image Structure 
	}
	
	return Status;										// Return The Status
}
AUX_RGBImageRec* SkyDome::LoadBMP(char*filename)
{
		FILE *File=NULL;									// File Handle

	if (!filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;			
}