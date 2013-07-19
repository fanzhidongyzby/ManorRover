// Model.h: interface for the Model class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_H__A0CA8C91_A8B7_4867_826E_F9AE6B62867D__INCLUDED_)
#define AFX_MODEL_H__A0CA8C91_A8B7_4867_826E_F9AE6B62867D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MAX_TEXTURES 100                // ����������Ŀ
#include "StdAfx.h"
#include "Vector.h"

#include <fstream>
#include <vector>

#include <crtdbg.h>
#include <olectl.h>              
              
using namespace std;
// struct: ��Ľṹ����
struct tFace
{
  int vertIndex[3];       // ��������
  int coordIndex[3];      // ������������
};

// struct: ������Ϣ�ṹ��
struct tMaterialInfo
{
  char strName[255];      // ��������
  char strFile[255];      // �����������ӳ�䣬���ʾ�����ļ�����
  BYTE color[3];		  // �����RGB��ɫ
  int texureId;			  // ����ID
  float uTile;			 // u �ظ�
  float vTile;           // v �ظ�
  float uOffset;		 // u ����ƫ��
  float vOffset;         // v ����ƫ��
} ;

// struct: ������Ϣ�ṹ��
struct t3DObject 
{
  int numOfVerts;			// ģ���ж������Ŀ
  int numOfFaces;			// ģ���������Ŀ
  int numTexVertex;			// ģ���������������Ŀ
  int materialID;			// ����ID
  bool bHasTexture;			// �Ƿ��������ӳ��
  char strName[255];		// ���������
  CVector3 *pVerts;			// ����Ķ���
  CVector3 *pNormals;		// ����ķ�����
  CVector2 *pTexVerts;		// ����UV����
  tFace *pFaces;			// ���������Ϣ
};

struct tIndices 
{              
  unsigned short a, b, c, bVisible;  
};

// struct: �������Ϣ�Ľṹ
struct tChunk
{
  unsigned short int ID;          // ���ID    
  unsigned int length;          // ��ĳ���
  unsigned int bytesRead;          // ��Ҫ���Ŀ����ݵ��ֽ���
};

// class:ģ����Ϣ�ṹ��
class Model 
{
public:
	//bool LoadFrom3dsFile(char *filename);	
		
	UINT texture[MAX_TEXTURES];			//����
	int numOfObjects;					// ģ���ж������Ŀ
	int numOfMaterials;					// ģ���в��ʵ���Ŀ
	vector<tMaterialInfo> pMaterials;	// ����������Ϣ
	vector<t3DObject> pObject;			// ģ���ж���������Ϣ
	bool Import3DS(char *filename);		//����3DS�ļ�
	void DrawModel();					//����ģ��
	void Clear();						//�����Ϣ
};

/////////////////////////////////////////////////////////////////////////////////////
// ������(Primary Chunk)��λ���ļ��Ŀ�ʼ
#define PRIMARY 0x4D4D

// ����(Main Chunks)
#define OBJECTINFO 0x3D3D        // �������İ汾��
#define VERSION 0x0002        // .3ds�ļ��İ汾
#define EDITKEYFRAME 0xB000        // ���йؼ�֡��Ϣ��ͷ��

// ����Ĵμ�����(��������Ĳ��ʺͶ���
#define MATERIAL   0xAFFF        // ����������Ϣ
#define OBJECT     0x4000        // ���������桢�������Ϣ

// ���ʵĴμ�����
#define MATNAME 0xA000        // �����������
#define MATDIFFUSE 0xA020        // ����/���ʵ���ɫ
#define MATMAP 0xA200        // �²��ʵ�ͷ��
#define MATMAPFILE 0xA300        // ����������ļ���

#define OBJECT_MESH 0x4100        // �µ��������

// OBJECT_MESH�Ĵμ�����
#define OBJECT_VERTICES 0x4110      // ���󶥵�
#define OBJECT_FACES    0x4120      // �������
#define OBJECT_MATERIAL    0x4130      // ����Ĳ���
#define OBJECT_UV      0x4140      // �����UV��������

// CLoad3DS�ദ�����е�װ�����
class CLoad3DS
{
public:
  CLoad3DS();                // ��ʼ�����ݳ�Ա
  // װ��3ds�ļ���ģ�ͽṹ��
  bool Import3DS(Model *pModel, char *strFileName);
	// ����һ������
  int BuildTexture(char *szPathName, GLuint &texid);
private:  
  
  // ��һ���ַ���
  int GetString(char *);
  // ����һ����
  void ReadChunk(tChunk *);
  // ����һ����
  void ProcessNextChunk(Model *pModel, tChunk *);
  // ����һ�������
  void ProcessNextObjectChunk(Model *pModel, t3DObject *pObject, tChunk *);
  // ����һ�����ʿ�
  void ProcessNextMaterialChunk(Model *pModel, tChunk *);
  // ��������ɫ��RGBֵ
  void ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk);
  // ������Ķ���
  void ReadVertices(t3DObject *pObject, tChunk *);
  // �����������Ϣ
  void ReadVertexIndices(t3DObject *pObject, tChunk *);
  // ���������������
  void ReadUVCoordinates(t3DObject *pObject, tChunk *);
  // ���������Ĳ�������
  void ReadObjectMaterial(Model *pModel, t3DObject *pObject, tChunk *pPreviousChunk);
  // ������󶥵�ķ�����
  void ComputeNormals(Model * pModel);
  // �ر��ļ����ͷ��ڴ�ռ�
  void CleanUp();
  // �ļ�ָ��
  FILE *m_FilePointer;

  tChunk *m_CurrentChunk;
  tChunk *m_TempChunk;
};
#endif // !defined(AFX_MODEL_H__A0CA8C91_A8B7_4867_826E_F9AE6B62867D__INCLUDED_)
