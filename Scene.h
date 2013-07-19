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

struct DetailedModel	//ģ����Ϣ�ṹ��
{
	int listIndex;		//��ʾ�б�������
	CVector3 position;	//λ��
	CVector3 size;      //ԭʼ��С
	float yrot;			//��ת�Ƕ�
	float scale;		//��С
};

struct TreeData			//��ľ �ṹ��
{
	int x,y,z;			//λ��
	float size;			//��С
	int h;				//�߶�
	int text;			//����
};

struct GrassData		//���� �ṹ��
{
	int x,y,z;			//λ��
	float size;			//��С
	int text;			//����
};

class Scene  
{
public:
	
	int m_nLists;										//������ʾ�б����Ŀ
	GLuint m_listIndex[MAX_NUMBER_OF_LISTS];			//ģ����ʾ�б�����	
	int m_nModels;										//ģ����
	DetailedModel m_models[MAX_NUMBER_OF_DETAILED_MODELS];//�Ѽ��ص�ģ���б�	
	Model m_modelLoader;						//����ģ�͸�������

	int m_nTrees;										//��ľ������
	TreeData m_treeData[1400];//ʵ��1354				//��ľ����
	int m_nGrasses;										//���ݵ�����
	GrassData m_grassData[1200];//ʵ��1091				//��������
	Plant m_Plant;//����ֲ�����

	GLuint m_textureRiver;								//����������ͼ
	GLuint m_textureBridge;								//����������ͼ

	GLuint m_textureFence;								//����������ͼ
	GLuint m_textureBoundary;							//�ֽ���������ͼ
	GLuint m_textureWall[5];							//ǽ����ͼ
	GLuint m_groundTexture;								//����������ͼ
	GLuint m_textureLake;								//����������ͼ
public:
	Scene();
	virtual ~Scene();
	void Load();						//���볡��
	void Render();						//��ʾ����	
	bool AddModel(char *modelfile);		//���ģ��

	bool ReadPlant();//���ļ�����ֲ��
	void RenderPlant();//����ֲ��

	void DrawRiver(float x1,float z1,float x2,float z2,
				   float x3,float z3,float x4,float z4);
	void RenderRiver();//���ƺ���

	void RenderRoadBridge();				//����·�ߵ���
	void RenderBridge();					//���ƴ���	

	void DrawMultiLake(float,float);	//���ƺ���	
	void DrawNearLake(float,float);		//���ƺ��ܱ߳���
	void DrawLake();					//���ƺ���
	void Select(int r);//ѡ����ɫ
	
	
};

#endif // !defined(AFX_SCENE_H__0681AC9A_D40F_41FC_B0C8_716D84C81B5B__INCLUDED_)
