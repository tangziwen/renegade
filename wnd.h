#ifndef RNG_WND_H
#define RNG_WND_H
#include "base.h"
#include "color.h"



//����һ������
//
//title:����ı����ַ���
//width:����Ŀ��
//height:����ĸ߶�
LOCAL_API void RNG_WndCreate(const char * title,RNG_Int width,RNG_Int height,RNG_BOOL fullscreen );


//��ʼ��Ⱦ����
//
//func��һ���ص�����,ÿһ֡��ȷ����ִ��һ��
//�����������һ��ѭ��,�����ϵ���Ⱦ����,ֱ�����汻�ս�
EXPORT_API void RNG_WndRender(void(* func)( ));

EXPORT_API void RNG_SetCallBack(void (* func)() );

//���ô���ı���ɫ
//
//ptr ָ��һ����ɫ�����ָ��
EXPORT_API void RNG_WndSetBG(RNG_Color  ptr);

//���ô���ȫ�����
//
//fullscreen:
//	RNG_TRUE-ȫ��
//	RNG_FALSE-���廯
EXPORT_API void RNG_WndSetFullscreen(RNG_BOOL fullscreen );


//���ô�����·ֱ���
//
//�ڴ���ģʽ��,�ֱ��ʾ͵�ͬ�ڴ���ĳߴ�
EXPORT_API void RNG_WndSetRes(int width ,int height );


//���ô���ı���
//
//new_title:�����±�����ַ�����ʾ
EXPORT_API void RNG_WndSetTitle(const char * new_title );


//�����ڿ����������Ƿ���ʾ���
//
//is_show::
//	RNG_TRUE��ʾ
//	RNG_FALSE����ʾ
EXPORT_API void RNG_WndSetCursor(RNG_BOOL is_show);


//��ȡ��һ֡����Ⱦ����
EXPORT_API RNG_Real RNG_GetDuration();


extern GLuint current_texture_ID;
#endif
