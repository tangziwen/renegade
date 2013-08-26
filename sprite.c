#include "sprite.h"
#include "vector.h"
#include <wchar.h>

LOCAL_API RNG_Sprite * RNG_SpriteCreate(RNG_Vector pos ,RNG_Real width,RNG_Real height, RNG_Texture * texture,void (*fun)(RNG_Sprite * self))
{
	RNG_Sprite * obj=malloc(sizeof(RNG_Sprite));
	obj->pos=pos;
	obj->texture=texture;
	obj->action=fun;
	obj->height=height;
	obj->width=width;
	obj->angle=0;
	obj->anchor_pos.x=0.5;
	obj->anchor_pos.y=0.5;
	obj->bottom_x =1;
	obj->bottom_y =1;
	obj->top_x =0;
	obj->top_y =0;
	obj->OnTouch=NULL;
	obj->OneRelease=NULL;
	obj->label=NULL;
	obj->userdata=NULL;
	obj->is_visible=RNG_TRUE;
	obj->color =RNG_Col3(1,1,1);
	obj->scale_factor=RNG_Vec(1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX,obj->matrix);
	return obj;
}
EXPORT_API void   RNG_SpriteSetUsrData(RNG_Sprite * ptr,void * data)
{
	ptr->userdata=data;
}

EXPORT_API RNG_Real RNG_SpriteGetAngle(RNG_Sprite * ptr)
{
	if(!ptr) return 0;
	return ptr->angle;
}
EXPORT_API RNG_Vector   RNG_SpriteGetPos(RNG_Sprite * ptr)
{
	if(ptr)
	{
		return ptr->pos;
	}
	else
	{
		return RNG_Vec(0,0);
	}
}
EXPORT_API void *  RNG_SpriteGetUsrData(RNG_Sprite * ptr)
{
	return ptr->userdata;
}

EXPORT_API RNG_BOOL  RNG_SpriteIsVisible(RNG_Sprite * ptr)
{
	if(!ptr) return RNG_FALSE;
	else
		return ptr->is_visible;
}


EXPORT_API void RNG_SpriteShow(RNG_Sprite * ptr)
{
	if(!ptr) return;
	ptr->is_visible=RNG_TRUE;
}

EXPORT_API void RNG_SpriteHide(RNG_Sprite * ptr)
{
	if(!ptr) return;
	ptr->is_visible=RNG_FALSE;
}

EXPORT_API void RNG_SpriteScale(RNG_Sprite * ptr,RNG_Vector vec)
{
	ptr->scale_factor=vec;
}

EXPORT_API RNG_Vector RNG_SpriteGetScale(RNG_Sprite * ptr)
{
	return ptr->scale_factor;
}

EXPORT_API void RNG_SpriteVisibleToggle(RNG_Sprite * ptr)
{
	if(!ptr) return;
	if(ptr->is_visible)
	{
		ptr->is_visible=RNG_FALSE;
	}
	else
	{
		ptr->is_visible=RNG_TRUE;
	}
}



EXPORT_API void   RNG_SpriteSetPos(RNG_Sprite * ptr,RNG_Vector pos)
{
	ptr->pos=pos;
}


EXPORT_API void   RNG_SpriteTranslate(RNG_Sprite * ptr,RNG_Vector pos)
{
	ptr->pos.x+=pos.x;
	ptr->pos.y+=pos.y;
}

LOCAL_API void SpriteKill(RNG_Sprite * ptr)
{
	if(ptr)
	{
		free(ptr);
	}

}

EXPORT_API void RNG_SpriteMorph(RNG_Sprite * ptr,RNG_Texture * texture)
{
	ptr->texture=texture;
}


EXPORT_API void RNG_SpriteSetAction(RNG_Sprite * ptr,void (*fun)(RNG_Sprite * self))
{
	ptr->action=fun;
}
LOCAL_API void RNG_SpriteRender(RNG_Sprite * ptr,int pre_texture)
{

	GLdouble quad[4][2];


	//左下
	quad[0][0]=0;
	quad[0][1]=0;
	//右下
	quad[1][0]=ptr->width;
	quad[1][1]=0;
	//左上
	quad[2][0]=0;
	quad[2][1]=ptr->height;
	//右上
	quad[3][0]=ptr->width;
	quad[3][1]=ptr->height;
	GLfloat textureCoordinates[4][2];
	//左下
	textureCoordinates[0][0]=ptr->top_x;
	textureCoordinates[0][1]=ptr->bottom_y;
	//右下
	textureCoordinates[1][0]=ptr->bottom_x;
	textureCoordinates[1][1]=ptr->bottom_y;

	//左上
	textureCoordinates[2][0]=ptr->top_x;
	textureCoordinates[2][1]=ptr->top_y;

	//右上
	textureCoordinates[3][0]=ptr->bottom_x;
	textureCoordinates[3][1]=ptr->top_y;
	glPushMatrix();
	glTranslated((ptr->pos.x+ptr->width*ptr->anchor_pos.x),(ptr->pos.y+ptr->height*ptr->anchor_pos.y),0);
	glRotated(ptr->angle,0,0,1);
	glScaled(ptr->scale_factor.x,ptr->scale_factor.y,1);
	glTranslated(-1*(ptr->pos.x+ptr->width*ptr->anchor_pos.x),-1*(ptr->pos.y+ptr->height*ptr->anchor_pos.y),0);
	glTranslated(ptr->pos.x+ptr->width*(0.5-ptr->anchor_pos.x),ptr->pos.y+ptr->height*(0.5-ptr->anchor_pos.y),0);

	if(ptr->texture)
	{
		if(ptr->texture->texture_handle)
		{
			glColor4d(ptr->color.red,ptr->color.green,ptr->color.blue,ptr->color.alpha);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			glBindTexture(GL_TEXTURE_2D,ptr->texture->texture_handle);
			glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinates);
			glVertexPointer(2,GL_DOUBLE,0,quad);
			glDrawArrays(GL_TRIANGLE_STRIP,0,4);
		}
	}
	if(ptr->label)
	{
		RNG_LabelDraw(ptr->label);
	}
	glGetFloatv(GL_MODELVIEW_MATRIX,ptr->matrix);
	glPopMatrix();
	if(ptr->action)
	{
		ptr->action(ptr);
	}
}


EXPORT_API void   RNG_SpriteReSize(RNG_Sprite * ptr,RNG_Real width,RNG_Real height )
{
	ptr->width=width;
	ptr->height=height;
}

EXPORT_API void RNG_SpriteSetAnchor(RNG_Sprite * ptr,RNG_Vector vec)
{
	if(!ptr) return;
	ptr->anchor_pos=vec;
}

EXPORT_API RNG_Vector RNG_SpriteGetAnchor(RNG_Sprite * ptr)
{
	if(!ptr) return RNG_Vec(0.5,0.5);
	return ptr->anchor_pos;
}

EXPORT_API void RNG_SpriteRotate(RNG_Sprite * ptr,RNG_Real angle)
{
	ptr->angle=angle;
}
EXPORT_API void  RNG_SpriteSetRenderRect(RNG_Sprite * ptr,RNG_Real bottom_x,RNG_Real bottom_y,RNG_Real top_x,RNG_Real top_y)
{
	ptr->bottom_x=bottom_x;
	ptr->bottom_y=bottom_y;
	ptr->top_x=top_x;
	ptr->top_y=top_y;
}


EXPORT_API void RNG_SpriteOnTouch(RNG_Sprite * ptr,void (*fun)(RNG_Sprite * self))
{
	ptr->OnTouch=fun;
}


EXPORT_API void RNG_SpriteOnRelease(RNG_Sprite * ptr,void (*fun)(RNG_Sprite * self))
{
	ptr->OneRelease=fun;
}

EXPORT_API void RNG_SpriteSetColor(RNG_Sprite * ptr,RNG_Color color)
{
	ptr->color=color;
}

void RNG_SpriteAddLabel(RNG_Sprite * ptr,RNG_Label * label)
{
	ptr->label=label;
}
