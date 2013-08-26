#include"base.h"
#include <math.h>
//创建临时的向量对象
EXPORT_API RNG_Vector RNG_Vec(RNG_Real x,RNG_Real y)
{
	RNG_Vector pos;
	pos.x=x;
	pos.y=y;
	return pos;
}

//判断两个向量之间的距离
EXPORT_API RNG_Real RNG_VecDist(RNG_Vector a, RNG_Vector b)
{
return  sqrt((a.x-b.x) *(a.x-b.x) +(a.y-b.y)*(a.y-b.y));
}

//计算两向量的和向量
EXPORT_API RNG_Vector RNG_VecAdd(RNG_Vector a, RNG_Vector b)
{
	a.x+=b.x;
	a.y+=b.y;
	return a;
}
//计算两向量的差向量
EXPORT_API RNG_Vector RNG_VecMinus(RNG_Vector a, RNG_Vector b)
{
	a.x-=b.x;
	a.y-=b.y;
	return a;
}
//向量求模
EXPORT_API RNG_Real RNG_VecLength(RNG_Vector a)
{
return sqrt((a.x*a.x)+(a.y*a.y ) );
}

//将向量单位化
EXPORT_API RNG_Vector RNG_VecUnit(RNG_Vector a)
{
a.x=a.x/RNG_VecLength(a);
a.y=a.y/RNG_VecLength(a);
return a;
}

//求向量的点积
EXPORT_API RNG_Vector RNG_VecDot(RNG_Vector a, RNG_Real b)
{
a.x*=b;
a.y*=b;
return a;
}

//打印向量结果
EXPORT_API void RNG_VecPrint(RNG_Vector a)
{
printf("X:%g Y:%g\n",a.x,a.y);
}
