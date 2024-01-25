/*
**  _                               _           
** | |_ _   _ _ __ ___   __ _ _ __ (_)_ __ ___  
** | __| | | | '_ ` _ \ / _` | '_ \| | '_ ` _ \ 
** | |_| |_| | | | | | | (_| | | | | | | | | | |
**  \__|\__,_|_| |_| |_|\__,_|_| |_|_|_| |_| |_|
**                                              
*/
#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "tumanim-image.h"

tuma_image_t* 
tuma_image_load(const char* path)
{
  tuma_image_t* ret = (tuma_image_t*)malloc(sizeof(tuma_image_t));
  
  SDL_Surface* surface = IMG_Load(path);

  if (surface == NULL)
  {
    fprintf(stderr, "error to load image with path: %s\n", path);
    exit(-1);
  }
  
  ret->surf = surface;
  ret->orig_w = surface->w;
  ret->orig_h = surface->h;
  
  ret->x = 0;
  ret->y = 0;
  ret->w = 0;
  ret->h = 0;
  ret->tex = NULL;
  
  return ret;
}
  
void
tuma_image_resize(SDL_Renderer* renderer, tuma_image_t* image, int want_width, int want_height)
{
  SDL_Rect sourceDimensions;
  sourceDimensions.x = 0;
  sourceDimensions.y = 0;
  sourceDimensions.w = image->orig_w;
  sourceDimensions.h = image->orig_h;

  SDL_Rect targetDimensions;
  targetDimensions.x = 0;
  targetDimensions.y = 0;
  targetDimensions.w = want_width;
  targetDimensions.h = want_height;
  
  SDL_Surface* surface = image->surf;

  /*!
  ** create a 32 bits per pixel surface to Blit the image to first, 
  ** before BlitScaled
  **
  ** @see https://stackoverflow.com/questions/33850453/sdl2-blit-scaled-from-a-palettized-8bpp-surface-gives-error-blit-combination/33944312
  */
  SDL_Surface* bpp_surface = SDL_CreateRGBSurface(surface->flags,
                                                    sourceDimensions.w,
                                                    sourceDimensions.h,
                                                    32,
                                                    surface->format->Rmask,
                                                    surface->format->Gmask,
                                                    surface->format->Bmask,
                                                    surface->format->Amask);

  if (SDL_BlitSurface(surface, NULL, bpp_surface, NULL) < 0) 
  {
    printf("Error did not blit surface: %s\n", SDL_GetError());
    return;
  }
  // create another 32 bits per pixel surface are the desired scale
  SDL_Surface* scale_surface = SDL_CreateRGBSurface(bpp_surface->flags,
                                                    targetDimensions.w,
                                                    targetDimensions.h,
                                                    bpp_surface->format->BitsPerPixel,
                                                    bpp_surface->format->Rmask,
                                                    bpp_surface->format->Gmask,
                                                    bpp_surface->format->Bmask,
                                                    bpp_surface->format->Amask);
  
  /*!
  ** 32 bit per pixel surfaces (loaded from the original file) won't scale 
  ** down with BlitScaled, suggestion to first fill the surface 8 and 24 bit 
  ** depth pngs did not require this
  **
  ** @see https://stackoverflow.com/questions/20587999/sdl-blitscaled-doesnt-work
  */
  SDL_FillRect(scale_surface, &targetDimensions, SDL_MapRGBA(scale_surface->format, 255, 0, 0, 255));

  if (SDL_BlitScaled(bpp_surface, NULL, scale_surface, NULL) < 0) 
  {
    printf("Error did not scale surface: %s\n", SDL_GetError());
    SDL_FreeSurface(scale_surface);
    scale_surface = NULL;
  }

  SDL_FreeSurface(bpp_surface);
  bpp_surface = NULL;

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image->surf);

  if (texture == NULL) 
  {
    printf("Error image load: %s\n", SDL_GetError());
    return;
  }
  else 
  {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    image->tex = texture;
  }
}