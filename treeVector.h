//treeVector.h:
//			向量类
////////////////////////////////////////////////////////////////////////////////////////

#ifndef __VECTORLIB_H_INCLUDED__
#define __VECTORLIB_H_INCLUDED__

#include <math.h>

/*************************** 宏定义和常量 ***************************/
// returns a number ranging from -1.0 to 1.0
#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)
#define Clamp(x, min, max)  x = (x<min  ? min : x<max ? x : max);
#define SQUARE(x)  (x)*(x)

//struct: 向量
struct vector3_t
{
  vector3_t(float x, float y, float z) : x(x), y(y), z(z) {}
  vector3_t(const vector3_t &v) : x(v.x), y(v.y), z(v.z) {}
  vector3_t() : x(0.0f), y(0.0f), z(0.0f) {}

  vector3_t& operator=(const vector3_t &rhs)	//重载=
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }
 
  vector3_t operator+(const vector3_t &rhs) const // 重载+，向量相加
  {
    return vector3_t(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  vector3_t operator-(const vector3_t &rhs) const //重载-，向量相减
  {
    return vector3_t(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  vector3_t operator*(const float scalar) const   //重载*，向量按比例扩大
  {
    return vector3_t(x * scalar, y * scalar, z * scalar);
  }

  float operator*(const vector3_t &rhs) const	  //重载*，向量的点乘
  {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

  vector3_t operator^(const vector3_t &rhs) const  //重载^，向量的叉乘
  {
    return vector3_t(y * rhs.z - rhs.y * z, rhs.x * z - x * rhs.z, x * rhs.y - rhs.x * y);
  }

  float& operator[](int index)						//重载[]，返回向量某一分量
  {
    return v[index];
  }

  float Length()									//向量的长度
  {
    float length = (float)sqrt(SQUARE(x) + SQUARE(y) + SQUARE(z));
    return (length != 0.0f) ? length : 1.0f;
  }

  vector3_t Normalize()								//向量的单位化
  {
    *this = *this * (1.0f/Length());
    return *this;
  }

  union								//共用体，向量的不同形式
  {
    struct
    {
      float x;
      float y;
      float z;
    };
    float v[3];
  };
};

#endif __VECTORLIB_H_INCLUDED__