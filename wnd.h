#ifndef RNG_WND_H
#define RNG_WND_H
#include "base.h"
#include "color.h"



//创建一个窗体
//
//title:窗体的标题字符串
//width:窗体的宽度
//height:窗体的高度
LOCAL_API void RNG_WndCreate(const char * title,RNG_Int width,RNG_Int height,RNG_BOOL fullscreen );


//开始渲染窗体
//
//func是一个回调函数,每一帧都确保被执行一次
//这里面包含了一个循环,将不断的渲染窗体,直至引擎被终结
EXPORT_API void RNG_WndRender(void(* func)( ));

EXPORT_API void RNG_SetCallBack(void (* func)() );

//设置窗体的背景色
//
//ptr 指向一个颜色对象的指针
EXPORT_API void RNG_WndSetBG(RNG_Color  ptr);

//设置窗体全屏与否
//
//fullscreen:
//	RNG_TRUE-全屏
//	RNG_FALSE-窗体化
EXPORT_API void RNG_WndSetFullscreen(RNG_BOOL fullscreen );


//设置窗体的新分辨率
//
//在窗体模式下,分辨率就等同于窗体的尺寸
EXPORT_API void RNG_WndSetRes(int width ,int height );


//设置窗体的标题
//
//new_title:窗体新标题的字符串表示
EXPORT_API void RNG_WndSetTitle(const char * new_title );


//设置在可视区域内是否显示鼠标
//
//is_show::
//	RNG_TRUE显示
//	RNG_FALSE不显示
EXPORT_API void RNG_WndSetCursor(RNG_BOOL is_show);


//获取上一帧的渲染周期
EXPORT_API RNG_Real RNG_GetDuration();


extern GLuint current_texture_ID;
#endif
