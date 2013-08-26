#ifndef RNG_EXCEPTION_H
#define RNG_EXCEPTION_H
#include "base.h"

#define RNG_EXCEPTION_STRICT  0
#define RNG_EXCEPTION_SILENT 1
#define RNG_EXCEPTION_LOG 2

//设置异常的警告级别
//
//警告级别分为三种:
//RNG_EXCEPTION_STRICT :严格型,一遇到异常就中断
//RNG_EXCEPTION_SILENT :默许型,遇到异常仅记录异常(可被覆盖的),但是并不会阻挠程序的运行(除非错误是致命的).
//RNG_EXCEPTION_LOG : 与默许型类似,但是额外的讲异常写入rng.log中
EXPORT_API void RNG_ExceptionSetLevel(RNG_Int level);

//以字符串的方式获得最后一个错误
EXPORT_API const char * RNG_ExceptionGetLast();

//抛出异常
//
//error_info:错误的描述信息
LOCAL_API void exception_raise(const char * error_info);
#endif
