#include "type.h"
#include "exception.h"
EXPORT_API RNG_Int RNG_GetType(void * ptr)
{
	if(!ptr)
	{
		exception_raise("��Ч�Ķ���,��RNG_GetType��");
	}
	return ((RNG_Meta* )ptr)->type;
}

