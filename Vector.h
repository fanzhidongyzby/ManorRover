// Vector.h: interface for the Vector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__13DCB881_E0A8_44CE_AE5A_13295F459D3C__INCLUDED_)
#define AFX_VECTOR_H__13DCB881_E0A8_44CE_AE5A_13295F459D3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// class: ����2D���࣬���ڱ���ģ�͵�UV��������
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

// class: ����3D����࣬���ڱ���ģ���еĶ���
class CVector3 
{
public:
	CVector3(){}
	CVector3(float x1,float y1,float z1);
	CVector3 operator -(CVector3 &vect);		//����-�������
	void Init(float x1,float y1,float z1);		//��ʼ��
	CVector3 Cross(CVector3 &vect);				//�������
	CVector3 operator+(CVector3 &vect);			//����+�������
	CVector3 DivideVectorByScaler(float Scaler);//�����С
	static CVector3 Normalize(CVector3 vNormal);//��λ������
	static CVector3 Vector(CVector3 vPoint1,	//�������Ӧ������
						   CVector3 vPoint2);
	float x, y, z;
};

#endif // !defined(AFX_VECTOR_H__13DCB881_E0A8_44CE_AE5A_13295F459D3C__INCLUDED_)
