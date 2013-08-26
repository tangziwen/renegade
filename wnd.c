#include "wnd.h"
#include <GL/glew.h>
#include "SOIL.h"
#include "exception.h"
#include "scene.h"
#include "event.h"
#define MAX_FPS 60
//标记窗体是否已经被建立
static char windows_is_create= 0;

extern RNG_Scene * major_scene;
static void (*renderCallBack)()=NULL;
//记录振渲染周期
static RNG_Real time_duration=0.016666666666667;

//标记窗体是否为全屏
static RNG_BOOL is_fullscreen=RNG_FALSE;
GLuint current_texture_ID;
static GLuint tex_2d =0;
extern int shader_program=0;
static void printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}

static void printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}
static char * load_file(const char * file_name)
{
	FILE * buffer_file;
	buffer_file= fopen(file_name,"rb");
	fseek(buffer_file,0,SEEK_END);
	int buffer_size =ftell(buffer_file);
	rewind(buffer_file);
	char * buffer;
	buffer = (char*)malloc((buffer_size+1)*sizeof(char));
	{
		int i;
		for(i=0; !feof(buffer_file); i++)
		{
			fread(buffer+i,sizeof(char),1,buffer_file);
			if(buffer[i]=='\r')
			{
				buffer[i]=' ';
			}
		}
	}
	buffer[buffer_size]='\0';
	fclose(buffer_file);
	return buffer;
}
static void shader_config()
{
	char * vertex_file=NULL;
	char * fragment_file=NULL;
	int v=glCreateShader(GL_VERTEX_SHADER);
	int f=glCreateShader(GL_FRAGMENT_SHADER);
	vertex_file=load_file("./v.glsl");
	fragment_file=load_file("./f.glsl");
	glShaderSource(v, 1, &vertex_file, NULL);


	glShaderSource(f, 1, &fragment_file, NULL);
	glCompileShader(v);
	glCompileShader(f);
	int success=GL_TRUE;
	glGetShaderiv(v, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		printf("vertex shader:\n");
		printShaderInfoLog(v);
	}
	glGetShaderiv(f, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		printf("fragment shader:\n");
		printShaderInfoLog(f);
	}
	shader_program=glCreateProgram();
	glAttachShader(shader_program, f);
	glAttachShader(shader_program,v);
	glLinkProgram(shader_program);
	glUseProgram(shader_program);
}


static void blend_configure()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
}


//初始化opengl相关的属性
static void setup_opengl( int width, int height )
{
	glewInit();
	blend_configure();
	shader_config();
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluOrtho2D(0,width,0,height);


	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}



//创建一个窗体
//
//title:窗体的标题字符串
//width:窗体的宽度
//height:窗体的高度
LOCAL_API void RNG_WndCreate(const char * title,RNG_Int width,RNG_Int height,RNG_BOOL fullscreen)
{
	if(!windows_is_create)
	{
		windows_is_create=1;
		exception_raise("窗体已经被建立,在RNG_WndCreate中");
	}
	else
	{
		return ;
	}

	const SDL_VideoInfo* info = SDL_GetVideoInfo( );
	int bpp = info->vfmt->BitsPerPixel;


	is_fullscreen=fullscreen;
	int flags =0;
	if(is_fullscreen==RNG_TRUE)
	{
		flags = SDL_OPENGL|SDL_FULLSCREEN;
	}
	else
	{
		flags = SDL_OPENGL;
	}
	printf("the width %d ,the height %d \n",width,height);
	if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 )
	{
		exception_raise("窗口设置失败,在RNG_WndCreate中");
	}
	setup_opengl(width,height);

	SDL_WM_SetCaption(title,NULL);

}



//开始渲染窗体
//
//这里面包含了一个循环,将不断的渲染窗体,直至引擎被终结
EXPORT_API void RNG_WndRender(void(* func)())
{
	static RNG_Int   time_old;
	RNG_Int   time_delta=0;
	int running=1;
	SDL_Event event;
	SDL_ShowCursor(1);
	renderCallBack=func;
	time_old=SDL_GetTicks();
	//主循环
	while( running )
	{
		//事件处理
		while( SDL_PollEvent( &event ) )
		{
			switch(event.type)      //处理取到的消息，判断消息类型
			{
			case SDL_QUIT:          //如果是退出事件请求，例如点击窗口的关闭按钮
				running = 0;            //退出循环
				break;
			default:
				break;
			}
		}
		//背景色
		glClear( GL_COLOR_BUFFER_BIT );
		SceneRender(major_scene);
		RNG_Vector abs_pos;
		int mouse_state=RNG_GetMouseState(&abs_pos,NULL);
		if(mouse_state==RNG_MOUSE_LEFT ||mouse_state==RNG_MOUSE_RIGHT )
		{
			RNG_SceneTriggerTouch(major_scene,abs_pos);
		}
		else
		{
			SceneTriggerRealease(major_scene,abs_pos);
		}
		if(renderCallBack)
		{
			renderCallBack();
		}

		RNG_Vector mouse_pos;
		int mouse_flag =RNG_GetMouseState(&mouse_pos,NULL);
		switch(mouse_flag)
		{
		case RNG_MOUSE_NONE:
			if(RNG_OnMouseRelaeseHandler)
			{
				RNG_OnMouseRelaeseHandler(mouse_pos);
			}
			break;
		case RNG_MOUSE_LEFT:
			if(RNG_OnMouseDownHandler)
			{
				RNG_OnMouseDownHandler(mouse_pos);
			}
			break;
		}
		//交换缓冲区
		SDL_GL_SwapBuffers( );
		RNG_Int time_new=SDL_GetTicks();
		time_delta=time_new-time_old;
		time_old=time_new;
		time_duration= (1.0*time_delta)/1000;
		if((1.0/MAX_FPS) >time_duration)
		{
			SDL_Delay(((1.0/MAX_FPS) -time_duration)*1000);
			time_duration=(1.0/MAX_FPS);
		}
		time_old=SDL_GetTicks();
	}
}

//获取上一帧的渲染周期
EXPORT_API RNG_Real RNG_GetDuration()
{
	return time_duration;
}

//设置窗体的背景色
//
//ptr 指向一个颜色对象的指针
EXPORT_API void RNG_WndSetBG(RNG_Color  color)
{
	glClearColor(color.red,color.green,color.blue,color.alpha);
}


//设置窗体全屏与否
//
//fullscreen:
//	RNG_TRUE-全屏
//	RNG_FALSE-窗体化
EXPORT_API void RNG_WndSetFullscreen(RNG_BOOL fullscreen )
{
	if(is_fullscreen!=fullscreen)
	{
		SDL_Surface * surface= SDL_GetVideoSurface();
		int flags=surface->flags;
		flags ^=SDL_FULLSCREEN;
		SDL_SetVideoMode(surface->w,surface->h,0,flags);
	}
	is_fullscreen=fullscreen;
}

//设置窗体的新分辨率
//
//在窗体模式下,分辨率就等同于窗体的尺寸
EXPORT_API void RNG_WndSetRes(int width ,int height )
{
	SDL_SetVideoMode(width,height,0,SDL_GetVideoSurface()->flags);
}


//设置窗体的标题
//
//new_title:窗体新标题的字符串表示
EXPORT_API void RNG_WndSetTitle(const char * new_title )
{
	SDL_WM_SetCaption(new_title,NULL);
}

//设置在可视区域内是否显示鼠标
//
//is_show::
//	RNG_TRUE显示
//	RNG_FALSE不显示
EXPORT_API void RNG_WndSetCursor(RNG_BOOL is_show)
{
	SDL_ShowCursor(is_show);
}

EXPORT_API void RNG_SetCallBack(void (* func)() )
{
	renderCallBack=func;
}
