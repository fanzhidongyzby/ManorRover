// Scene.h: interface for the Scene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENE_H__0681AC9A_D40F_41FC_B0C8_716D84C81B5B__INCLUDED_)
#define AFX_SCENE_H__0681AC9A_D40F_41FC_B0C8_716D84C81B5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Model.h"	// Added by ClassView
#include "Vector.h"
#include "Model.h"
#include "SkyDome.h"	// Added by ClassView
#include "Plant.h"
#include <gl\glu.h>     

#include <fstream>

#define MAX_NUMBER_OF_LISTS 200
#define MAX_NUMBER_OF_DETAILED_MODELS 200

struct DetailedModel	//模型信息结构体
{
	int listIndex;		//显示列表索引号
	CVector3 position;	//位置
	CVector3 size;      //原始大小
	float yrot;			//旋转角度
	float scale;		//大小
};

struct TreeData			//树木 结构体
{
	int x,y,z;			//位置
	float size;			//大小
	int h;				//高度
	int text;			//纹理
};

struct GrassData		//花草 结构体
{
	int x,y,z;			//位置
	float size;			//大小
	int text;			//纹理
};

class Scene  
{
public:
	
	int m_nLists;										//建筑显示列表的数目
	GLuint m_listIndex[MAX_NUMBER_OF_LISTS];			//模型显示列表索引	
	int m_nModels;										//模型数
	DetailedModel m_models[MAX_NUMBER_OF_DETAILED_MODELS];//已加载的模型列表	
	Model m_modelLoader;						//载入模型辅助对象

	int m_nTrees;										//树木的数量
	TreeData m_treeData[1400];//实际1354				//树木索引
	int m_nGrasses;										//花草的数量
	GrassData m_grassData[1200];//实际1091				//花草索引
	Plant m_Plant;//载入植物对象

	GLuint m_textureRiver;								//河流纹理贴图
	GLuint m_textureBridge;								//桥梁纹理贴图

	GLuint m_textureFence;								//扶手纹理贴图
	GLuint m_textureBoundary;							//分界面纹理贴图
	GLuint m_textureWall[5];							//墙体贴图
	GLuint m_groundTexture;								//地面纹理贴图
	GLuint m_textureLake;								//湖面纹理贴图
public:
	Scene();
	virtual ~Scene();
	void Load();						//载入场景
	void Render();						//显示场景	
	bool AddModel(char *modelfile);		//添加模型

	bool ReadPlant();//读文件载入植物
	void RenderPlant();//绘制植物

	void DrawRiver(float x1,float z1,float x2,float z2,
				   float x3,float z3,float x4,float z4);
	void RenderRiver();//绘制河流

	void RenderRoadBridge();				//绘制路边的桥
	void RenderBridge();					//绘制大桥	

	void DrawMultiLake(float,float);	//绘制湖面	
	void DrawNearLake(float,float);		//绘制湖周边场景
	void DrawLake();					//绘制湖面
	void Select(int r);//选择颜色
	
	
};

#endif // !defined(AFX_SCENE_H__0681AC9A_D40F_41FC_B0C8_716D84C81B5B__INCLUDED_)
