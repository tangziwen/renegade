#ifndef RNG_INIT_H
#define RNG_INIT_H
#include "base.h"

#define RNG_VERSION "Renegade  ver 0.01"
//��ʼ������
//
//������ʹ�����ú���֮ǰʹ��
EXPORT_API void RNG_Init(const char * title,RNG_Int width,RNG_Int height,RNG_BOOL fullscreen );


//�˳�����
EXPORT_API void RNG_Exit();

//������浱ǰ�İ汾���ַ�����ʾ
EXPORT_API const char * RNG_VerGet();

EXPORT_API void RNG_Wait(RNG_Int ms);
#endif
