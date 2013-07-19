// Scene.cpp: implementation of the Scene class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Scene.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Scene::Scene()
{
	m_nLists=0;
	m_nModels=0;

	m_nTrees=0;	
	m_nGrasses=0;
}

Scene::~Scene()
{

}

void Scene ::Load()
{
		CLoad3DS l;
	l.BuildTexture("grass.BMP",m_groundTexture);	
	l.BuildTexture("water.bmp",m_textureRiver);
	l.BuildTexture("lake.bmp",m_textureLake);
	l.BuildTexture("护栏.bmp",m_textureBoundary);
	l.BuildTexture("桥.bmp",m_textureBridge);
	l.BuildTexture("rail.bmp",m_textureFence);
	l.BuildTexture("xiangyun.bmp",m_textureWall[0]);
	l.BuildTexture("金色.jpg",m_textureWall[1]);
	l.BuildTexture("红色.jpg",m_textureWall[2]);
	l.BuildTexture("祥云.bmp",m_textureWall[3]);
	l.BuildTexture("xiang.bmp",m_textureWall[4]);
	//载入植物
	m_Plant.LoadPlant();
	ReadPlant();
	//载入场景
	AddModel("Model/Scene/有颜色的长方体.3DS");	//0
	AddModel("Model/Scene/有色屋顶.3DS");	//1
	AddModel("Model/Scene/双贴图.3DS");	//2
	AddModel("Model/Scene/中心长方体.3DS");	//3
	AddModel("Model/Scene/无心圆柱体.3DS");	//4
	AddModel("Model/Scene/小城堡.3DS");	//5
	AddModel("Model/Scene/grassland.3DS");	//6
	//载入动态模型
	AddModel("Model/Object/cone.3DS");//7
	AddModel("Model/Object/cuboid.3DS");//8
	AddModel("Model/Object/cylinder.3DS");  //9
	AddModel("Model/Object/spheroid.3DS");//10

	m_modelLoader.Clear();

	//模型信息初始化
	//颜色长方体
	m_models[0].listIndex=m_listIndex[0];
	m_models[0].position.Init(0.0f,0.0f,6.0f);
	m_models[0].size.Init(1.0f,1.0f,1.0f);
	m_models[0].yrot=0.0f;
	m_models[0].scale=0.001f;
    //屋顶
	m_models[1].listIndex=m_listIndex[1];
	m_models[1].position.Init(-15.0f,0.0f,0.0f);
	m_models[1].size.Init(1.0f,1.0f,1.0f);
	m_models[1].yrot=0.0f;
	m_models[1].scale=0.001f;
    //双贴图
	m_models[2].listIndex=m_listIndex[2];
	m_models[2].position.Init(0.0f,0.0f,-6.0f);
	m_models[2].size.Init(1.0f,1.0f,1.0f);
	m_models[2].yrot=0.0f;
	m_models[2].scale=0.001f;

	//中心长方体
	m_models[3].listIndex=m_listIndex[3];
	m_models[3].position.Init(0.0f,0.0f,-4.0f);
	m_models[3].size.Init(1.0f,1.0f,1.0f);
	m_models[3].yrot=0.0f;
	m_models[3].scale=0.001f;
    //无心圆柱体
	m_models[4].listIndex=m_listIndex[4];
	m_models[4].position.Init(0.0f,0.0f,-3.0f);
	m_models[4].size.Init(1.0f,1.0f,1.0f);
	m_models[4].yrot=0.0f;
	m_models[4].scale=0.001f;
    //小城堡
	m_models[5].listIndex=m_listIndex[5];
	m_models[5].position.Init(0.0f,6.0f,-40.0f);
	m_models[5].size.Init(1.0f,1.0f,1.0f);
	m_models[5].yrot=0.0f;
	m_models[5].scale=0.001f;
    //地面
	m_models[6].listIndex=m_listIndex[6];
	m_models[6].position.Init(0.0f,0.0f,0.0f);
	m_models[6].size.Init(1.0f,1.0f,1.0f);
	m_models[6].yrot=0.0f;
	m_models[6].scale=0.001f;

	m_models[7].listIndex=m_listIndex[7];
	m_models[7].position.Init(4.0f,0.0f,0.0f);
	m_models[7].size.Init(0.5f,0.5f,0.8f);
	m_models[7].yrot=0.0f;
	m_models[7].scale=0.001f;

	m_models[8].listIndex=m_listIndex[8];
	m_models[8].position.Init(6.0f,0.0f,2.0f);
	m_models[8].size.Init(0.8f,0.7f,0.4f);
	m_models[8].yrot=0.0f;
	m_models[8].scale=0.001f;

	m_models[9].listIndex=m_listIndex[9];
	m_models[9].position.Init(8.0f,0.0f,0.0f);
	m_models[9].size.Init(0.6f,0.6f,0.8f);
	m_models[9].yrot=0.0f;
	m_models[9].scale=0.001f;

	m_models[10].listIndex=m_listIndex[10];
	m_models[10].position.Init(10.0f,0.0f,0.0f);
	m_models[10].size.Init(0.7f,0.7f,0.7f);
	m_models[10].yrot=0.0f;
	m_models[10].scale=0.001f;

	m_nModels=11;

}

void Scene::Render()
{
//	glPushMatrix();
//	glColor3f(255.0f,0.0f,255.0f);
//	glLineWidth(2);
//	glTranslatef ( 0, 0,0);
//	glBegin(GL_LINE_LOOP);///////////////////Y
//	glVertex3f(0.0f,-10.0f,0.0f);
//	glVertex3f(0.0f,10.0f,0.0f);
//	//glVertex3f(10.0f,0.0f,0.0f);
//	glEnd();
//	glLineWidth(1);
//	glBegin(GL_LINE_LOOP);////////////////////X
//	glVertex3f(-10.0f,0.0f,0.0f);
//	glVertex3f(10.0f,0.0f,0.0f);
//	//glVertex3f(10.0f,0.0f,0.0f);
//	glEnd();
//	glLineWidth(4);
//	glBegin(GL_LINE_LOOP);///////////////////Z
//	glVertex3f(0.0f,0.0f,-10.0f);
//	glVertex3f(0.0f,0.0f,10.0f);
//	//glVertex3f(10.0f,0.0f,0.0f);
//	glEnd();
//	glPopMatrix();
	
	//显示所有模型
	glPushMatrix();
	for(int i=0;i<m_nModels;i++)
	{
		glPushMatrix();
		glTranslatef(m_models[i].position.x,m_models[i].position.y,m_models[i].position.z);
		glRotatef(m_models[i].yrot,0,1,0);
		glScalef(m_models[i].scale,m_models[i].scale,m_models[i].scale);
		glCallList(m_models[i].listIndex);
		glPopMatrix();
	}
	glPopMatrix();
	
	glPushMatrix();
	RenderPlant();
	glPopMatrix();

	glPushMatrix();
	//new River
	RenderRiver();
	glPopMatrix();

	glPushMatrix();
	RenderBridge();
	glPopMatrix();

	glPushMatrix();
	RenderRoadBridge();
	glPopMatrix();

	glPushMatrix();
	//DrawLake();
	glPopMatrix();
}


//////////////////////////////////////////////////////////////////////////
// 函数：AddModel()
// 参数：modelfile为所要添加的3DS文件名
// 功能：添加3D模型
//////////////////////////////////////////////////////////////////////////
bool Scene::AddModel(char *modelfile)
{
	m_modelLoader.Clear();
	if(!m_modelLoader.Import3DS(modelfile))
		return false;
	m_listIndex[m_nLists]=glGenLists(1);
	glNewList(m_listIndex[m_nLists],GL_COMPILE);

	glPushMatrix();
	m_modelLoader.DrawModel();
	glPopMatrix();
	glEndList();
	m_nLists++;
	return true;
}


void Scene::RenderPlant()
{
	int i;
	for(i=0;i<m_nGrasses;i++)
		m_Plant.DrawPlant(m_grassData[i].x,m_grassData[i].y,m_grassData[i].z
		,m_grassData[i].size,0,m_grassData[i].text,false);

	for(i=0;i<m_nTrees;i++)
		m_Plant.DrawPlant(m_treeData[i].x,m_treeData[i].y,m_treeData[i].z
		,m_treeData[i].size,m_treeData[i].h,m_treeData[i].text);

}

void Scene::RenderRiver()
{
	DrawRiver(4580,2400,4620,2380,4280,1850,4240,1850);//r1
	DrawRiver(4240,1850,4280,1850,4100,1625,4060,1625);
	DrawRiver(4060,1625,4100,1625,3920,1380,3920,1420);	
	DrawRiver(3920,1380,3920,1420,3830,1300,3870,1300);//r2	
	DrawRiver(3850,1320,3850,1280,3725,1210,3685,1210);//r3
	DrawRiver(3685,1210,3725,1210,3645,1150,3605,1150);
	DrawRiver(3605,1150,3645,1150,3420,1000,3380,1000);
	DrawRiver(3380,1000,3420,1000,3000,680,3000,720);
	DrawRiver(3000,720,3000,680,2880,580,2840,580);//r4
	DrawRiver(2840,580,2880,580,2770,350,2730,350);
	DrawRiver(2730,350,2770,350,2630,150,2590,150);
	DrawRiver(2590,150,2630,150,2520,0,2480,0);
	DrawRiver(2500,20,2500,-20,2000,-80,2000,-40);//r5
	DrawRiver(2000,-40,2000,-80,1860,-210,1820,-210);//r6
	DrawRiver(1820,-210,1860,-210,1520,-540,1480,-540);
	DrawRiver(1480,-540,1520,-540,1000,-1040,1000,-1000);
	
	DrawRiver(1000,-1000,1000,-1040,860,-1190,820,-1190);
	DrawRiver(820,-1190,860,-1190,570,-1460,530,-1460);
	DrawRiver(530,-1460,570,-1460,395,-1580,355,-1580);
	DrawRiver(355,-1580,395,-1580,220,-1700,180,-1700);
	DrawRiver(180,-1700,220,-1700,180,-1800,140,-1800);
	DrawRiver(140,-1800,180,-1800,120,-1940,100,-1910);	
}


//////////////////////////////////////////////////////////////////////////
// 函数：readstr()
// 参数：f为文件输入指针，string为存储输入的缓冲区
// 功能：读入一行字符，结果保存在缓冲区
//////////////////////////////////////////////////////////////////////////
bool readstr(FILE *f,char *string)
{
	do
	{
		if(!fgets(string, 255, f))return false;
	} while ((string[0] == '/') || (string[0] == '\n'));
	return true;
}


bool Scene::ReadPlant()
{
	FILE *in;
	bool check;
	char oneline[255];
	int s;
	in = fopen("tree.txt", "rt");				// File To Load World Data From
	check=readstr(in,oneline);
	if(!check)return false;
	while(1)
	{
		if(check)
		{
			sscanf(oneline,"%d %d %d %d %d %d\n",
				&(m_treeData[m_nTrees]).x,&(m_treeData[m_nTrees]).y,&(m_treeData[m_nTrees]).z,
				&s,&m_treeData[m_nTrees].h,&m_treeData[m_nTrees].text);/**/
			if(s>20)(m_treeData[m_nTrees].size)=s*(1+(rand()%20-40)/100.0);
			else m_treeData[m_nTrees].size=s;
			m_nTrees++;
		}
		else break;
		check=readstr(in,oneline);
	}
	fclose(in);

	in = fopen("grass.txt", "rt");				// File To Load World Data From
	check=readstr(in,oneline);
	if(!check)return false;
	while(1)
	{
		if(check)
		{
			sscanf(oneline,"%d %d %d %f %d\n",
				&(m_grassData[m_nGrasses]).x,&(m_grassData[m_nGrasses]).y,&(m_grassData[m_nGrasses]).z,
				&m_grassData[m_nGrasses].size,&m_grassData[m_nGrasses].text);/**/
			m_nGrasses++;
		}
		else break;
		check=readstr(in,oneline);
	}
	fclose(in);
	return true;
}


//////////////////////////////////////////////////////////////////////////
// 函数：DrawRiver()
// 参数：见功能
// 功能：绘制以(x1,z1)、(x2,z2)、(x3,z3)、(x4,z4)为顶点的河面
//////////////////////////////////////////////////////////////////////////
void Scene::DrawRiver(float x1,float z1,float x2,float z2,
			   float x3,float z3,float x4,float z4)
{
	float y=0.2f;
	glPushMatrix();
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D,m_textureRiver);
	glEnable(GL_TEXTURE_2D);
	glColor4ub(91,191,240,200);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(x1,y,z1);
	glTexCoord2f(5.0f, 0.0f);glVertex3f(x2,y,z2);
	glTexCoord2f(5.0f,20.0f);glVertex3f(x3,y,z3);
	glTexCoord2f(0.0f, 20.0f);glVertex3f(x4,y,z4);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


//////////////////////////////////////////////////////////////////////////
// 函数：DrawBridge()
// 参数：NULL
// 功能：绘制桥及其扶手
//////////////////////////////////////////////////////////////////////////
void Scene::RenderBridge()
{
	float y=4.0;
	float w=2.0;
	float h=2.0;
	float rail=2.0;
	float inc=20;

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
	//边缘
	glBindTexture(GL_TEXTURE_2D,m_textureBoundary);
	glBegin(GL_QUADS);
	//路1
	glTexCoord2f(0.0f,0.0f);glVertex3f(3854,0,720);//上
	glTexCoord2f(1.0f,0.0f);glVertex3f(3854,0,720+w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(4755,0,720+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(4755,0,720);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3854,0,680);//下
	glTexCoord2f(1.0f,0.0f);glVertex3f(3854,0,680-w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(4755,0,680-w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(4755,0,680);
	//路2
	glTexCoord2f(0.0f,0.0f);glVertex3f(3960,0,1320);//上
	glTexCoord2f(1.0f,0.0f);glVertex3f(3960,0,1320+w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(4960,0,1320+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(4960,0,1320);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3948,0,1280);//下
	glTexCoord2f(1.0f,0.0f);glVertex3f(3948,0,1280-w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(4855,0,1280-w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(4855,0,1280);
	glEnd();
	//护栏
	glBindTexture(GL_TEXTURE_2D,m_textureFence);
	glBegin(GL_QUADS);
	//路1
	glTexCoord2f(0.0f,0.0f);glVertex3f(3824,y,720);//上
	glTexCoord2f(1.0f,0.0f);glVertex3f(3824,y+h,720+w);
	glTexCoord2f(1.0f,10.0f);glVertex3f(4795,y+h,720+w);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4795,y,720);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3824,y,680);//下
	glTexCoord2f(1.0f,0.0f);glVertex3f(3824,y+h,680-w);
	glTexCoord2f(1.0f,10.0f);glVertex3f(4795,y+h,680-w);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4795,y,680);
	//路2
	glTexCoord2f(0.0f,0.0f);glVertex3f(3920,y,1320);//上
	glTexCoord2f(1.0f,0.0f);glVertex3f(3920,y+h,1320+w);
	glTexCoord2f(1.0f,12.0f);glVertex3f(4990,y+h,1320+w);
	glTexCoord2f(0.0f,12.0f);glVertex3f(4990,y,1320);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3918,y,1280);//下
	glTexCoord2f(1.0f,0.0f);glVertex3f(3918,y+h,1280-w);
	glTexCoord2f(1.0f,11.0f);glVertex3f(4895,y+h,1280-w);
	glTexCoord2f(0.0f,11.0f);glVertex3f(4895,y,1280);

	glEnd();
	//桥
	glBindTexture(GL_TEXTURE_2D,m_textureBridge);
	glBegin(GL_QUADS);
	//扶手支持
	//路1 上
	glTexCoord2f(0.0f,0.0f);glVertex3f(3824,0,720);//开始
	glTexCoord2f(1.0f,0.0f);glVertex3f(3824,0,720+w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(3824,y+h,720+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(3824,y,720);

	for(int i=0;i<(4795-3824)/inc;i++)
	{
		glTexCoord2f(0.0f,0.0f);glVertex3f(3824+i*inc,0,720);
		glTexCoord2f(1.0f,0.0f);glVertex3f(3824+rail+i*inc,0,720);
		glTexCoord2f(1.0f,1.0f);glVertex3f(3824+rail+i*inc,y,720);
		glTexCoord2f(0.0f,1.0f);glVertex3f(3824+i*inc,y,720);
	}
	
	glTexCoord2f(0.0f,0.0f);glVertex3f(4795,0,720);//结束
	glTexCoord2f(1.0f,0.0f);glVertex3f(4795,0,720+w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(4795,y+h,720+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(4795,y,720);
	//路1 下
	glTexCoord2f(0.0f,0.0f);glVertex3f(3824,0,680);//开始
	glTexCoord2f(1.0f,0.0f);glVertex3f(3824,0,680-w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(3824,y+h,680-w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(3824,y,680);

	for(i=0;i<(4795-3824)/inc;i++)
	{
		glTexCoord2f(0.0f,0.0f);glVertex3f(3824+i*inc,0,680);
		glTexCoord2f(1.0f,0.0f);glVertex3f(3824+rail+i*inc,0,680);
		glTexCoord2f(1.0f,1.0f);glVertex3f(3824+rail+i*inc,y,680);
		glTexCoord2f(0.0f,1.0f);glVertex3f(3824+i*inc,y,680);
	}
	
	glTexCoord2f(0.0f,0.0f);glVertex3f(4795,0,680);//结束
	glTexCoord2f(1.0f,0.0f);glVertex3f(4795,0,680-w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(4795,y+h,680-w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(4795,y,680);
	//路2 上
	glTexCoord2f(0.0f,0.0f);glVertex3f(3920,0,1320);//开始
	glTexCoord2f(1.0f,0.0f);glVertex3f(3920,0,1320+w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(3920,y+h,1320+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(3920,y,1320);

	for(i=0;i<(4990-3920)/inc;i++)
	{
		glTexCoord2f(0.0f,0.0f);glVertex3f(3920+i*inc,0,1320);
		glTexCoord2f(1.0f,0.0f);glVertex3f(3920+rail+i*inc,0,1320);
		glTexCoord2f(1.0f,1.0f);glVertex3f(3920+rail+i*inc,y,1320);
		glTexCoord2f(0.0f,1.0f);glVertex3f(3920+i*inc,y,1320);
	}
	
	glTexCoord2f(0.0f,0.0f);glVertex3f(4990,0,1320);//结束
	glTexCoord2f(1.0f,0.0f);glVertex3f(4990,0,1320+w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(4990,y+h,1320+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(4990,y,1320);
	//路2 下
	glTexCoord2f(0.0f,0.0f);glVertex3f(3918,0,1280);//开始
	glTexCoord2f(1.0f,0.0f);glVertex3f(3918,0,1280-w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(3918,y+h,1280-w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(3918,y,1280);

	for(i=0;i<(4895-3918)/inc;i++)
	{
		glTexCoord2f(0.0f,0.0f);glVertex3f(3918+i*inc,0,1280);
		glTexCoord2f(1.0f,0.0f);glVertex3f(3918+rail+i*inc,0,1280);
		glTexCoord2f(1.0f,1.0f);glVertex3f(3918+rail+i*inc,y,1280);
		glTexCoord2f(0.0f,1.0f);glVertex3f(3918+i*inc,y,1280);
	}
	
	glTexCoord2f(0.0f,0.0f);glVertex3f(4895,0,1280);//结束
	glTexCoord2f(1.0f,0.0f);glVertex3f(4895,0,1280-w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(4895,y+h,1280-w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(4895,y,1280);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////
// 函数：DrawRoadBridge()
// 参数：NULL
// 功能：绘制路边的桥
//////////////////////////////////////////////////////////////////////////
void Scene::RenderRoadBridge()
{
	float y=2.0;
	float w=2.0f;
	float yl=0.2f;
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,m_textureFence);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f,0.0f);glVertex3f(2990,yl,720);//700 上
	glTexCoord2f(1.0f,0.0f);glVertex3f(2990,y,720+w);
	glTexCoord2f(1.0f,5.0f);glVertex3f(3060,y,720+w);
	glTexCoord2f(0.0f,5.0f);glVertex3f(3060,yl,720);
	glTexCoord2f(0.0f,0.0f);glVertex3f(2990,yl,720+2*w);//700 上
	glTexCoord2f(1.0f,0.0f);glVertex3f(2990,y,720+w);
	glTexCoord2f(1.0f,5.0f);glVertex3f(3060,y,720+w);
	glTexCoord2f(0.0f,5.0f);glVertex3f(3060,yl,720+2*w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(2940,yl,680);//700 下
	glTexCoord2f(1.0f,0.0f);glVertex3f(2940,y,680-w);
	glTexCoord2f(1.0f,5.0f);glVertex3f(3010,y,680-w);
	glTexCoord2f(0.0f,5.0f);glVertex3f(3010,yl,680);
	glTexCoord2f(0.0f,0.0f);glVertex3f(2940,yl,680-2*w);//700 下
	glTexCoord2f(1.0f,0.0f);glVertex3f(2940,y,680-w);
	glTexCoord2f(1.0f,5.0f);glVertex3f(3010,y,680-w);
	glTexCoord2f(0.0f,5.0f);glVertex3f(3010,yl,680-2*w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(2480,yl,20);//0 上
	glTexCoord2f(1.0f,0.0f);glVertex3f(2480,y,20+w);
	glTexCoord2f(1.0f,5.0f);glVertex3f(2550,y,20+w);
	glTexCoord2f(0.0f,5.0f);glVertex3f(2550,yl,20);
	glTexCoord2f(0.0f,0.0f);glVertex3f(2480,yl,20+2*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(2480,y,20+w);
	glTexCoord2f(1.0f,5.0f);glVertex3f(2550,y,20+w);
	glTexCoord2f(0.0f,5.0f);glVertex3f(2550,yl,20+2*w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(2130,yl,-20);//0 下
	glTexCoord2f(1.0f,0.0f);glVertex3f(2130,y,-20-w);
	glTexCoord2f(1.0f,15.0f);glVertex3f(2485,y,-20-w);
	glTexCoord2f(0.0f,15.0f);glVertex3f(2485,yl,-20);
	glTexCoord2f(0.0f,0.0f);glVertex3f(2130,yl,-20-2*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(2130,y,-20-w);
	glTexCoord2f(1.0f,15.0f);glVertex3f(2485,y,-20-w);
	glTexCoord2f(0.0f,15.0f);glVertex3f(2485,yl,-20-2*w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(2020,yl,-30);//0 右
	glTexCoord2f(1.0f,0.0f);glVertex3f(2020+w,y,-30);
	glTexCoord2f(1.0f,5.0f);glVertex3f(2020+w,y,-80);
	glTexCoord2f(0.0f,5.0f);glVertex3f(2020,yl,-80);
	glTexCoord2f(0.0f,0.0f);glVertex3f(2020+2*w,yl,-30);
	glTexCoord2f(1.0f,0.0f);glVertex3f(2020+w,y,-30);
	glTexCoord2f(1.0f,5.0f);glVertex3f(2020+w,y,-80);
	glTexCoord2f(0.0f,5.0f);glVertex3f(2020+2*w,yl,-80);

	glTexCoord2f(0.0f,0.0f);glVertex3f(1980,yl,-50);//0 左
	glTexCoord2f(1.0f,0.0f);glVertex3f(1980-w,y,-50);
	glTexCoord2f(1.0f,5.0f);glVertex3f(1980-w,y,-110);
	glTexCoord2f(0.0f,5.0f);glVertex3f(1980,yl,-110);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1980-2*w,yl,-50);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1980-w,y,-50);
	glTexCoord2f(1.0f,5.0f);glVertex3f(1980-w,y,-110);
	glTexCoord2f(0.0f,5.0f);glVertex3f(1980-2*w,yl,-110);

	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,yl,-985);//-1000 右
	glTexCoord2f(2.0f,0.0f);glVertex3f(1020,2*y,-985+w);
	glTexCoord2f(2.0f,3.0f);glVertex3f(1060,2*y,-985+w);
	glTexCoord2f(0.0f,3.0f);glVertex3f(1060,yl,-985);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,yl,-985+2*w);
	glTexCoord2f(2.0f,0.0f);glVertex3f(1020,2*y,-985+w);
	glTexCoord2f(2.0f,5.0f);glVertex3f(1060,2*y,-985+w);
	glTexCoord2f(0.0f,5.0f);glVertex3f(1060,yl,-985+2*w);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,yl,-985);//开口
	glTexCoord2f(2.0f,0.0f);glVertex3f(1020,yl,-985+2*w);
	glTexCoord2f(2.0f,1.0f);glVertex3f(1020,2*y,-985+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(1020,2*y,-985+w);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1060,yl,-985);
	glTexCoord2f(2.0f,0.0f);glVertex3f(1060,yl,-985+2*w);
	glTexCoord2f(2.0f,1.0f);glVertex3f(1060,2*y,-985+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(1060,2*y,-985+w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(980,yl,-1010);//-1000 左
	glTexCoord2f(2.0f,0.0f);glVertex3f(980-w,2*y,-1010);
	glTexCoord2f(2.0f,5.0f);glVertex3f(980-w,2*y,-1080);
	glTexCoord2f(0.0f,5.0f);glVertex3f(980,yl,-1080);
	glTexCoord2f(0.0f,0.0f);glVertex3f(980-2*w,yl,-1010);
	glTexCoord2f(2.0f,0.0f);glVertex3f(980-w,2*y,-1010);
	glTexCoord2f(2.0f,5.0f);glVertex3f(980-w,2*y,-1080);
	glTexCoord2f(0.0f,5.0f);glVertex3f(980-2*w,yl,-1080);
	glTexCoord2f(0.0f,0.0f);glVertex3f(980-2*w,yl,-1010);//开口
	glTexCoord2f(2.0f,0.0f);glVertex3f(980,yl,-1010);
	glTexCoord2f(2.0f,1.0f);glVertex3f(980-w,2*y,-1010);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-w,2*y,-1010);
	glTexCoord2f(0.0f,0.0f);glVertex3f(980-2*w,yl,-1080);
	glTexCoord2f(2.0f,0.0f);glVertex3f(980,yl,-1080);
	glTexCoord2f(2.0f,1.0f);glVertex3f(980-w,2*y,-1080);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-w,2*y,-1080);

	glEnd();
	//底
	glBindTexture(GL_TEXTURE_2D,m_textureBoundary);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);glVertex3f(2990,yl,720);//700 上
	glTexCoord2f(1.0f,0.0f);glVertex3f(2990,yl,720+2*w);
	glTexCoord2f(1.0f,5.0f);glVertex3f(3060,yl,720+2*w);
	glTexCoord2f(0.0f,5.0f);glVertex3f(3060,yl,720);
	glTexCoord2f(0.0f,0.0f);glVertex3f(2940,yl,680-2*w);//700 下
	glTexCoord2f(1.0f,0.0f);glVertex3f(2940,yl,680);
	glTexCoord2f(1.0f,5.0f);glVertex3f(3010,yl,680);
	glTexCoord2f(0.0f,5.0f);glVertex3f(3010,yl,680-2*w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(2480,yl,20+2*w);//0 上
	glTexCoord2f(1.0f,0.0f);glVertex3f(2480,yl,20);
	glTexCoord2f(1.0f,5.0f);glVertex3f(2550,yl,20);
	glTexCoord2f(0.0f,5.0f);glVertex3f(2550,yl,20+2*w);
	glTexCoord2f(0.0f,0.0f);glVertex3f(2130,yl,-20-2*w);//0 下
	glTexCoord2f(1.0f,0.0f);glVertex3f(2130,yl,-20);
	glTexCoord2f(1.0f,15.0f);glVertex3f(2485,yl,-20);
	glTexCoord2f(0.0f,15.0f);glVertex3f(2485,yl,-20-2*w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(2020+2*w,yl,-30);//0 右
	glTexCoord2f(1.0f,0.0f);glVertex3f(2020,yl,-30);
	glTexCoord2f(1.0f,5.0f);glVertex3f(2020,yl,-80);
	glTexCoord2f(0.0f,5.0f);glVertex3f(2020+2*w,yl,-80);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1980-2*w,yl,-50);//0 左
	glTexCoord2f(1.0f,0.0f);glVertex3f(1980,yl,-50);
	glTexCoord2f(1.0f,5.0f);glVertex3f(1980,yl,-110);
	glTexCoord2f(0.0f,5.0f);glVertex3f(1980-2*w,yl,-110);

	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,yl,-985+2*w);//-1000 右
	glTexCoord2f(1.0f,0.0f);glVertex3f(1020,yl,-985);
	glTexCoord2f(1.0f,5.0f);glVertex3f(1060,yl,-985);
	glTexCoord2f(0.0f,5.0f);glVertex3f(1060,yl,-985+2*w);
	glTexCoord2f(0.0f,0.0f);glVertex3f(980-2*w,yl,-1010);//-1000 左
	glTexCoord2f(1.0f,0.0f);glVertex3f(980,yl,-1010);
	glTexCoord2f(1.0f,5.0f);glVertex3f(980,yl,-1080);
	glTexCoord2f(0.0f,5.0f);glVertex3f(980-2*w,yl,-1080);
	glEnd();

	//特殊体
	glBindTexture(GL_TEXTURE_2D,m_textureWall[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,2*y,-985+2*w);//-1000 右
	glTexCoord2f(1.0f,0.0f);glVertex3f(1020,2*y,-985+w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(1060,2*y,-985+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(1060,2*y,-985+2*w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,2*y,-985+2*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1020,2*y,-985+w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(1020,50*y,-985-3*w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(1020,50*y,-985+5*w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(1060,2*y,-985+2*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1060,2*y,-985+w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(1060,50*y,-985-3*w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(1060,50*y,-985+5*w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(980-2*w,2*y,-1010);//-1000 左
	glTexCoord2f(1.0f,0.0f);glVertex3f(980-w,2*y,-1010);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980-w,2*y,-1080);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-2*w,2*y,-1080);

	glTexCoord2f(0.0f,0.0f);glVertex3f(980-w,2*y,-1010);
	glTexCoord2f(1.0f,0.0f);glVertex3f(980+3*w,50*y,-1010);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980-6*w,50*y,-1010);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-2*w,2*y,-1010);

	glTexCoord2f(0.0f,0.0f);glVertex3f(980-w,2*y,-1080);
	glTexCoord2f(1.0f,0.0f);glVertex3f(980+3*w,50*y,-1080);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980-6*w,50*y,-1080);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-2*w,2*y,-1080);

	glTexCoord2f(0.0f,0.0f);glVertex3f(1060,50*y,-985-3*w);//横
	glTexCoord2f(1.0f,0.0f);glVertex3f(1060-w,48*y,-985-3*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980+3*w,48*y,-1080+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980+3*w,50*y,-1080);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1060-w,48*y,-985-3*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1060-2*w,50*y,-985-3*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980+3*w,50*y,-1080+2*w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980+3*w,48*y,-1080+w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,50*y,-985-3*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1020+w,49*y,-985-3*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980+3*w,49*y,-1010-w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980+3*w,50*y,-1010);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1020+w,49*y,-985-3*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1020+2*w,50*y,-985-3*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980+3*w,50*y,-1010-2*w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980+3*w,49*y,-1010-w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(1060,50*y,-985+6*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1060-w,48*y,-985+6*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980-6*w,48*y,-1080+w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-6*w,50*y,-1080);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1060-w,48*y,-985+6*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1060-2*w,50*y,-985+6*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980-6*w,50*y,-1080+2*w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-6*w,48*y,-1080+w);

	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,50*y,-985+6*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1020+w,49*y,-985+6*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980-6*w,49*y,-1010-w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-6*w,50*y,-1010);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1020+w,49*y,-985+6*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1020+2*w,50*y,-985+6*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980-6*w,50*y,-1010-2*w);
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-6*w,49*y,-1010-w);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,m_textureWall[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,2*y,-985+w);//-1000 右
	glTexCoord2f(0.0f,1.0f);glVertex3f(1020,50*y,-985-3*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(1060,50*y,-985-3*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1060,2*y,-985+w);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,m_textureWall[1]);
	glBegin(GL_QUADS);	
	glTexCoord2f(0.0f,0.0f);glVertex3f(1020,2*y,-985+2*w);//-1000 右
	glTexCoord2f(0.0f,1.0f);glVertex3f(1020,50*y,-985+6*w);
	glTexCoord2f(1.0f,1.0f);glVertex3f(1060,50*y,-985+6*w);
	glTexCoord2f(1.0f,0.0f);glVertex3f(1060,2*y,-985+2*w);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,m_textureWall[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);glVertex3f(980-2*w,2*y,-1010);//-1000 左
	glTexCoord2f(0.0f,1.0f);glVertex3f(980-6*w,50*y,-1010);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980-6*w,50*y,-1080);
	glTexCoord2f(1.0f,0.0f);glVertex3f(980-2*w,2*y,-1080);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,m_textureWall[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.1f);glVertex3f(980-w,2*y,-1010);//-1000 左
	glTexCoord2f(0.0f,1.0f);glVertex3f(980+3*w,50*y,-1010);
	glTexCoord2f(1.0f,1.0f);glVertex3f(980+3*w,50*y,-1080);
	glTexCoord2f(1.0f,0.1f);glVertex3f(980-w,2*y,-1080);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////
// 函数：Select()
// 参数: 颜色索引值
// 功能：选择颜色
//////////////////////////////////////////////////////////////////////////
void Scene::Select(int r)//选择颜色
{
	switch(r)
	{
	case 0:glColor4ub(57,153,227,181);
		break;
	case 1:glColor4ub(91,191,240,200);
		break;
	case 2:glColor4ub(140,197,242,191);
		break;
	case 3:glColor4ub(1,178,228,238);
		break;
	case 4:glColor4ub(0,132,233,240);
		break;
	case 5:glColor4ub(173,249,239,207);
		break;
	}

}

//////////////////////////////////////////////////////////////////////////
// 函数：DrawLake()
// 参数：NULL
// 功能：绘制湖面
//////////////////////////////////////////////////////////////////////////
void Scene::DrawLake()
{
	float y=0.1f;
	float yh=4.0f;
	int r=1;
	glPushMatrix();
	
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D,m_textureRiver);
	glEnable(GL_TEXTURE_2D);	

	glBegin(GL_QUADS);
	Select(r);
	//Lake1
	glTexCoord2f(0.0f,0.0f);glVertex3f(80,y,200);
	glTexCoord2f(65.0f,0.0f);glVertex3f(80,y,600);
	glTexCoord2f(65.0f,60.0f);glVertex3f(745,y,600);
	glTexCoord2f(0.0f, 60.0f);glVertex3f(745,y,200);
	
	//斜边
	glTexCoord2f(0.0f,0.0f);glVertex3f(80,yh,180);//下
	glTexCoord2f(2.0f,0.0f);glVertex3f(80,y,200);
	glTexCoord2f(2.0f,60.0f);glVertex3f(745,y,200);
	glTexCoord2f(0.0f,60.0f);glVertex3f(745,yh,180);

	glTexCoord2f(0.0f,0.0f);glVertex3f(70,yh,200);//右
	glTexCoord2f(1.0f,0.0f);glVertex3f(80,y,200);
	glTexCoord2f(1.0f,60.0f);glVertex3f(80,y,600);
	glTexCoord2f(0.0f,60.0f);glVertex3f(70,yh,600);
	
	glTexCoord2f(0.0f,0.0f);glVertex3f(80,y,600);//上
	glTexCoord2f(1.0f,0.0f);glVertex3f(80,yh,610);
	glTexCoord2f(1.0f,60.0f);glVertex3f(725,yh,610);
	glTexCoord2f(0.0f,60.0f);glVertex3f(725,y,600);

	glTexCoord2f(0.0f,0.0f);glVertex3f(745,y,200);//左
	glTexCoord2f(2.0f,0.0f);glVertex3f(765,yh,200);
	glTexCoord2f(2.0f,60.0f);glVertex3f(765,yh,600);
	glTexCoord2f(0.0f,60.0f);glVertex3f(745,y,600);

	//平面
	glTexCoord2f(0.0f,0.0f);glVertex3f(80,yh,170);
	glTexCoord2f(1.0f,0.0f);glVertex3f(80,yh,180);
	glTexCoord2f(1.0f,60.0f);glVertex3f(745,yh,180);
	glTexCoord2f(0.0f, 60.0f);glVertex3f(745,yh,170);
	
	glTexCoord2f(0.0f,0.0f);glVertex3f(80,yh,610);
	glTexCoord2f(1.0f,0.0f);glVertex3f(80,yh,630);
	glTexCoord2f(1.0f,60.0f);glVertex3f(725,yh,630);
	glTexCoord2f(0.0f,60.0f);glVertex3f(725,yh,610);

	glTexCoord2f(0.0f,0.0f);glVertex3f(765,yh,200);
	glTexCoord2f(2.0f,0.0f);glVertex3f(785,yh,200);
	glTexCoord2f(2.0f,60.0f);glVertex3f(785,yh,600);
	glTexCoord2f(0.0f,60.0f);glVertex3f(765,yh,600);

	//三角形补口
	glTexCoord2f(0.0f,0.0f);glVertex3f(80,y,200);//下右
	glTexCoord2f(2.0f,0.0f);glVertex3f(80,yh,180);
	glTexCoord2f(2.0f,2.0f);glVertex3f(70,yh,200);
	glTexCoord2f(0.0f,2.0f);glVertex3f(70,yh,200);

	glTexCoord2f(0.0f,0.0f);glVertex3f(80,y,600);//右上
	glTexCoord2f(2.0f,0.0f);glVertex3f(80,yh,610);
	glTexCoord2f(2.0f,2.0f);glVertex3f(70,yh,600);
	glTexCoord2f(0.0f,2.0f);glVertex3f(70,yh,600);

	glTexCoord2f(0.0f,0.0f);glVertex3f(745,y,200);//下左
	glTexCoord2f(4.0f,0.0f);glVertex3f(745,yh,180);
	glTexCoord2f(4.0f,4.0f);glVertex3f(765,yh,200);
	glTexCoord2f(0.0f,4.0f);glVertex3f(765,yh,200);
	glEnd();
	glPopMatrix();	
	
	DrawMultiLake(y,yh);
	DrawNearLake(y,yh);
}

//////////////////////////////////////////////////////////////////////////
// 函数：DrawMultiLake()
// 参数：参数 y, yh无实意
// 功能：绘制多个湖面
//////////////////////////////////////////////////////////////////////////
void Scene::DrawMultiLake(float y,float yh)
{
	yh=y=0.0;
	y=-20.0;
	glPushMatrix();	
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D,m_textureLake);//m_groundTexture);
	glEnable(GL_TEXTURE_2D);	
	//Lake2群
	glBegin(GL_QUADS);
	//L1_A
	glTexCoord2f(0.0f,0.0f);glVertex3f(4835,y,1280);
	glTexCoord2f(20.0f,0.0f);glVertex3f(3958,y,1280);
	glTexCoord2f(20.0f,10.0f);glVertex3f(3864,y,720);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4735,y,720);
	//B
	glTexCoord2f(0.0f,0.0f);glVertex3f(4735,y,680);
	glTexCoord2f(20.0f,0.0f);glVertex3f(4735,y,400);
	glTexCoord2f(20.0f,10.0f);glVertex3f(3864,y,400);
	glTexCoord2f(0.0f,10.0f);glVertex3f(3864,y,680);

	//C_1
	glTexCoord2f(0.0f,0.0f);glVertex3f(4900,y,1770);
	glTexCoord2f(20.0f,0.0f);glVertex3f(4282,y,1770);
	glTexCoord2f(20.0f,10.0f);glVertex3f(4282,y,1320);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4900,y,1320);

	//C_2
	glTexCoord2f(0.0f,0.0f);glVertex3f(4282,y,1770);
	glTexCoord2f(20.0f,0.0f);glVertex3f(4181,y,1625);
	glTexCoord2f(20.0f,20.0f);glVertex3f(3984,y,1358);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4282,y,1358);

	//C_3
	glTexCoord2f(0.0f,0.0f);glVertex3f(4282,y,1358);
	glTexCoord2f(20.0f,0.0f);glVertex3f(3984,y,1358);
	glTexCoord2f(20.0f,8.0f);glVertex3f(4000,y,1320);
	glTexCoord2f(0.0f,8.0f);glVertex3f(4282,y,1320);

	//路底
	glTexCoord2f(0.0f,0.0f);glVertex3f(4735,y,720);//(A B)
	glTexCoord2f(20.0f,0.0f);glVertex3f(3864,y,720);
	glTexCoord2f(20.0f,4.0f);glVertex3f(3864,y,680);
	glTexCoord2f(0.0f,4.0f);glVertex3f(4735,y,680);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4835,y,1280);//(B C)
	glTexCoord2f(20.0f,0.0f);glVertex3f(3958,y,1280);
	glTexCoord2f(20.0f,3.0f);glVertex3f(3960,y,1320);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4900,y,1320);
	
	//斜面
	glTexCoord2f(0.0f,0.0f);glVertex3f(4735,y,400);//下
	glTexCoord2f(40.0f,0.0f);glVertex3f(3864,y,400);
	glTexCoord2f(40.0f,2.0f);glVertex3f(3864,yh,390);
	glTexCoord2f(0.0f,2.0f);glVertex3f(4735,yh,390);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3854,yh,400);//右_1
	glTexCoord2f(2.0f,0.0f);glVertex3f(3864,y,400);
	glTexCoord2f(2.0f,15.0f);glVertex3f(3864,y,720);
	glTexCoord2f(0.0f,15.0f);glVertex3f(3854,yh,720);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4735,y,720);//左_1
	glTexCoord2f(2.0f,0.0f);glVertex3f(4755,yh,720);
	glTexCoord2f(2.0f,30.0f);glVertex3f(4755,yh,400);
	glTexCoord2f(0.0f,30.0f);glVertex3f(4735,y,400);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3958,y,1280);//右_2
	glTexCoord2f(3.0f,0.0f);glVertex3f(3948,yh,1280);
	glTexCoord2f(3.0f,15.0f);glVertex3f(3854,yh,720);
	glTexCoord2f(0.0f,15.0f);glVertex3f(3864,y,720);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4735,y,720);//左_2
	glTexCoord2f(3.0f,0.0f);glVertex3f(4755,yh,720);
	glTexCoord2f(3.0f,20.0f);glVertex3f(4855,yh,1280);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4835,y,1280);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3984,y,1358);//右_3
	glTexCoord2f(6.0f,0.0f);glVertex3f(4000,y,1320);
	glTexCoord2f(6.0f,3.0f);glVertex3f(3980,yh,1320);
	glTexCoord2f(0.0f,3.0f);glVertex3f(3964,yh,1358);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4181,y,1625);//右_4
	glTexCoord2f(10.0f,0.0f);glVertex3f(3984,y,1358);
	glTexCoord2f(10.0f,3.0f);glVertex3f(3964,yh,1358);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4161,yh,1625);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4282,y,1770);//右_5
	glTexCoord2f(3.0f,0.0f);glVertex3f(4282,yh,1790);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4161,yh,1625);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4181,y,1625);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4282,y,1770);//上
	glTexCoord2f(3.0f,0.0f);glVertex3f(4282,yh,1790);
	glTexCoord2f(3.0f,40.0f);glVertex3f(4900,yh,1790);
	glTexCoord2f(0.0f,40.0f);glVertex3f(4900,y,1770);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4900,y,1770);//左_3
	glTexCoord2f(15.0f,0.0f);glVertex3f(4900,y,1390);
	glTexCoord2f(15.0f,3.0f);glVertex3f(4930,yh,1390);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4930,yh,1770);

	//平面
	glTexCoord2f(0.0f,0.0f);glVertex3f(4735,yh,390);//下
	glTexCoord2f(40.0f,0.0f);glVertex3f(3864,yh,390);
	glTexCoord2f(40.0f,2.0f);glVertex3f(3864,yh,370);
	glTexCoord2f(0.0f,2.0f);glVertex3f(4735,yh,370);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3854,yh,720);//右_1
	glTexCoord2f(2.0f,0.0f);glVertex3f(3834,yh,720);
	glTexCoord2f(2.0f,30.0f);glVertex3f(3834,yh,400);
	glTexCoord2f(0.0f,30.0f);glVertex3f(3854,yh,400);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4775,yh,720);//左_1
	glTexCoord2f(2.0f,0.0f);glVertex3f(4755,yh,720);
	glTexCoord2f(2.0f,30.0f);glVertex3f(4755,yh,400);
	glTexCoord2f(0.0f,30.0f);glVertex3f(4775,yh,400);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3948,yh,1280);//右_2
	glTexCoord2f(20.0f,0.0f);glVertex3f(3854,yh,720);
	glTexCoord2f(20.0f,3.0f);glVertex3f(3834,yh,720);
	glTexCoord2f(0.0f,3.0f);glVertex3f(3928,yh,1280);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4875,yh,1280);//左_2
	glTexCoord2f(4.0f,0.0f);glVertex3f(4855,yh,1280);
	glTexCoord2f(4.0f,20.0f);glVertex3f(4755,yh,720);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4775,yh,720);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3964,yh,1358);//右_3
	glTexCoord2f(3.0f,0.0f);glVertex3f(3980,yh,1320);
	glTexCoord2f(3.0f,6.0f);glVertex3f(3950,yh,1320);
	glTexCoord2f(0.0f,6.0f);glVertex3f(3934,yh,1358);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4161,yh,1625);//右_4
	glTexCoord2f(20.0f,0.0f);glVertex3f(3964,yh,1358);
	glTexCoord2f(20.0f,3.0f);glVertex3f(3934,yh,1358);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4131,yh,1625);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4282,yh,1790);//右_5
	glTexCoord2f(3.0f,0.0f);glVertex3f(4282,yh,1820);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4131,yh,1625);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4161,yh,1625);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4282,yh,1790);//上
	glTexCoord2f(3.0f,0.0f);glVertex3f(4282,yh,1820);
	glTexCoord2f(3.0f,40.0f);glVertex3f(4900,yh,1820);
	glTexCoord2f(0.0f,40.0f);glVertex3f(4900,yh,1790);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4960,yh,1770);//左_3
	glTexCoord2f(30.0f,0.0f);glVertex3f(4960,yh,1390);
	glTexCoord2f(30.0f,6.0f);glVertex3f(4930,yh,1390);
	glTexCoord2f(0.0f,6.0f);glVertex3f(4930,yh,1770);

	//缺口
	//斜
	glTexCoord2f(0.0f,0.0f);glVertex3f(3864,y,400);//下右
	glTexCoord2f(2.0f,0.0f);glVertex3f(3864,yh,390);
	glTexCoord2f(2.0f,2.0f);glVertex3f(3854,yh,400);
	glTexCoord2f(0.0f,2.0f);glVertex3f(3854,yh,400);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4735,y,400);//下左
	glTexCoord2f(3.0f,0.0f);glVertex3f(4735,yh,390);
	glTexCoord2f(3.0f,3.0f);glVertex3f(4755,yh,400);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4755,yh,400);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4900,y,1770);//上左
	glTexCoord2f(4.0f,0.0f);glVertex3f(4900,yh,1790);
	glTexCoord2f(4.0f,3.0f);glVertex3f(4930,yh,1770);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4930,y,1770);

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(3958,y,1280);//右_2 右_3
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(3948,yh,1280);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(3980,yh,1320);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(4000,y,1320);

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(4835,y,1280);//左_2  左_3
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(4900,y,1320);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(4905,yh,1320);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(4855,yh,1280);

	//平
	glTexCoord2f(0.0f,0.0f);glVertex3f(3864,yh,390);
	glTexCoord2f(2.0f,0.0f);glVertex3f(3854,yh,400);
	glTexCoord2f(2.0f,3.0f);glVertex3f(3834,yh,400);
	glTexCoord2f(0.0f,3.0f);glVertex3f(3864,yh,370);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4735,yh,390);
	glTexCoord2f(4.0f,0.0f);glVertex3f(4755,yh,400);
	glTexCoord2f(4.0f,4.0f);glVertex3f(4775,yh,400);
	glTexCoord2f(0.0f,4.0f);glVertex3f(4735,yh,370);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4900,yh,1790);
	glTexCoord2f(4.0f,0.0f);glVertex3f(4900,yh,1820);
	glTexCoord2f(4.0f,4.0f);glVertex3f(4960,yh,1770);
	glTexCoord2f(0.0f,4.0f);glVertex3f(4930,yh,1770);

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(3948,yh,1280);//右_2 右_3
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(3928,yh,1280);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(3950,yh,1320);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(3980,yh,1320);

	//特殊处理
	glTexCoord2f(0.0f,0.0f);glVertex3f(4900,y,1390);//左_2 左_3
	glTexCoord2f(2.0f,0.0f);glVertex3f(4900,y,1320);
	glTexCoord2f(2.0f,5.0f);glVertex3f(4905,yh,1320);
	glTexCoord2f(0.0f,5.0f);glVertex3f(4905,yh,1390);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4900,y,1390);
	glTexCoord2f(2.0f,0.0f);glVertex3f(4905,yh,1390);
	glTexCoord2f(2.0f,3.0f);glVertex3f(4935,yh,1390);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4935,yh,1390);

	//L2
	glTexCoord2f(0.0f,0.0f);glVertex3f(4362,y,1930);
	glTexCoord2f(20.0f,0.0f);glVertex3f(4685,y,2273);
	glTexCoord2f(20.0f,10.0f);glVertex3f(4870,y,2200);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4900,y,1930);

	//斜
	glTexCoord2f(0.0f,0.0f);glVertex3f(4900,y,1930);//下
	glTexCoord2f(5.0f,0.0f);glVertex3f(4930,yh,1910);
	glTexCoord2f(5.0f,15.0f);glVertex3f(4342,yh,1910);
	glTexCoord2f(0.0f,15.0f);glVertex3f(4362,y,1930);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4685,y,2273);//右
	glTexCoord2f(3.0f,0.0f);glVertex3f(4665,yh,2293);
	glTexCoord2f(3.0f,20.0f);glVertex3f(4342,yh,1910);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4362,y,1910);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4685,y,2273);//上
	glTexCoord2f(5.0f,0.0f);glVertex3f(4665,yh,2293);
	glTexCoord2f(5.0f,15.0f);glVertex3f(4900,yh,2220);
	glTexCoord2f(0.0f,15.0f);glVertex3f(4870,y,2200);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4870,y,2200);//左
	glTexCoord2f(5.0f,0.0f);glVertex3f(4900,yh,2220);
	glTexCoord2f(5.0f,15.0f);glVertex3f(4930,yh,1910);
	glTexCoord2f(0.0f,15.0f);glVertex3f(4900,y,1930);

	//平面
	glTexCoord2f(0.0f,0.0f);glVertex3f(4930,yh,1910);//下
	glTexCoord2f(5.0f,0.0f);glVertex3f(4960,yh,1880);
	glTexCoord2f(5.0f,15.0f);glVertex3f(4312,yh,1880);
	glTexCoord2f(0.0f,15.0f);glVertex3f(4342,yh,1910);
	
	glTexCoord2f(0.0f,0.0f);glVertex3f(4665,yh,2293);//右
	glTexCoord2f(3.0f,0.0f);glVertex3f(4635,yh,2323);
	glTexCoord2f(3.0f,20.0f);glVertex3f(4312,yh,1880);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4342,yh,1910);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4665,yh,2293);//上
	glTexCoord2f(5.0f,0.0f);glVertex3f(4635,yh,2323);
	glTexCoord2f(5.0f,20.0f);glVertex3f(4930,yh,2250);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4900,yh,2220);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4900,yh,2220);//左
	glTexCoord2f(3.0f,0.0f);glVertex3f(4930,yh,2250);
	glTexCoord2f(3.0f,20.0f);glVertex3f(4960,yh,1880);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4930,yh,1910);

	//L3(注销)
/*	glTexCoord2f(0.0f,0.0f);glVertex3f(3978,y,1442);
	glTexCoord2f(5.0f,0.0f);glVertex3f(4019,y,1625);
	glTexCoord2f(5.0f,10.0f);glVertex3f(3978,y,1850);
	glTexCoord2f(0.0f,10.0f);glVertex3f(3978,y,1850);
*/
	//L4
	glTexCoord2f(0.0f,0.0f);glVertex3f(4029,y,1625);
	glTexCoord2f(20.0f,0.0f);glVertex3f(4008,y,1850);
	glTexCoord2f(20.0f,22.0f);glVertex3f(4080,y,2202);
	glTexCoord2f(0.0f,22.0f);glVertex3f(4500,y,2295);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4500,y,2295);
	glTexCoord2f(2.0f,0.0f);glVertex3f(4500,y,2295);
	glTexCoord2f(2.0f,2.0f);glVertex3f(4208,y,1850);
	glTexCoord2f(0.0f,2.0f);glVertex3f(4029,y,1625);

	//斜
	glTexCoord2f(0.0f,0.0f);glVertex3f(4029,y,1625);//下_1
	glTexCoord2f(3.0f,0.0f);glVertex3f(4039,yh,1625);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4218,yh,1850);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4208,y,1850);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4029,y,1625);//下_2
	glTexCoord2f(3.0f,0.0f);glVertex3f(4029,yh,1615);
	glTexCoord2f(3.0f,8.0f);glVertex3f(3998,yh,1850);
	glTexCoord2f(0.0f,8.0f);glVertex3f(4008,y,1850);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4008,y,1850);//右
	glTexCoord2f(3.0f,0.0f);glVertex3f(3998,yh,1850);
	glTexCoord2f(3.0f,20.0f);glVertex3f(4060,yh,2222);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4080,y,2202);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4080,y,2202);//上_1
	glTexCoord2f(3.0f,0.0f);glVertex3f(4060,yh,2222);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4520,yh,2315);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4500,y,2295);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4500,y,2295);//左
	glTexCoord2f(3.0f,0.0f);glVertex3f(4520,yh,2315);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4218,yh,1850);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4208,y,1850);

	//平
	glTexCoord2f(0.0f,0.0f);glVertex3f(4039,yh,1625);//下_1
	glTexCoord2f(3.0f,0.0f);glVertex3f(4049,yh,1625);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4228,yh,1850);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4218,yh,1850);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4029,yh,1615);//下_2
	glTexCoord2f(5.0f,0.0f);glVertex3f(4019,yh,1605);
	glTexCoord2f(5.0f,10.0f);glVertex3f(3988,yh,1850);
	glTexCoord2f(0.0f,10.0f);glVertex3f(3998,yh,1850);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3998,yh,1850);//右
	glTexCoord2f(3.0f,0.0f);glVertex3f(3988,yh,1850);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4040,yh,2252);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4060,yh,2222);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4060,yh,2222);//上_1
	glTexCoord2f(3.0f,0.0f);glVertex3f(4040,yh,2252);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4540,yh,2345);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4520,yh,2315);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4520,yh,2315);//左
	glTexCoord2f(3.0f,0.0f);glVertex3f(4540,yh,2345);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4228,yh,1850);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4218,yh,1850);

	//补充
	//斜
	glTexCoord2f(0.0f,0.0f);glVertex3f(4029,y,1625);//下_1 下_2
	glTexCoord2f(3.0f,0.0f);glVertex3f(4039,yh,1625);
	glTexCoord2f(3.0f,3.0f);glVertex3f(4029,yh,1615);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4029,yh,1615);

	//平
	glTexCoord2f(0.0f,0.0f);glVertex3f(4039,yh,1625);//下_1 下_2
	glTexCoord2f(3.0f,0.0f);glVertex3f(4049,yh,1625);
	glTexCoord2f(3.0f,3.0f);glVertex3f(4019,yh,1605);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4029,yh,1615);

	glEnd();
/*	
	glColor3f(0.5,1.0,1.0);
	glBegin(GL_POLYGON);
	//L2_A
	//glTexCoord2f(0.0f,0.0f);glVertex3f(5055,y,1320);
	//glTexCoord2f(1.0f,0.0f);
	glVertex3f(3978,y,1850);
	//glTexCoord2f(1.0f,60.0f);
	glVertex3f(4020,y,2282);
	//glTexCoord2f(0.0f,60.0f);
	glVertex3f(4500,y,2375);
	//glTexCoord2f(0.0f,0.0f);
	glVertex3f(4558,y,2368);
	//glTexCoord2f(1.0f,0.0f);
	glVertex3f(4238,y,1850);
	//glTexCoord2f(1.0f,60.0f);
	//glColor3f(1.0,0.0,0.0);
	glVertex3f(4059,y,1625);
	//glTexCoord2f(0.0f,60.0f);glVertex3f(4800,y,2350);	
	glEnd();
*/
/*
	//L2_A
	glBegin(GL_TRIANGLES);
	//glTexCoord2f(0.0f,0.0f);
	glVertex3f(3935,y,1442);
	//glTexCoord2f(1.0f,0.0f);
	glVertex3f(4059,y,1625);
	//glTexCoord2f(1.0f,60.0f);
	glVertex3f(3978,y,1850);
	//glTexCoord2f(0.0f,60.0f);glVertex3f(4895,y,1280);	
	glEnd();
*/
/*
	//L2_B
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f,0.0f);glVertex3f(3920,y,1320);
	glTexCoord2f(1.0f,0.0f);glVertex3f(3904,y,1358);
	glTexCoord2f(1.0f,60.0f);glVertex3f(4101,y,1625);
	glTexCoord2f(0.0f,60.0f);glVertex3f(4282,y,1850);
	glTexCoord2f(0.0f,0.0f);glVertex3f(4990,y,1850);
	glTexCoord2f(1.0f,0.0f);glVertex3f(4990,y,1320);	
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f,0.0f);glVertex3f(4282,y,1850);
	glTexCoord2f(1.0f,0.0f);glVertex3f(4605,y,2353);
	glTexCoord2f(1.0f,60.0f);glVertex3f(4960,y,2280);
	glTexCoord2f(0.0f,60.0f);glVertex3f(4990,y,1850);
	glEnd();
*/
	glDisable(GL_TEXTURE_2D);
}

//////////////////////////////////////////////////////////////////////////
// 函数：DrawNearLake(float y,float yh)
// 参数：参数 y,yh分别表示所绘制草地的高度
// 功能：绘制湖周边的草地
//////////////////////////////////////////////////////////////////////////
void Scene::DrawNearLake(float y,float yh)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D,m_groundTexture);
	//glColor4ub(56,66,102,256);
	glColor4ub(114,109,105,255);
	glBegin(GL_QUADS);

	//Lake1
	//草地边沿		
	glTexCoord2f(0.0f,0.0f);glVertex3f(80,y,150);
	glTexCoord2f(2.0f,0.0f);glVertex3f(80,yh,170);
	glTexCoord2f(2.0f,30.0f);glVertex3f(745,yh,170);
	glTexCoord2f(0.0f,30.0f);glVertex3f(745,y,150);

	glTexCoord2f(0.0f,0.0f);glVertex3f(60,y,200);
	glTexCoord2f(1.0f,0.0f);glVertex3f(70,yh,200);
	glTexCoord2f(1.0f,30.0f);glVertex3f(70,yh,600);
	glTexCoord2f(0.0f,30.0f);glVertex3f(60,y,600);

	glTexCoord2f(0.0f,0.0f);glVertex3f(80,y,150);
	glTexCoord2f(2.0f,0.0f);glVertex3f(80,yh,170);
	glTexCoord2f(2.0f,5.0f);glVertex3f(70,yh,200);
	glTexCoord2f(0.0f,5.0f);glVertex3f(60,y,200);

	glTexCoord2f(0.0f,0.0f);glVertex3f(80,yh,630);
	glTexCoord2f(1.0f,0.0f);glVertex3f(80,y,638);
	glTexCoord2f(1.0f,30.0f);glVertex3f(730,y,638);
	glTexCoord2f(0.0f,30.0f);glVertex3f(730,yh,630);

	glTexCoord2f(0.0f,0.0f);glVertex3f(60,y,600);
	glTexCoord2f(3.0f,0.0f);glVertex3f(70,yh,600);
	glTexCoord2f(3.0f,5.0f);glVertex3f(80,yh,630);
	glTexCoord2f(0.0f,5.0f);glVertex3f(80,y,638);

	glTexCoord2f(0.0f,0.0f);glVertex3f(785,yh,200);
	glTexCoord2f(2.0f,0.0f);glVertex3f(795,y,200);
	glTexCoord2f(2.0f,20.0f);glVertex3f(795,y,600);
	glTexCoord2f(0.0f,20.0f);glVertex3f(785,yh,600);

	glTexCoord2f(0.0f,0.0f);glVertex3f(745,y,150);
	glTexCoord2f(2.0f,0.0f);glVertex3f(745,yh,170);
	glTexCoord2f(2.0f,4.0f);glVertex3f(785,yh,200);
	glTexCoord2f(0.0f,4.0f);glVertex3f(795,y,200);

	y=0.0;yh=0.0;	
	//L1_A
	glTexCoord2f(0.0f,0.0f);glVertex3f(4735,yh,370);
	glTexCoord2f(40.0f,0.0f);glVertex3f(3864,yh,370);
	glTexCoord2f(40.0f,1.0f);glVertex3f(3864,y,365);
	glTexCoord2f(0.0f,1.0f);glVertex3f(4735,y,365);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3834,yh,720);
	glTexCoord2f(1.0f,0.0f);glVertex3f(3824,y,720);
	glTexCoord2f(1.0f,30.0f);glVertex3f(3824,y,400);
	glTexCoord2f(0.0f,30.0f);glVertex3f(3834,yh,400);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3864,y,365);
	glTexCoord2f(2.0f,0.0f);glVertex3f(3824,y,400);
	glTexCoord2f(2.0f,2.0f);glVertex3f(3834,yh,400);
	glTexCoord2f(0.0f,2.0f);glVertex3f(3864,yh,370);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4795,y,720);
	glTexCoord2f(2.0f,0.0f);glVertex3f(4775,yh,720);
	glTexCoord2f(2.0f,30.0f);glVertex3f(4775,yh,400);
	glTexCoord2f(0.0f,30.0f);glVertex3f(4795,y,400);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4795,y,400);
	glTexCoord2f(4.0f,0.0f);glVertex3f(4775,yh,400);
	glTexCoord2f(4.0f,3.0f);glVertex3f(4735,yh,370);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4735,y,365);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3928,yh,1280);
	glTexCoord2f(2.0f,0.0f);glVertex3f(3918,y,1280);
	glTexCoord2f(2.0f,30.0f);glVertex3f(3824,y,720);
	glTexCoord2f(0.0f,30.0f);glVertex3f(3834,yh,720);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3950,yh,1320);
	glTexCoord2f(3.0f,0.0f);glVertex3f(3920,y,1320);
	glTexCoord2f(3.0f,5.0f);glVertex3f(3926,y,1358);
	glTexCoord2f(0.0f,5.0f);glVertex3f(3934,yh,1358);

	glTexCoord2f(0.0f,0.0f);glVertex3f(3934,yh,1358);
	glTexCoord2f(3.0f,0.0f);glVertex3f(3926,y,1358);
	glTexCoord2f(3.0f,15.0f);glVertex3f(4101,y,1625);
	glTexCoord2f(0.0f,15.0f);glVertex3f(4131,yh,1625);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4282,yh,1820);
	glTexCoord2f(3.0f,0.0f);glVertex3f(4282,y,1850);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4101,y,1625);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4131,yh,1625);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4282,y,1850);
	glTexCoord2f(3.0f,0.0f);glVertex3f(4282,yh,1820);
	glTexCoord2f(3.0f,60.0f);glVertex3f(4900,yh,1820);
	glTexCoord2f(0.0f,60.0f);glVertex3f(4900,y,1850);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4960,yh,1770);
	glTexCoord2f(20.0f,0.0f);glVertex3f(4960,yh,1390);
	glTexCoord2f(20.0f,3.0f);glVertex3f(4990,y,1390);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4990,y,1770);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4900,yh,1820);
	glTexCoord2f(4.0f,0.0f);glVertex3f(4900,y,1850);
	glTexCoord2f(4.0f,3.0f);glVertex3f(4990,y,1770);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4960,yh,1770);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4895,y,1280);
	glTexCoord2f(4.0f,0.0f);glVertex3f(4875,yh,1280);
	glTexCoord2f(4.0f,20.0f);glVertex3f(4775,yh,720);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4795,y,720);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4905,yh,1320);//S
	glTexCoord2f(10.0f,0.0f);glVertex3f(4905,yh,1390);
	glTexCoord2f(10.0f,5.0f);glVertex3f(4960,yh,1390);
	glTexCoord2f(0.0f,5.0f);glVertex3f(4960,yh,1320);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4960,yh,1320);
	glTexCoord2f(8.0f,0.0f);glVertex3f(4990,y,1320);
	glTexCoord2f(8.0f,5.0f);glVertex3f(4990,y,1390);
	glTexCoord2f(0.0f,5.0f);glVertex3f(4960,yh,1390);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4990,y,1320);
	glTexCoord2f(8.0f,0.0f);glVertex3f(4960,yh,1320);
	glTexCoord2f(8.0f,3.0f);glVertex3f(4905,yh,1320);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4900,y,1320);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4990,y,1850);
	glTexCoord2f(6.0f,0.0f);glVertex3f(4960,yh,1880);
	glTexCoord2f(6.0f,60.0f);glVertex3f(4312,yh,1880);
	glTexCoord2f(0.0f,60.0f);glVertex3f(4282,y,1850);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4605,y,2353);
	glTexCoord2f(6.0f,0.0f);glVertex3f(4635,yh,2323);
	glTexCoord2f(6.0f,20.0f);glVertex3f(4312,yh,1880);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4282,y,1850);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4605,y,2353);
	glTexCoord2f(5.0f,0.0f);glVertex3f(4635,yh,2323);
	glTexCoord2f(5.0f,20.0f);glVertex3f(4930,yh,2250);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4960,y,2280);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4960,y,2280);
	glTexCoord2f(6.0f,0.0f);glVertex3f(4930,yh,2250);
	glTexCoord2f(6.0f,20.0f);glVertex3f(4960,yh,1880);
	glTexCoord2f(0.0f,20.0f);glVertex3f(4990,y,1850);

	//L_4
	glTexCoord2f(0.0f,0.0f);glVertex3f(4049,yh,1625);
	glTexCoord2f(3.0f,0.0f);glVertex3f(4059,y,1625);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4238,y,1850);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4228,yh,1850);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4019,yh,1605);
	glTexCoord2f(3.0f,0.0f);glVertex3f(4019,y,1600);
	glTexCoord2f(3.0f,10.0f);glVertex3f(3978,y,1850);
	glTexCoord2f(0.0f,10.0f);glVertex3f(3988,yh,1850);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4059,y,1625);
	glTexCoord2f(3.0f,0.0f);glVertex3f(4049,yh,1625);
	glTexCoord2f(3.0f,3.0f);glVertex3f(4019,yh,1605);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4019,y,1600);
	
	glTexCoord2f(0.0f,0.0f);glVertex3f(3978,y,1850);
	glTexCoord2f(3.0f,0.0f);glVertex3f(3988,yh,1850);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4040,yh,2252);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4020,y,2282);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4020,y,2282);
	glTexCoord2f(3.0f,0.0f);glVertex3f(4040,yh,2252);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4540,yh,2345);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4500,y,2375);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4500,y,2375);
	glTexCoord2f(2.0f,0.0f);glVertex3f(4558,y,2368);
	glTexCoord2f(2.0f,3.0f);glVertex3f(4540,yh,2345);
	glTexCoord2f(0.0f,3.0f);glVertex3f(4540,yh,2345);

	glTexCoord2f(0.0f,0.0f);glVertex3f(4558,y,2368);
	glTexCoord2f(3.0f,0.0f);glVertex3f(4540,yh,2345);
	glTexCoord2f(3.0f,10.0f);glVertex3f(4228,yh,1850);
	glTexCoord2f(0.0f,10.0f);glVertex3f(4238,y,1850);

	glEnd();
	//glClearColor(0.0,0.0,0.0,0.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

