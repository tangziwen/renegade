#include "type.h"
#include "exception.h"
EXPORT_API RNG_Int RNG_GetType(void * ptr)
{
	if(!ptr)
	{
		exception_raise("无效的对象,在RNG_GetType中");
	}
	return ((RNG_Meta* )ptr)->type;
}

