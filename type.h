#ifndef RNG_TYPE_H
#define RNG_TYPE_H
#include "base.h"
#include "color.h"
//RNGԪ����
typedef struct
{
	RNG_Int type;
} RNG_Meta;
//��ͷ�ļ�������RNG���õĶ���������صĲ���

#define RNG_TYPE_COLOR  0


EXPORT_API RNG_Int RNG_GetType(void * ptr);

#endif
