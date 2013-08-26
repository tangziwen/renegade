#ifndef RNG_EVENT_H
#define RNG_EVENT_H
#include "base.h"


typedef enum
{
	/** @name ASCII mapped keysyms
	 *  The keyboard syms have been cleverly chosen to map to ASCII
	 */
	/*@{*/
	RNGK_UNKNOWN		= 0,
	RNGK_FIRST		= 0,
	RNGK_BACKSPACE		= 8,
	RNGK_TAB		= 9,
	RNGK_CLEAR		= 12,
	RNGK_RETURN		= 13,
	RNGK_PAUSE		= 19,
	RNGK_ESCAPE		= 27,
	RNGK_SPACE		= 32,
	RNGK_EXCLAIM		= 33,
	RNGK_QUOTEDBL		= 34,
	RNGK_HASH		= 35,
	RNGK_DOLLAR		= 36,
	RNGK_AMPERSAND		= 38,
	RNGK_QUOTE		= 39,
	RNGK_LEFTPAREN		= 40,
	RNGK_RIGHTPAREN		= 41,
	RNGK_ASTERISK		= 42,
	RNGK_PLUS		= 43,
	RNGK_COMMA		= 44,
	RNGK_MINUS		= 45,
	RNGK_PERIOD		= 46,
	RNGK_SLASH		= 47,
	RNGK_0			= 48,
	RNGK_1			= 49,
	RNGK_2			= 50,
	RNGK_3			= 51,
	RNGK_4			= 52,
	RNGK_5			= 53,
	RNGK_6			= 54,
	RNGK_7			= 55,
	RNGK_8			= 56,
	RNGK_9			= 57,
	RNGK_COLON		= 58,
	RNGK_SEMICOLON		= 59,
	RNGK_LESS		= 60,
	RNGK_EQUALS		= 61,
	RNGK_GREATER		= 62,
	RNGK_QUESTION		= 63,
	RNGK_AT			= 64,
	/*
	   Skip uppercase letters
	 */
	RNGK_LEFTBRACKET	= 91,
	RNGK_BACKSLASH		= 92,
	RNGK_RIGHTBRACKET	= 93,
	RNGK_CARET		= 94,
	RNGK_UNDERSCORE		= 95,
	RNGK_BACKQUOTE		= 96,
	RNGK_a			= 97,
	RNGK_b			= 98,
	RNGK_c			= 99,
	RNGK_d			= 100,
	RNGK_e			= 101,
	RNGK_f			= 102,
	RNGK_g			= 103,
	RNGK_h			= 104,
	RNGK_i			= 105,
	RNGK_j			= 106,
	RNGK_k			= 107,
	RNGK_l			= 108,
	RNGK_m			= 109,
	RNGK_n			= 110,
	RNGK_o			= 111,
	RNGK_p			= 112,
	RNGK_q			= 113,
	RNGK_r			= 114,
	RNGK_s			= 115,
	RNGK_t			= 116,
	RNGK_u			= 117,
	RNGK_v			= 118,
	RNGK_w			= 119,
	RNGK_x			= 120,
	RNGK_y			= 121,
	RNGK_z			= 122,
	RNGK_DELETE		= 127,
	/* End of ASCII mapped keysyms */
	/*@}*/

	/** @name International keyboard syms */
	/*@{*/
	RNGK_WORLD_0		= 160,		/* 0xA0 */
	RNGK_WORLD_1		= 161,
	RNGK_WORLD_2		= 162,
	RNGK_WORLD_3		= 163,
	RNGK_WORLD_4		= 164,
	RNGK_WORLD_5		= 165,
	RNGK_WORLD_6		= 166,
	RNGK_WORLD_7		= 167,
	RNGK_WORLD_8		= 168,
	RNGK_WORLD_9		= 169,
	RNGK_WORLD_10		= 170,
	RNGK_WORLD_11		= 171,
	RNGK_WORLD_12		= 172,
	RNGK_WORLD_13		= 173,
	RNGK_WORLD_14		= 174,
	RNGK_WORLD_15		= 175,
	RNGK_WORLD_16		= 176,
	RNGK_WORLD_17		= 177,
	RNGK_WORLD_18		= 178,
	RNGK_WORLD_19		= 179,
	RNGK_WORLD_20		= 180,
	RNGK_WORLD_21		= 181,
	RNGK_WORLD_22		= 182,
	RNGK_WORLD_23		= 183,
	RNGK_WORLD_24		= 184,
	RNGK_WORLD_25		= 185,
	RNGK_WORLD_26		= 186,
	RNGK_WORLD_27		= 187,
	RNGK_WORLD_28		= 188,
	RNGK_WORLD_29		= 189,
	RNGK_WORLD_30		= 190,
	RNGK_WORLD_31		= 191,
	RNGK_WORLD_32		= 192,
	RNGK_WORLD_33		= 193,
	RNGK_WORLD_34		= 194,
	RNGK_WORLD_35		= 195,
	RNGK_WORLD_36		= 196,
	RNGK_WORLD_37		= 197,
	RNGK_WORLD_38		= 198,
	RNGK_WORLD_39		= 199,
	RNGK_WORLD_40		= 200,
	RNGK_WORLD_41		= 201,
	RNGK_WORLD_42		= 202,
	RNGK_WORLD_43		= 203,
	RNGK_WORLD_44		= 204,
	RNGK_WORLD_45		= 205,
	RNGK_WORLD_46		= 206,
	RNGK_WORLD_47		= 207,
	RNGK_WORLD_48		= 208,
	RNGK_WORLD_49		= 209,
	RNGK_WORLD_50		= 210,
	RNGK_WORLD_51		= 211,
	RNGK_WORLD_52		= 212,
	RNGK_WORLD_53		= 213,
	RNGK_WORLD_54		= 214,
	RNGK_WORLD_55		= 215,
	RNGK_WORLD_56		= 216,
	RNGK_WORLD_57		= 217,
	RNGK_WORLD_58		= 218,
	RNGK_WORLD_59		= 219,
	RNGK_WORLD_60		= 220,
	RNGK_WORLD_61		= 221,
	RNGK_WORLD_62		= 222,
	RNGK_WORLD_63		= 223,
	RNGK_WORLD_64		= 224,
	RNGK_WORLD_65		= 225,
	RNGK_WORLD_66		= 226,
	RNGK_WORLD_67		= 227,
	RNGK_WORLD_68		= 228,
	RNGK_WORLD_69		= 229,
	RNGK_WORLD_70		= 230,
	RNGK_WORLD_71		= 231,
	RNGK_WORLD_72		= 232,
	RNGK_WORLD_73		= 233,
	RNGK_WORLD_74		= 234,
	RNGK_WORLD_75		= 235,
	RNGK_WORLD_76		= 236,
	RNGK_WORLD_77		= 237,
	RNGK_WORLD_78		= 238,
	RNGK_WORLD_79		= 239,
	RNGK_WORLD_80		= 240,
	RNGK_WORLD_81		= 241,
	RNGK_WORLD_82		= 242,
	RNGK_WORLD_83		= 243,
	RNGK_WORLD_84		= 244,
	RNGK_WORLD_85		= 245,
	RNGK_WORLD_86		= 246,
	RNGK_WORLD_87		= 247,
	RNGK_WORLD_88		= 248,
	RNGK_WORLD_89		= 249,
	RNGK_WORLD_90		= 250,
	RNGK_WORLD_91		= 251,
	RNGK_WORLD_92		= 252,
	RNGK_WORLD_93		= 253,
	RNGK_WORLD_94		= 254,
	RNGK_WORLD_95		= 255,		/* 0xFF */
	/*@}*/

	/** @name Numeric keypad */
	/*@{*/
	RNGK_KP0		= 256,
	RNGK_KP1		= 257,
	RNGK_KP2		= 258,
	RNGK_KP3		= 259,
	RNGK_KP4		= 260,
	RNGK_KP5		= 261,
	RNGK_KP6		= 262,
	RNGK_KP7		= 263,
	RNGK_KP8		= 264,
	RNGK_KP9		= 265,
	RNGK_KP_PERIOD		= 266,
	RNGK_KP_DIVIDE		= 267,
	RNGK_KP_MULTIPLY	= 268,
	RNGK_KP_MINUS		= 269,
	RNGK_KP_PLUS		= 270,
	RNGK_KP_ENTER		= 271,
	RNGK_KP_EQUALS		= 272,
	/*@}*/

	/** @name Arrows + Home/End pad */
	/*@{*/
	RNGK_UP			= 273,
	RNGK_DOWN		= 274,
	RNGK_RIGHT		= 275,
	RNGK_LEFT		= 276,
	RNGK_INSERT		= 277,
	RNGK_HOME		= 278,
	RNGK_END		= 279,
	RNGK_PAGEUP		= 280,
	RNGK_PAGEDOWN		= 281,
	/*@}*/

	/** @name Function keys */
	/*@{*/
	RNGK_F1			= 282,
	RNGK_F2			= 283,
	RNGK_F3			= 284,
	RNGK_F4			= 285,
	RNGK_F5			= 286,
	RNGK_F6			= 287,
	RNGK_F7			= 288,
	RNGK_F8			= 289,
	RNGK_F9			= 290,
	RNGK_F10		= 291,
	RNGK_F11		= 292,
	RNGK_F12		= 293,
	RNGK_F13		= 294,
	RNGK_F14		= 295,
	RNGK_F15		= 296,
	/*@}*/

	/** @name Key state modifier keys */
	/*@{*/
	RNGK_NUMLOCK		= 300,
	RNGK_CAPSLOCK		= 301,
	RNGK_SCROLLOCK		= 302,
	RNGK_RSHIFT		= 303,
	RNGK_LSHIFT		= 304,
	RNGK_RCTRL		= 305,
	RNGK_LCTRL		= 306,
	RNGK_RALT		= 307,
	RNGK_LALT		= 308,
	RNGK_RMETA		= 309,
	RNGK_LMETA		= 310,
	RNGK_LSUPER		= 311,		/**< Left "Windows" key */
	RNGK_RSUPER		= 312,		/**< Right "Windows" key */
	RNGK_MODE		= 313,		/**< "Alt Gr" key */
	RNGK_COMPOSE		= 314,		/**< Multi-key compose key */
	/*@}*/

	/** @name Miscellaneous function keys */
	/*@{*/
	RNGK_HELP		= 315,
	RNGK_PRINT		= 316,
	RNGK_SYSREQ		= 317,
	RNGK_BREAK		= 318,
	RNGK_MENU		= 319,
	RNGK_POWER		= 320,		/**< Power Macintosh power key */
	RNGK_EURO		= 321,		/**< Some european keyboards */
	RNGK_UNDO		= 322,		/**< Atari keyboard has Undo */
	/*@}*/

	/* Add any other keys here */

	RNGK_LAST
} RNG_Key;

//获取某一键位的状态
//
//如果某一键位被按下,就返回1
//否则返回0
EXPORT_API RNG_Int RNG_GetKeyState(RNG_Key key_code);

extern void (*RNG_OnMouseDownHandler)(RNG_Vector pos);

extern void (*RNG_OnMouseRelaeseHandler)(RNG_Vector pos);
//鼠标状态
typedef enum
{
	RNG_MOUSE_NONE=0,
	RNG_MOUSE_LEFT,
	RNG_MOUSE_RIGHT,
} RNG_MouseState;
//获得鼠标某个键是否被按下
//
//返回当前被按下的鼠标按键
//abs_pos 鼠标的绝对坐标
//re_pos 鼠标的相对坐标
EXPORT_API RNG_MouseState RNG_GetMouseState(RNG_Vector * abs_pos,RNG_Vector * re_pos);
#endif
