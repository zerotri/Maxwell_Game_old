#include "SDL.h"

// Color macros from SDL_blit.h
#define RGB_FROM_PIXEL(pixel, fmt, r, g, b)				\
{									\
	r = (((pixel&fmt->Rmask)>>fmt->Rshift)<<fmt->Rloss); 		\
	g = (((pixel&fmt->Gmask)>>fmt->Gshift)<<fmt->Gloss); 		\
	b = (((pixel&fmt->Bmask)>>fmt->Bshift)<<fmt->Bloss); 		\
}

#define PIXEL_FROM_RGB(pixel, fmt, r, g, b)				\
{									\
	pixel = ((r>>fmt->Rloss)<<fmt->Rshift)|				\
		((g>>fmt->Gloss)<<fmt->Gshift)|				\
		((b>>fmt->Bloss)<<fmt->Bshift);				\
}
