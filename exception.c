#include "exception.h"
#include "engine.h"
#include "string.h"
#include <time.h>
static int exception_level=RNG_EXCEPTION_SILENT;
static char the_last_error_str[512];
//�����쳣�ľ��漶��
//
//���漶���Ϊ����:
//RNG_EXCEPTION_STRICT :�ϸ���,һ�����쳣���ж�
//RNG_EXCEPTION_SILENT :Ĭ����,�����쳣����¼�쳣�Ĵ����,���ǲ��������ӳ��������(���Ǵ�����������).
//RNG_EXCEPTION_LOG : ��Ĭ��������,���Ƕ���Ľ��쳣д��rng.log��
EXPORT_API void RNG_ExceptionSetLevel(RNG_Int level)
{
	exception_level=level;
}

//���ַ����ķ�ʽ������һ������
EXPORT_API const char * RNG_ExceptionGetLast()
{
	return  the_last_error_str;
}

//�׳��쳣
//
//error_info:�����������Ϣ
LOCAL_API void exception_raise(const char * error_info)
{
	strcpy(the_last_error_str,error_info);
	switch(exception_level)
	{
	case RNG_EXCEPTION_SILENT:
		break;
	case RNG_EXCEPTION_STRICT:
		fprintf(stderr,"%s\n",the_last_error_str);
you		exit(EXIT_FAILURE);
		break;
	case RNG_EXCEPTION_LOG:
	{
		//ȷ���ļ�����
		FILE   *fp;
		fp=fopen("./rng.log", "w");
		fclose(fp);
		//д���쳣
		fp=fopen("./rng.log", "a");
		time_t timep;
		time(&timep);
		fprintf(fp,"%s %s",RNG_VerGet(),asctime(gmtime(&timep)));
		fprintf(fp,"%s\n",the_last_error_str);
		fclose(fp);
	}
	break;
	}
}
