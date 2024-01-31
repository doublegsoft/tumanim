/*
**  _                               _           
** | |_ _   _ _ __ ___   __ _ _ __ (_)_ __ ___  
** | __| | | | '_ ` _ \ / _` | '_ \| | '_ ` _ \ 
** | |_| |_| | | | | | | (_| | | | | | | | | | |
**  \__|\__,_|_| |_| |_|\__,_|_| |_|_|_| |_| |_|
**                                              
*/
#ifndef __TUMANIM_RENDERER_H__
#define __TUMANIM_RENDERER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <SDL2/SDL.h>


/*!
** 动画形式显示直线。
*/
void
tuma_line_animate(SDL_Renderer*, int sx, int sy, int dx, int dy, int duration, int width);

#ifdef __cplusplus
}
#endif

#endif // __TUMANIM_RENDERER_H__