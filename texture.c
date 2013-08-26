#include "texture.h"
#include "SOIL.h"

extern GLuint current_texture_ID;
EXPORT_API RNG_Texture * RNG_TextureCreate(const char * file_name)
{

	RNG_Texture * obj= malloc(sizeof(RNG_Texture));
	obj->texture_handle= SOIL_load_OGL_texture
			     (
				     file_name,
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_POWER_OF_TWO
			     );
	return obj;
}

EXPORT_API RNG_Texture * RNG_TextureCreateFromBuffer(char * file_buffer,int buffer_size)
{
	RNG_Texture * obj= malloc(sizeof(RNG_Texture));
	obj->texture_handle= SOIL_load_OGL_texture_from_memory
			     (
				     file_buffer,
				     buffer_size ,
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_POWER_OF_TWO
			     );
	return obj;
}

EXPORT_API void  RNG_TextureDispose(RNG_Texture * ptr)
{
	glDeleteTextures(1,&(ptr->texture_handle));
	free(ptr);
}

//获得纹理的OPENGL对象的索引
EXPORT_API RNG_Int  RNG_TextureGetGLHandle(RNG_Texture * ptr)
{
	if(ptr)
	{
		return ptr->texture_handle;
	}
	else
	{
		return -1;
	}
}
