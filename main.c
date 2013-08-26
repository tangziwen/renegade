#include <stdio.h>
#include <stdlib.h>
#include "renegade.h"
#include <time.h>
#include <GL/glew.h>
#define WINDOW_SIZE_WIDTH 800
#define  WINDOW_SIZE_HEIGHT 600
extern int shader_program;
int main()
{
	RNG_Init("renegade test",WINDOW_SIZE_WIDTH,WINDOW_SIZE_HEIGHT,RNG_FALSE);
	RNG_Scene * scene =RNG_SceneNew();
	RNG_Texture * rabbit=RNG_TextureCreate("zazaka.png");
	RNG_Texture * back_ground_texture=RNG_TextureCreate("background.jpg");



	RNG_Sprite * test=RNG_SpriteNew(scene,RNG_Vec(100,100),200,200,rabbit,2,NULL);
	RNG_Sprite * background =RNG_SpriteNew(scene,RNG_Vec(0,0),WINDOW_SIZE_WIDTH,WINDOW_SIZE_HEIGHT,back_ground_texture,1,NULL);
	RNG_SpriteRotate(test,90);
	RNG_WndRender(NULL);
	RNG_Exit();
	return 0;
}

