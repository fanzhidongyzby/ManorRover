// Vector.h: interface for the Vector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__13DCB881_E0A8_44CE_AE5A_13295F459D3C__INCLUDED_)
#define AFX_VECTOR_H__13DCB881_E0A8_44CE_AE5A_13295F459D3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// class: 定义2D点类，用于保存模型的UV纹理坐标
class CVector2 
{
public:
	CVector2(){}
	CVector2(float xpos,float ypos);
	float DistanceFrom(CVector2 &p);
	void Init(float xpos,float ypos);
	CVector2 operator-(CVector2 &vect);
	float x, y;
	bool operator ==(CVector2 &vd);
};

// class: 定义3D点的类，用于保存模型中的顶点
class CVector3 
{
public:
	CVector3(){}
	CVector3(float x1,float y1,float z1);
	CVector3 operator -(CVector3 &vect);		//重载-，点相减
	void Init(float x1,float y1,float z1);		//初始化
	CVector3 Cross(CVector3 &vect);				//向量叉乘
	CVector3 operator+(CVector3 &vect);			//重载+，点相加
	CVector3 DivideVectorByScaler(float Scaler);//点的缩小
	static CVector3 Normalize(CVector3 vNormal);//单位化向量
	static CVector3 Vector(CVector3 vPoint1,	//求两点对应的向量
						   CVector3 vPoint2);
	float x, y, z;
};

#endif // !defined(AFX_VECTOR_H__13DCB881_E0A8_44CE_AE5A_13295F459D3C__INCLUDED_)
