#include "exception.h"
#include "engine.h"
#include "string.h"
#include <time.h>
static int exception_level=RNG_EXCEPTION_SILENT;
static char the_last_error_str[512];
//设置异常的警告级别
//
//警告级别分为三种:
//RNG_EXCEPTION_STRICT :严格型,一遇到异常就中断
//RNG_EXCEPTION_SILENT :默许型,遇到异常仅记录异常的代码号,但是并不会阻挠程序的运行(除非错误是致命的).
//RNG_EXCEPTION_LOG : 与默许型类似,但是额外的讲异常写入rng.log中
EXPORT_API void RNG_ExceptionSetLevel(RNG_Int level)
{
	exception_level=level;
}

//以字符串的方式获得最后一个错误
EXPORT_API const char * RNG_ExceptionGetLast()
{
	return  the_last_error_str;
}

//抛出异常
//
//error_info:错误的描述信息
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
		//确保文件存在
		FILE   *fp;
		fp=fopen("./rng.log", "w");
		fclose(fp);
		//写入异常
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
