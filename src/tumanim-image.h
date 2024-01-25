/*
**  _                               _           
** | |_ _   _ _ __ ___   __ _ _ __ (_)_ __ ___  
** | __| | | | '_ ` _ \ / _` | '_ \| | '_ ` _ \ 
** | |_| |_| | | | | | | (_| | | | | | | | | | |
**  \__|\__,_|_| |_| |_|\__,_|_| |_|_|_| |_| |_|
**                                              
*/
#ifndef __TUMANIM_IMAGE_H__
#define __TUMANIM_IMAGE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <SDL2/SDL.h>

typedef struct tuma_image_s
{
  int           x;
  int           y;
  int           w;
  int           h;
    
  int           orig_w;
  int           orig_h;
  SDL_Surface*  surf;
  SDL_Texture*  tex;
}
tuma_image_t;

void
tuma_calc_layout();

tuma_image_t*
tuma_image_load(const char* path);

void
tuma_image_resize(SDL_Renderer* renderer, tuma_image_t* image, int width, int height);

#ifdef __cplusplus
}
#endif

#endif // __TUMANIM_IMAGE_H__