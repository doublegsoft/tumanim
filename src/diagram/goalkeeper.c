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

#include "tumanim-type.h"
#include "tumanim-util.h"
#include "tumanim-image.h"
#include "tumanim-renderer.h"

int
tuma_frame_width(void)
{
  return 738;
}

int
tuma_frame_height(void)
{
  return 601;
}

void
tuma_render_and_run(SDL_Renderer* renderer)
{  
  // Create a texture from the image surface
  tuma_image_t* img_field = tuma_image_load("../../img/football-half-field.png");
  tuma_image_t* img_football = tuma_image_load("../../img/football.png");
  tuma_image_t* img_8 = tuma_image_load("../../img/number-8.png");
  tuma_image_t* img_21 = tuma_image_load("../../img/number-21.png");
  tuma_image_t* img_target = tuma_image_load("../../img/target.png");
    
  img_field->w = tuma_frame_width();
  img_field->h = tuma_frame_height();  
  img_football->w = 24;
  img_football->h = 24;
  img_target->w = 32;
  img_target->h = 32;
  
  tuma_image_resize(renderer, img_field, img_field->w, img_field->h);
  tuma_image_resize(renderer, img_football, img_football->w, img_football->h);
  tuma_image_resize(renderer, img_8, 0, 0);
  tuma_image_resize(renderer, img_21, 0, 0);
  tuma_image_resize(renderer, img_target, img_target->w, img_target->h);
  
  SDL_Event event;
  int quit = 0;
  
  int offset_target = 75;
  int direction = 0; // from right to left
  int repeat = 0;
  while (!quit) {
    while (SDL_PollEvent(&event)) 
      if (event.type == SDL_QUIT) 
        quit = 1;

    // Clear the renderer
    SDL_RenderClear(renderer);
    
    SDL_Rect rect_field;
    rect_field.x = 0;
    rect_field.y = 0;
    rect_field.w = img_field->w;
    rect_field.h = img_field->h;
    SDL_RenderCopy(renderer, img_field->tex, NULL, &rect_field);
    
    SDL_Rect rect_football;
    rect_football.x = (img_field->w - img_football->w) / 2;
    rect_football.y = img_field->h - img_football->h - 175;
    rect_football.w = img_football->w;
    rect_football.h = img_football->h;
    SDL_RenderCopy(renderer, img_football->tex, NULL, &rect_football);
    
    SDL_Rect rect_8;
    rect_8.x = (img_field->w - img_football->w) / 2;
    rect_8.y = img_field->h - img_football->h - 175 - img_8->h;
    rect_8.w = img_8->w;
    rect_8.h = img_8->h;
    SDL_RenderCopy(renderer, img_8->tex, NULL, &rect_8);
    
    SDL_Rect rect_21;
    rect_21.x = (img_field->w - img_21->w) / 2;
    rect_21.y = img_field->h - img_21->h - 25;
    rect_21.w = img_21->w;
    rect_21.h = img_21->h;
    SDL_RenderCopy(renderer, img_21->tex, NULL, &rect_21);
    
    SDL_Rect rect_target;
    rect_target.x = (img_field->w - img_21->w) / 2 + offset_target;
    rect_target.y = img_field->h - img_21->h - 25;
    rect_target.w = img_target->w;
    rect_target.h = img_target->h;
    SDL_RenderCopy(renderer, img_target->tex, NULL, &rect_target);
    
    if (repeat <= 3) 
    {
      if (direction)
        offset_target += 3;
      else
        offset_target -= 3;
      
      if (offset_target >= 75) 
        direction = 0;
      if (offset_target <= -75) 
      {
        direction = 1;
        repeat++;
      }     
    }
    else
    {
      int ex_target, ey_target, ex_football, ey_football;
      tuma_point_to_circle_center(rect_football.x + img_football->w / 2, 
                                  rect_football.y + img_football->h / 2, 
                                  rect_target.x + img_target->w / 2, 
                                  rect_target.y + img_target->h / 2, 
                                  img_target->w / 2, 
                                  &ex_target, 
                                  &ey_target);
      tuma_point_to_circle_center(rect_target.x + img_target->w / 2, 
                                  rect_target.y + img_target->h / 2, 
                                  rect_football.x + img_football->w / 2, 
                                  rect_football.y + img_football->h / 2, 
                                  img_football->w / 2, 
                                  &ex_football, 
                                  &ey_football);                        
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                 
                         
      tuma_line_animate(renderer, ex_football, ey_football, ex_target, ey_target, 0, 2);   
       
      int x_close, y_close, ex_21, ey_21;
      tuma_point_to_line_shortest(ex_football, ey_football, ex_target, ey_target, rect_21.x + rect_21.w / 2, rect_21.y + rect_21.h / 2, &x_close, &y_close); 
      
      tuma_point_to_circle_center(x_close, 
                                  y_close, 
                                  rect_21.x + img_21->w / 2, 
                                  rect_21.y + img_21->h / 2, 
                                  img_21->w / 2, 
                                  &ex_21, 
                                  &ey_21);   
      
      tuma_line_animate(renderer, ex_21, ey_21, x_close, y_close, 2000, 2);                                                                              
    }
    

    // Present the renderer
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 30);
  }
}