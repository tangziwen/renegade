#ifndef RNG_SCENE_H
#define RNG_SCENE_H
#include "base.h"
#include "sprite.h"
#define NODE_EVENT 0
#define NODE_SPRITE 1
typedef struct event_t
{
void *env;
void (*func)(struct event_t *self, void * env);
} RNG_Event;
typedef struct node_t
{
	RNG_Int layer;
	RNG_Int z_order;
	struct node_t *next;
	struct node_t *pre;
	RNG_Sprite * Sprite;
	RNG_BOOL is_removed;
	RNG_BOOL is_touched;
	RNG_Event * event;
	int type;
} SceneNode;

typedef struct
{
	struct
	{
	SceneNode* head;
	SceneNode* tail;
	}sprite_list;
	struct
	{
	SceneNode* head;
	SceneNode* tail;
	}event_list;
} RNG_Scene;

/*
创建一个渲染场景，默认的以最后一个被创建的场景作为major场景
*/
EXPORT_API RNG_Scene * RNG_SceneNew();

EXPORT_API void  RNG_SceneDispose(RNG_Scene * ptr);

EXPORT_API RNG_Sprite* RNG_SpriteNew(RNG_Scene * ptr ,RNG_Vector pos,RNG_Real width,RNG_Real height,RNG_Texture * texture,RNG_Int layer,void (*fun)(RNG_Sprite * self));

EXPORT_API void RNG_SpriteRemove(RNG_Scene * ptr ,RNG_Sprite * Sprite);

EXPORT_API void RNG_SceneActivate(RNG_Scene * ptr );


EXPORT_API void RNG_SceneSwapOrder(RNG_Scene  *ptr, RNG_Sprite * sp1,RNG_Sprite * sp2);

EXPORT_API void  RNG_SceneAddEvent(RNG_Scene * ptr,RNG_Event * event,void *env);

EXPORT_API void RNG_EventKill(RNG_Scene * ptr, RNG_Event *event);

EXPORT_API void RNG_EventRemove(RNG_Event * event);

EXPORT_API RNG_Scene * RNG_SceneGetAcitvied();

EXPORT_API RNG_Event * RNG_EventNew(void (* func)(RNG_Event * self, void * env));

LOCAL_API void SceneRender(RNG_Scene * ptr);

LOCAL_API void RNG_SceneTriggerTouch(RNG_Scene * ptr,RNG_Vector mouse_pos);

LOCAL_API void SceneTriggerRealease(RNG_Scene * ptr,RNG_Vector mouse_pos);


extern RNG_Scene * major_scene;
#endif
