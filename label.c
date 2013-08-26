#include "label.h"

static FT_Library  library;
static int texture;
EXPORT_API void RNG_LabelInit()
{
	FT_Init_FreeType( &library );
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

EXPORT_API RNG_Label * RNG_LabelNew(const  char *file_name)
{
	RNG_Label * label =malloc(sizeof(RNG_Label ));
	FT_New_Face( library,file_name  ,0,&(label->face) );
	FT_Set_Pixel_Sizes((label->face),0,128 );
	label->file_name=file_name;
	label->str=NULL;
	label->width=32;
	label->offset.x=0;
	label->offset.y=0;
	label->height=32;
	label->color=RNG_Col4(1,1,1,1);
	return label;
}

EXPORT_API void RNG_LabelSetText(RNG_Label * ptr,wchar_t * str)
{
	ptr->str=str;
}
static void text_draw(FT_Face     face,wchar_t * str,RNG_Int width ,RNG_Int height,RNG_Color  color,RNG_Vector offset)
{
	static GLdouble quad[4][2];
	static GLubyte expanded_data [128*128*4];
	static GLfloat textureCoordinates[4][2];
	glTranslated(offset.x,offset.y,0);
	for(int k=0; str[k]!='\0'; k++)
	{
		//对空格进行特殊处理
		if(str[k]==32)
		{
			for(int i =0; i<128*128*4; i++)
			{
				expanded_data[i]=0;
			}
		}
		else
		{
			FT_Load_Glyph( face, FT_Get_Char_Index( face, str[k]), FT_LOAD_DEFAULT );
			FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL  );
			for(int j=0; j <face->glyph->bitmap.rows; j++)
			{
				for(int i=0; i < face->glyph->bitmap.width; i++)
				{
					if(face->glyph->bitmap.buffer[i + face->glyph->bitmap.width*j])
					{
						expanded_data[4*(i+j*face->glyph->bitmap.width)] = 255;
						expanded_data[4*(i+j*face->glyph->bitmap.width)+1]=255;
						expanded_data[4*(i+j*face->glyph->bitmap.width)+2]=255;
						expanded_data[4*(i+j*face->glyph->bitmap.width)+3]=255;
					}
					else
					{
						expanded_data[4*(i+j*face->glyph->bitmap.width)] = 0;
						expanded_data[4*(i+j*face->glyph->bitmap.width)+1]=0;
						expanded_data[4*(i+j*face->glyph->bitmap.width)+2]=0;
						expanded_data[4*(i+j*face->glyph->bitmap.width)+3]=0;
					}
				}
			}
		}

		//左下
		quad[0][0]=0;
		quad[0][1]=0;
		//右下
		quad[1][0]=width;
		quad[1][1]=0;
		//左上
		quad[2][0]=0;
		quad[2][1]=height;
		//右上
		quad[3][0]=width;
		quad[3][1]=height;
		//左下
		textureCoordinates[0][0]=0;
		textureCoordinates[0][1]=1;
		//右下
		textureCoordinates[1][0]=1;
		textureCoordinates[1][1]=1;

		//左上
		textureCoordinates[2][0]=0;
		textureCoordinates[2][1]=0;

		//右上
		glColor4d(color.red,color.green,color.blue,color.alpha);
		textureCoordinates[3][0]=1;
		textureCoordinates[3][1]=0;
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,face->glyph->bitmap.width,face->glyph->bitmap.rows,0,GL_RGBA,GL_UNSIGNED_BYTE,expanded_data);
		glTranslatef(width,0,0);
		glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinates);
		glVertexPointer(2,GL_DOUBLE,0,quad);
		glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	}
}

EXPORT_API void RNG_LabelDraw(RNG_Label * ptr)
{
	text_draw(ptr->face,ptr->str,ptr->width,ptr->height,ptr->color,ptr->offset);
}


EXPORT_API void RNG_LabelDispose(RNG_Label *ptr)
{
	FT_Done_Face( ptr-> face );
	free(ptr);
}


EXPORT_API void RNG_LabelSetSize(RNG_Label * ptr,RNG_Int width,RNG_Int height)
{
	ptr->width=width;
	ptr->height=height;
}

EXPORT_API void RNG_LabelSetColor(RNG_Label *ptr,RNG_Color  color)
{
	ptr->color=color;
}

EXPORT_API void RNG_LabelSetOffset(RNG_Label *ptr,RNG_Vector offset)
{
	ptr->offset=offset;
}
