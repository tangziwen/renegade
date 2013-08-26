#ifndef RNG_Sprite_H
#define RNG_Sprite_H
#include "base.h"
#include "texture.h"
#include "label.h"
typedef struct RNG_Sprite_t
{
	RNG_Texture * texture;
	RNG_Vector  pos;
	RNG_Real width;
	RNG_Real height;
	RNG_Real angle;
	RNG_Vector anchor_pos;
	RNG_BOOL is_visible;
	void (*action)(struct RNG_Sprite_t * self);
	void (* OnTouch)(struct RNG_Sprite_t * self);
	void (* OneRelease)(struct RNG_Sprite_t * self);
	float matrix[16];
	RNG_Real bottom_x;
	RNG_Real bottom_y;
	RNG_Real top_x;
	RNG_Real top_y;
	RNG_Vector scale_factor;
	RNG_Label * label;
	RNG_Color  color;
	void * userdata;
} RNG_Sprite;



EXPORT_API void   RNG_SpriteSetPos(RNG_Sprite * ptr,RNG_Vector pos);

EXPORT_API void   RNG_SpriteReSize(RNG_Sprite * ptr,RNG_Real width,RNG_Real height );

EXPORT_API void   RNG_SpriteTranslate(RNG_Sprite * ptr,RNG_Vector pos);

EXPORT_API RNG_Vector   RNG_SpriteGetPos(RNG_Sprite * ptr);

EXPORT_API void RNG_SpriteMorph(RNG_Sprite * ptr,RNG_Texture * texture);

EXPORT_API void RNG_SpriteSetAction(RNG_Sprite * ptr,void (*fun)(RNG_Sprite * self));

EXPORT_API void RNG_SpriteRotate(RNG_Sprite * ptr,RNG_Real angle);

EXPORT_API void RNG_SpriteOnTouch(RNG_Sprite * ptr,void (*fun)(RNG_Sprite * self));

EXPORT_API void  RNG_SpriteOnRelease(RNG_Sprite * ptr,void (*fun)(RNG_Sprite * self));

EXPORT_API void  RNG_SpriteSetRenderRect(RNG_Sprite * ptr,RNG_Real bottom_x,RNG_Real bottom_y,RNG_Real top_x,RNG_Real top_y);

EXPORT_API void RNG_SpriteAddLabel(RNG_Sprite * ptr,RNG_Label * label);

EXPORT_API void RNG_SpriteSetColor(RNG_Sprite * ptr,RNG_Color  color);

EXPORT_API void   RNG_SpriteSetUsrData(RNG_Sprite * ptr,void * data);

EXPORT_API void *  RNG_SpriteGetUsrData(RNG_Sprite * ptr);

EXPORT_API RNG_Real RNG_SpriteGetAngle(RNG_Sprite * ptr);

EXPORT_API void RNG_SpriteShow(RNG_Sprite * ptr);

EXPORT_API void RNG_SpriteHide(RNG_Sprite * ptr);

EXPORT_API void RNG_SpriteVisibleToggle(RNG_Sprite * ptr);

EXPORT_API void RNG_SpriteScale(RNG_Sprite * ptr,RNG_Vector vec);

EXPORT_API RNG_Vector RNG_SpriteGetScale(RNG_Sprite * ptr);

EXPORT_API void RNG_SpriteSetAnchor(RNG_Sprite * ptr,RNG_Vector vec);

EXPORT_API RNG_Vector RNG_SpriteGetAnchor(RNG_Sprite * ptr);

LOCAL_API void SpriteKill(RNG_Sprite * ptr);

LOCAL_API void RNG_SpriteRender(RNG_Sprite * ptr,int pre_texture);

LOCAL_API RNG_Sprite * RNG_SpriteCreate(RNG_Vector pos ,RNG_Real width,RNG_Real height, RNG_Texture * texture,void (*fun)(RNG_Sprite * self));
#endif
