#ifndef RNG_EXCEPTION_H
#define RNG_EXCEPTION_H
#include "base.h"

#define RNG_EXCEPTION_STRICT  0
#define RNG_EXCEPTION_SILENT 1
#define RNG_EXCEPTION_LOG 2

//�����쳣�ľ��漶��
//
//���漶���Ϊ����:
//RNG_EXCEPTION_STRICT :�ϸ���,һ�����쳣���ж�
//RNG_EXCEPTION_SILENT :Ĭ����,�����쳣����¼�쳣(�ɱ����ǵ�),���ǲ��������ӳ��������(���Ǵ�����������).
//RNG_EXCEPTION_LOG : ��Ĭ��������,���Ƕ���Ľ��쳣д��rng.log��
EXPORT_API void RNG_ExceptionSetLevel(RNG_Int level);

//���ַ����ķ�ʽ������һ������
EXPORT_API const char * RNG_ExceptionGetLast();

//�׳��쳣
//
//error_info:�����������Ϣ
LOCAL_API void exception_raise(const char * error_info);
#endif
