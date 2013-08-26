#ifndef RNG_INIT_H
#define RNG_INIT_H
#include "base.h"

#define RNG_VERSION "Renegade  ver 0.01"
//初始化引擎
//
//必须在使用所用函数之前使用
EXPORT_API void RNG_Init(const char * title,RNG_Int width,RNG_Int height,RNG_BOOL fullscreen );


//退出引擎
EXPORT_API void RNG_Exit();

//获得引擎当前的版本的字符串表示
EXPORT_API const char * RNG_VerGet();

EXPORT_API void RNG_Wait(RNG_Int ms);
#endif
