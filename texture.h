#ifndef RNG_TEXTURE_H
#define RNG_TEXTURE_H
#include "base.h"
#include "color.h"
typedef struct
{
	GLuint texture_handle;
}
RNG_Texture;

EXPORT_API RNG_Texture * RNG_TextureCreate(const char * file_name);

EXPORT_API void  RNG_TextureDispose(RNG_Texture * ptr);

EXPORT_API RNG_Texture * RNG_TextureCreateFromBuffer(char * file_buffer,int buffer_size);

//获得纹理的OPENGL对象的索引
EXPORT_API RNG_Int  RNG_TextureGetGLHandle(RNG_Texture * ptr);

#endif
