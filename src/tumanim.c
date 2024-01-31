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
#include "tumanim-type.h"

int main() 
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }
  
  int imgFlags = IMG_INIT_PNG;
  IMG_Init(imgFlags);
  
  // Create a window
  SDL_Window* window = SDL_CreateWindow("Tumanim", 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        tuma_frame_width(), 
                                        tuma_frame_height(),
                                        SDL_WINDOW_SHOWN);
                                      
  if (window == NULL) 
  {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  
  // Create a renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) 
  {
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  
  tuma_render_and_run(renderer);

  // Clean up
  // SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
