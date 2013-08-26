#include "color.h"
#include "type.h"
#include "exception.h"

EXPORT_API RNG_Color RNG_Col3(RNG_Real red,RNG_Real green,RNG_Real blue)
{
	RNG_Color color;
	color.red=red;
	color.green=green;
	color.blue=blue;
	color.alpha=1;
	return color;
}


EXPORT_API RNG_Color RNG_Col4(RNG_Real red,RNG_Real green,RNG_Real blue,RNG_Real alpha)
{
	RNG_Color color;
	color.red=red;
	color.green=green;
	color.blue=blue;
	color.alpha=alpha;
	return color;
}
EXPORT_API void RNG_ColPrint(RNG_Color color)
{
	printf("R:%g G:%g B:%g A:%g\n",color.red,color.green,color.blue,color.alpha);
}
