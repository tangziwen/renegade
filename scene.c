#include "scene.h"
#include "exception.h"
RNG_Scene * major_scene=NULL;


static SceneNode * get_node_by_sprite(RNG_Scene *ptr,RNG_Sprite * sprite)
{
	SceneNode * tmp =ptr->sprite_list.head;
	SceneNode * result =NULL;
	while(tmp )
		{
			if(tmp->Sprite==sprite)
				{
					result=tmp;
					break;
				}
			tmp=tmp->next;
		}
	return result;
}

EXPORT_API RNG_Event * RNG_EventNew(void (* func)(RNG_Event * self, void * env))
{
	RNG_Event * new_event=malloc(sizeof(RNG_Event));
	new_event->func=func;
	new_event->env=NULL;
	return new_event;
}


/*
创建一个渲染场景，默认的以最后一个被创建的场景作为major场景
*/
EXPORT_API RNG_Scene * RNG_SceneNew()
{
	RNG_Scene * obj=malloc(sizeof(RNG_Scene));
	obj->event_list.head=NULL;
	obj->event_list.tail=NULL;

	obj->sprite_list.head=NULL;
	obj->sprite_list.tail=NULL;
	major_scene=obj;
	return obj;
}

EXPORT_API void  RNG_SceneDispose(RNG_Scene * ptr)
{

	SceneNode * tmp;
	tmp=ptr->sprite_list.head;
	while(tmp)
		{
			tmp=tmp->next;
			free(tmp->pre);
		}
	free(ptr);
}


static SceneNode* CreateNode(RNG_Sprite * sprite,int layer)
{
	SceneNode * new_node =malloc(sizeof(SceneNode));
	new_node->Sprite=sprite;
	new_node->next=NULL;
	new_node->pre=NULL;
	new_node->layer=layer;
	new_node->is_removed=RNG_FALSE;
	new_node->is_touched=RNG_FALSE;
	new_node->event=NULL;
	new_node->type=NODE_SPRITE;
	return new_node;
}

EXPORT_API RNG_Sprite* RNG_SpriteNew(RNG_Scene * ptr ,RNG_Vector pos,RNG_Real width,RNG_Real height,RNG_Texture * texture,RNG_Int layer,void (*fun)(RNG_Sprite * self))
{

	RNG_Sprite * new_sprite= RNG_SpriteCreate(pos,width,height,texture,fun);
	SceneNode * new_node =CreateNode(new_sprite,layer);
	SceneNode * tmp=ptr->sprite_list.head;
	if(!tmp)//场景之中没有精灵的情况
		{
			ptr->sprite_list.head=new_node;
			new_node->z_order=0;
			ptr->sprite_list.tail=new_node;
		}
	else
		{
			while( tmp&&  tmp->layer <=new_node->layer )
				{
					tmp=tmp->next;
				}
			if(tmp)
				{
					SceneNode * pre=tmp->pre;
					if(pre)
						{
							pre->next=new_node;
							if(new_node->layer==pre->layer)
								{
									new_node->z_order=pre->z_order+=1;
								}

						}
					else
						{
							ptr->sprite_list.head=new_node;
							new_node->z_order=0;
						}
					tmp->pre=new_node;
					new_node->pre=pre;
					new_node->next=tmp;
				}
			else
				{
					new_node->pre=ptr->sprite_list.tail;
					if(ptr->sprite_list.tail->layer==new_node->layer)
						{
							new_node->z_order=ptr->sprite_list.tail->z_order+1;
						}
					ptr->sprite_list.tail->next=new_node;
					ptr->sprite_list.tail=new_node;
				}
		}
	return new_sprite;
}

EXPORT_API void RNG_EventKill(RNG_Scene * ptr, RNG_Event *event)
{
	SceneNode * tmp =ptr->event_list.head;
	while(tmp)
		{
			if(tmp->event==event)
				{
					tmp->is_removed=RNG_TRUE;
					return;
				}
			tmp=tmp->next;
		}
}

EXPORT_API void RNG_EventRemove(RNG_Event * event)
{
	free(event);
}
EXPORT_API void  RNG_SceneAddEvent(RNG_Scene * ptr,RNG_Event * event,void * env)
{

	SceneNode * new_node =CreateNode(NULL,0);
	event->env=env;
	new_node->type=NODE_EVENT;
	new_node->event=event;

	if(!(ptr->event_list.tail))
		{

			ptr->event_list.head=ptr->event_list.tail=new_node;

		}
	else
		{
			ptr->event_list.tail->next=new_node;
			new_node->pre=ptr->event_list.tail;
			ptr->event_list.tail=new_node;

		}

}
EXPORT_API void RNG_SpriteRemove(RNG_Scene * ptr ,RNG_Sprite * Sprite)
{

	SceneNode * tmp =ptr->sprite_list.head;
	while(tmp)
		{
			if(tmp->Sprite==Sprite)
				{
					tmp->is_removed=RNG_TRUE;
					return;
				}
			tmp=tmp->next;
		}
}


EXPORT_API void RNG_SceneActivate(RNG_Scene * ptr )
{
	major_scene=ptr;
}

EXPORT_API RNG_Scene * RNG_SceneGetAcitvied()
{
	return major_scene;
}

void RNG_SceneSwapOrder(RNG_Scene  *ptr, RNG_Sprite * sp1,RNG_Sprite * sp2)
{
	SceneNode * n1=get_node_by_sprite(ptr,sp1);
	SceneNode * n2= get_node_by_sprite(ptr,sp2);
	if(n1 && n2 )
		{
			if(n1->layer==n2->layer)
				{
					SceneNode tmp =(*n2);
					n2->Sprite=n1->Sprite;
					n2->z_order=n1->z_order;
					n1->Sprite=tmp.Sprite;
					n1->z_order=tmp.z_order;
				}
			else
				{
					exception_raise("两精灵不在同一层上");
				}
		}
	else
		{
			exception_raise("无效的精灵");
		}
}
LOCAL_API void SceneRenderSprite(RNG_Scene * ptr)
{
	if(!ptr) return;
	SceneNode * tmp=ptr->sprite_list.head;
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glEnable(GL_TEXTURE_2D);
	int pre_texture=0;
	while(tmp)
		{
			if(tmp->Sprite&& tmp->Sprite->is_visible)
				{
					RNG_SpriteRender(tmp->Sprite,pre_texture);
					pre_texture=RNG_TextureGetGLHandle(tmp->Sprite->texture);
				}

			if(tmp->is_removed)
				{
					SceneNode * pre=tmp->pre;
					SceneNode * next=tmp->next;
					if(pre)
						{
							pre->next=next;
						}
					else
						{
							ptr->sprite_list.head=next;
						}
					if(next)
						{
							next->pre=pre;
						}
					else
						{
							ptr->sprite_list.tail=pre;
						}
					SceneNode *old =tmp;
					tmp=tmp->next;
					SpriteKill(old->Sprite);
					free(old);
					continue;
				}

			tmp=tmp->next;
		}
}

LOCAL_API void SceneHandleEvent(RNG_Scene * ptr)
{
	if(!ptr) return;
	SceneNode * tmp=ptr->event_list.head;
	while(tmp)
		{
			tmp->event->func(tmp->event,tmp->event->env);

			if(tmp->is_removed)
				{
					SceneNode * pre=tmp->pre;
					SceneNode * next=tmp->next;
					if(pre)
						{
							pre->next=next;
						}
					else
						{
							ptr->event_list.head=next;
						}
					if(next)
						{
							next->pre=pre;
						}
					else
						{
							ptr->event_list.tail=pre;
						}
					SceneNode *old =tmp;
					tmp=tmp->next;
					free(old);
					continue;
				}
			tmp=tmp->next;
		}
}


LOCAL_API void SceneRender(RNG_Scene * ptr)
{
	SceneRenderSprite(ptr);
	SceneHandleEvent(ptr);
}

//已知矩阵以及经过变化后的向量,求原向量(用于2d)
LOCAL_API RNG_Vector m3dReTransformVector2f(RNG_Vector vOut, float m[16])
{
	RNG_Vector v;
	v.y=(m[1]*vOut.x-m[0]*vOut.y-m[12]*m[1]+m[13]*m[0])/(m[4]*m[1]-m[5]*m[0]);
	v.x=(vOut.x-m[4]*v.y-m[12])/(m[0]);
	return v;
}

LOCAL_API void RNG_SceneTriggerTouch(RNG_Scene * ptr,RNG_Vector mouse_pos)
{
	if(!ptr) return;
	SceneNode * tmp=ptr->sprite_list.tail;
	while(tmp)
		{
			if(tmp->Sprite)
				{
					RNG_Vector pos= m3dReTransformVector2f(mouse_pos,tmp->Sprite->matrix);
					if(pos.x>=0 &&pos.x<=tmp->Sprite->width && pos.y>=0 && pos.y<=tmp->Sprite->height )
						{
							tmp->is_touched=RNG_TRUE;
							if(tmp->Sprite->OnTouch)
								{
									tmp->Sprite->OnTouch(tmp->Sprite);
								}
							break;
						}
				}

			tmp=tmp->pre;
		}
}

LOCAL_API void SceneTriggerRealease(RNG_Scene * ptr,RNG_Vector mouse_pos)
{
	if(!ptr) return;
	SceneNode * tmp=ptr->sprite_list.tail;
	while(tmp)
		{
			if(tmp->Sprite)
				{
					RNG_Vector pos= m3dReTransformVector2f(mouse_pos,tmp->Sprite->matrix);
					if(pos.x>=0 &&pos.x<=tmp->Sprite->width && pos.y>=0 && pos.y<=tmp->Sprite->height )
						{
							if(tmp->is_touched==RNG_TRUE)
								{
									if(tmp->Sprite->OneRelease)
										{
											tmp->Sprite->OneRelease(tmp->Sprite);
										}
									tmp->is_touched=RNG_FALSE;
								}
							break;
						}
				}

			tmp=tmp->pre;
		}
}
