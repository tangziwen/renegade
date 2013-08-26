#ifndef RNG_LABEL_H
#define RNG_LABEL_H
#include "color.h"
#include "base.h"
#include <ft2build.h>
#include FT_FREETYPE_H
typedef struct
{
	const char * file_name;
	wchar_t * str;
	FT_Face    face;
	RNG_Int width;
	RNG_Int height;
	RNG_Color  color;
	RNG_Vector offset;
} RNG_Label;

LOCAL_API void RNG_LabelInit();

EXPORT_API RNG_Label * RNG_LabelNew(const  char *file_name);

EXPORT_API void RNG_LabelSetText(RNG_Label * ptr,wchar_t * str);

EXPORT_API void RNG_LabelDraw(RNG_Label * ptr);

EXPORT_API void RNG_LabelSetSize(RNG_Label * ptr,RNG_Int width,RNG_Int height);

EXPORT_API void RNG_LabelDispose(RNG_Label *ptr);

EXPORT_API void RNG_LabelSetColor(RNG_Label *ptr,RNG_Color  color);

EXPORT_API void RNG_LabelSetOffset(RNG_Label *ptr,RNG_Vector offset);
#endif
