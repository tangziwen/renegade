#include "event.h"
extern void (*RNG_OnMouseDownHandler)(RNG_Vector pos)=NULL;

extern void (*RNG_OnMouseRelaeseHandler)(RNG_Vector pos)=NULL;
//获取某一键位的状态
EXPORT_API RNG_Int RNG_GetKeyState(RNG_Key key_code)
{
	Uint8 *keystate = SDL_GetKeyState(NULL);
	return keystate[key_code];
}


//获得鼠标某个键是否被按下
//
//返回当前被按下的鼠标按键
//abs_pos 鼠标的绝对坐标
//re_pos 鼠标的相对坐标
EXPORT_API RNG_MouseState RNG_GetMouseState(RNG_Vector * abs_pos,RNG_Vector * re_pos)
{
	int mouse_state= RNG_MOUSE_NONE;
	int x,y,relative_x,relative_y;
	int result =SDL_GetMouseState(&x, &y);
	SDL_Surface * surface=SDL_GetVideoSurface();
	y=surface->h-y;//与opengl的座标系保持一致。所以y轴的值要翻转
	SDL_GetRelativeMouseState(&relative_x,&relative_y);
	if(result &SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		mouse_state= RNG_MOUSE_LEFT;
	}
	else
	{
		if(result &SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			mouse_state= RNG_MOUSE_RIGHT;
		}
	}
	if(abs_pos)
	{
		abs_pos->x=(RNG_Real)x;
		abs_pos->y=(RNG_Real)y;
	}
	if(re_pos)
	{
		re_pos->x=relative_x;
		re_pos->y=relative_y;
	}
	return mouse_state;
}
EXPORT_API void RNG_OnMouseDown(void (*func)(RNG_Vector pos))
{
	RNG_OnMouseDownHandler=func;
}


EXPORT_API void RNG_OnMouseRealse(void (*func)(RNG_Vector pos))
{
	RNG_OnMouseRelaeseHandler=func;
}
