// Vector.cpp: implementation of the Vector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vector.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include <CMath>

// �������Щ������Ҫ�������㶥��ķ�����������ķ�������Ҫ�����������


// ����ĺ궨�����һ��ʸ���ĳ���
#define Mag(Normal) (sqrt(Normal.x*Normal.x + Normal.y*Normal.y + Normal.z*Normal.z))

//*/ 
// ������Vector()
// ����������vPoint1,vPoint2Ϊ����ʸ����������
// ���ܣ������������ʸ��
//*/

// ����ĺ��������������ʸ��
CVector3 CVector3::Vector(CVector3 vPoint1, CVector3 vPoint2)
{
  CVector3 vVector;              

  vVector.x = vPoint1.x - vPoint2.x;      
  vVector.y = vPoint1.y - vPoint2.y;      
  vVector.z = vPoint1.z - vPoint2.z;      

  return vVector;                
}

//*/ 
// ������DivideVectorByScaler(float Scaler)
// ����������ScalerΪ�����ı���
// ���ܣ�����ʸ��������
//*/

// ����ĺ�������ʸ��������
CVector3 CVector3::DivideVectorByScaler(float Scaler)
{
  CVector3 vResult;              
  
  vResult.x = x / Scaler;      
  vResult.y = y / Scaler;      
  vResult.z = z / Scaler;      

  return vResult;                
}

//*/ 
// ������Normalize()
// ����������vNormalΪһ��ʸ��
// ���ܣ�ʸ���ĵ�λ��
//*/

// ����ĺ����淶��ʸ��
CVector3 CVector3::Normalize(CVector3 vNormal)
{
  double Magnitude;              

  Magnitude = Mag(vNormal);          // ���ʸ���ĳ���

  vNormal.x /= (float)Magnitude;        
  vNormal.y /= (float)Magnitude;        
  vNormal.z /= (float)Magnitude;        

  return vNormal;                
}

//����+
CVector3 CVector3::operator +(CVector3 &vect)
{
	CVector3 vResult;              
	
	vResult.x = x + vect.x;    
	vResult.y = y + vect.y;    
	vResult.z = z + vect.z;    
	
	return vResult;                
	
}

//*/ 
// ������Cross(CVector3 &vect)
// ����������vectΪһ��ʸ��
// ���ܣ�������ʸ���Ĳ��
//*/

CVector3 CVector3::Cross(CVector3 &vect)
{
	CVector3 vCross;                
	
	vCross.x = ((y * vect.z) - (z * vect.y));
	
	vCross.y = ((z * vect.x) - (x * vect.z));
	
	vCross.z = ((x * vect.y) - (y * vect.x));
	
	return vCross;    
}

//*/ 
// ������Init()
// ����������x1, y1, z1һ����
// ���ܣ���ʼ����
//*/

void CVector3::Init(float x1, float y1, float z1)
{
	x=x1;
	y=y1;
	z=z1;
}

//����-
CVector3 CVector3::operator -(CVector3 &vect)
{
	CVector3 vResult;              
	
	vResult.x = x - vect.x;    
	vResult.y = y - vect.y;    
	vResult.z = z - vect.z;    
	
	return vResult;                
	

}

//////////////////////////////////////////////////////////////////////////
//����:operator ==
//����:һ��CVector2���͵ĵ�
//����:����==��������ж����������Ƿ����
//////////////////////////////////////////////////////////////////////////
bool CVector2::operator ==(CVector2 &vd)
{
	if ((x==vd.x)&&(y==vd.y))
	{
		return true;
	} 
	else
	{
		return false;
	}
}


//////////////////////////////////////////////////////////////////////////
//����:operator -
//����:һ��CVector2���͵ĵ�
//����:����-���������ɶ�ά�����ļ���
//////////////////////////////////////////////////////////////////////////
CVector2 CVector2::operator -(CVector2 &vect)
{
	CVector2 result;
	result.x=x-vect.x;
	result.y=y-vect.y;
	return result;
}


//////////////////////////////////////////////////////////////////////////
//����:Init
//����:Ҫ��ʼ��Ϊ��x y����ֵ
//����:��ʼ����ά����
//////////////////////////////////////////////////////////////////////////
void CVector2::Init(float xpos, float ypos)
{
	x=xpos;
	y=ypos;
}


//////////////////////////////////////////////////////////////////////////
//����:DistanceFrom
//����:һ��CVector2���͵ĵ�
//����:���������ľ���
//////////////////////////////////////////////////////////////////////////
float CVector2::DistanceFrom(CVector2 &p)
{
	return (float)sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));
}

//////���캯��
CVector2::CVector2(float xpos,float ypos)
{
	Init( xpos, ypos);
}
CVector3::CVector3(float x1,float y1,float z1)
{
	Init( x1, y1, z1);
}
