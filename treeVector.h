//treeVector.h:
//			������
////////////////////////////////////////////////////////////////////////////////////////

#ifndef __VECTORLIB_H_INCLUDED__
#define __VECTORLIB_H_INCLUDED__

#include <math.h>

/*************************** �궨��ͳ��� ***************************/
// returns a number ranging from -1.0 to 1.0
#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)
#define Clamp(x, min, max)  x = (x<min  ? min : x<max ? x : max);
#define SQUARE(x)  (x)*(x)

//struct: ����
struct vector3_t
{
  vector3_t(float x, float y, float z) : x(x), y(y), z(z) {}
  vector3_t(const vector3_t &v) : x(v.x), y(v.y), z(v.z) {}
  vector3_t() : x(0.0f), y(0.0f), z(0.0f) {}

  vector3_t& operator=(const vector3_t &rhs)	//����=
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }
 
  vector3_t operator+(const vector3_t &rhs) const // ����+���������
  {
    return vector3_t(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  vector3_t operator-(const vector3_t &rhs) const //����-���������
  {
    return vector3_t(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  vector3_t operator*(const float scalar) const   //����*����������������
  {
    return vector3_t(x * scalar, y * scalar, z * scalar);
  }

  float operator*(const vector3_t &rhs) const	  //����*�������ĵ��
  {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

  vector3_t operator^(const vector3_t &rhs) const  //����^�������Ĳ��
  {
    return vector3_t(y * rhs.z - rhs.y * z, rhs.x * z - x * rhs.z, x * rhs.y - rhs.x * y);
  }

  float& operator[](int index)						//����[]����������ĳһ����
  {
    return v[index];
  }

  float Length()									//�����ĳ���
  {
    float length = (float)sqrt(SQUARE(x) + SQUARE(y) + SQUARE(z));
    return (length != 0.0f) ? length : 1.0f;
  }

  vector3_t Normalize()								//�����ĵ�λ��
  {
    *this = *this * (1.0f/Length());
    return *this;
  }

  union								//�����壬�����Ĳ�ͬ��ʽ
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