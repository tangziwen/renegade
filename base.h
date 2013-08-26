#ifndef RNG_BASE_H
#define RNG_BASE_H



#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "GL/glew.h"

#define LOCAL_API
#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#if define _LINUX || define _UNIX
#define EXPORT_API __attribute__ ((visibility("hidden")))
#endif
#endif




#if __STDC_VERSION__>=199901L
#include <stdbool.h>
#define RNG_TRUE true
#define RNG_FALSE false
typedef bool RNG_BOOL;
#else
typedef char RNG_BOOL;
#define RNG_TRUE 1
#define RNG_FALSE 0
#endif


typedef unsigned char RNG_Byte;

typedef int RNG_Int;

typedef double RNG_Real;

typedef struct
{
	RNG_Real x;
	RNG_Real y;
} RNG_Vector;

#endif
