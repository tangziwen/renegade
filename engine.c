#include "engine.h"
#include "exception.h"
#include "label.h"
//初始化引擎
//
//必须在使用所用函数之前使用
EXPORT_API void RNG_Init(const char * title,RNG_Int width,RNG_Int height,RNG_BOOL fullscreen )
{
	if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)==-1))
	{
		exception_raise("引擎无法初始化");
	}
	RNG_LabelInit();
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	RNG_WndCreate(title,width,height,fullscreen);
	printf("the opengl version is %s\n",glGetString(GL_VERSION));
}



//退出引擎
EXPORT_API void RNG_Exit()
{
	SDL_Quit();
}


EXPORT_API void RNG_Wait(RNG_Int ms)
{
SDL_Delay(ms);
}

//获得引擎当前的版本的字符串表示
EXPORT_API const char * RNG_VerGet()
{
	return RNG_VERSION;
}
