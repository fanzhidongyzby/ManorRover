// Vector.cpp: implementation of the Vector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vector.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include <CMath>

// 下面的这些函数主要用来计算顶点的法向量，顶点的法向量主要用来计算光照


// 下面的宏定义计算一个矢量的长度
#define Mag(Normal) (sqrt(Normal.x*Normal.x + Normal.y*Normal.y + Normal.z*Normal.z))

//*/ 
// 函数：Vector()
// 参数：参数vPoint1,vPoint2为所求矢量的两个点
// 功能：求两点决定的矢量
//*/

// 下面的函数求两点决定的矢量
CVector3 CVector3::Vector(CVector3 vPoint1, CVector3 vPoint2)
{
  CVector3 vVector;              

  vVector.x = vPoint1.x - vPoint2.x;      
  vVector.y = vPoint1.y - vPoint2.y;      
  vVector.z = vPoint1.z - vPoint2.z;      

  return vVector;                
}

//*/ 
// 函数：DivideVectorByScaler(float Scaler)
// 参数：参数Scaler为所见的比例
// 功能：处理矢量的缩放
//*/

// 下面的函数处理矢量的缩放
CVector3 CVector3::DivideVectorByScaler(float Scaler)
{
  CVector3 vResult;              
  
  vResult.x = x / Scaler;      
  vResult.y = y / Scaler;      
  vResult.z = z / Scaler;      

  return vResult;                
}

//*/ 
// 函数：Normalize()
// 参数：参数vNormal为一个矢量
// 功能：矢量的单位化
//*/

// 下面的函数规范化矢量
CVector3 CVector3::Normalize(CVector3 vNormal)
{
  double Magnitude;              

  Magnitude = Mag(vNormal);          // 获得矢量的长度

  vNormal.x /= (float)Magnitude;        
  vNormal.y /= (float)Magnitude;        
  vNormal.z /= (float)Magnitude;        

  return vNormal;                
}

//重载+
CVector3 CVector3::operator +(CVector3 &vect)
{
	CVector3 vResult;              
	
	vResult.x = x + vect.x;    
	vResult.y = y + vect.y;    
	vResult.z = z + vect.z;    
	
	return vResult;                
	
}

//*/ 
// 函数：Cross(CVector3 &vect)
// 参数：参数vect为一个矢量
// 功能：求两个矢量的叉乘
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
// 函数：Init()
// 参数：参数x1, y1, z1一个点
// 功能：初始化点
//*/

void CVector3::Init(float x1, float y1, float z1)
{
	x=x1;
	y=y1;
	z=z1;
}

//重载-
CVector3 CVector3::operator -(CVector3 &vect)
{
	CVector3 vResult;              
	
	vResult.x = x - vect.x;    
	vResult.y = y - vect.y;    
	vResult.z = z - vect.z;    
	
	return vResult;                
	

}

//////////////////////////////////////////////////////////////////////////
//函数:operator ==
//参数:一个CVector2类型的点
//功能:重载==运算符，判断两点坐标是否相等
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
//函数:operator -
//参数:一个CVector2类型的点
//功能:重载-运算符，完成二维向量的减法
//////////////////////////////////////////////////////////////////////////
CVector2 CVector2::operator -(CVector2 &vect)
{
	CVector2 result;
	result.x=x-vect.x;
	result.y=y-vect.y;
	return result;
}


//////////////////////////////////////////////////////////////////////////
//函数:Init
//参数:要初始化为的x y坐标值
//功能:初始化二维向量
//////////////////////////////////////////////////////////////////////////
void CVector2::Init(float xpos, float ypos)
{
	x=xpos;
	y=ypos;
}


//////////////////////////////////////////////////////////////////////////
//函数:DistanceFrom
//参数:一个CVector2类型的点
//功能:计算两点间的距离
//////////////////////////////////////////////////////////////////////////
float CVector2::DistanceFrom(CVector2 &p)
{
	return (float)sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));
}

//////构造函数
CVector2::CVector2(float xpos,float ypos)
{
	Init( xpos, ypos);
}
CVector3::CVector3(float x1,float y1,float z1)
{
	Init( x1, y1, z1);
}
