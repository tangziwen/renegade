#ifndef RNG_TYPE_H
#define RNG_TYPE_H
#include "base.h"
#include "color.h"
//RNG元类型
typedef struct
{
	RNG_Int type;
} RNG_Meta;
//该头文件描述了RNG内置的对象类型相关的操作

#define RNG_TYPE_COLOR  0


EXPORT_API RNG_Int RNG_GetType(void * ptr);

#endif
