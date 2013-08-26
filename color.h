#ifndef RNG_COLOR_H
#define RNG_COLOR_H
#include "base.h"
//���ڱ�����ɫ������
typedef struct
{
	RNG_Int type;//һ����Ǳ�ʾ���Ҷ��������
	RNG_Real red;//��ɫ����
	RNG_Real green;//��ɫ����
	RNG_Real blue;//��ɫ����
	RNG_Real alpha;//͸���ȷ���
} RNG_Color;

EXPORT_API RNG_Color RNG_Col3(RNG_Real red,RNG_Real green,RNG_Real blue);
EXPORT_API RNG_Color RNG_Col4(RNG_Real red,RNG_Real green,RNG_Real blue,RNG_Real alpha);
EXPORT_API void RNG_ColPrint(RNG_Color color);
#endif
