#ifndef RNG_COLOR_H
#define RNG_COLOR_H
#include "base.h"
//用于保存颜色的类型
typedef struct
{
	RNG_Int type;//一个标记表示当且对象的类型
	RNG_Real red;//红色分量
	RNG_Real green;//绿色分量
	RNG_Real blue;//蓝色分量
	RNG_Real alpha;//透明度分量
} RNG_Color;

EXPORT_API RNG_Color RNG_Col3(RNG_Real red,RNG_Real green,RNG_Real blue);
EXPORT_API RNG_Color RNG_Col4(RNG_Real red,RNG_Real green,RNG_Real blue,RNG_Real alpha);
EXPORT_API void RNG_ColPrint(RNG_Color color);
#endif
