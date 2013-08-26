#ifndef RNG_VECTOR_H
#define RNG_VECTOR_H

//创建临时的向量对象
EXPORT_API RNG_Vector RNG_Vec(RNG_Real x,RNG_Real y);
//判断两个向量之间的距离
EXPORT_API RNG_Real RNG_VecDist(RNG_Vector a, RNG_Vector b);
//计算两向量的和向量
EXPORT_API RNG_Vector RNG_VecAdd(RNG_Vector a, RNG_Vector b);
//计算两向量的差向量
EXPORT_API RNG_Vector RNG_VecMinus(RNG_Vector a, RNG_Vector b);
//向量求模
EXPORT_API RNG_Real RNG_VecLength(RNG_Vector a);
//将向量单位化
EXPORT_API RNG_Vector RNG_VecUnit(RNG_Vector a);
//求向量的点积
EXPORT_API RNG_Vector RNG_VecDot(RNG_Vector a, RNG_Real b);
//打印向量结果
EXPORT_API void RNG_VecPrint(RNG_Vector a);
#endif // RNG_VECTOR_H
