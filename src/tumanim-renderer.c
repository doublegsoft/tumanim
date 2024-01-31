/*
**  _                               _           
** | |_ _   _ _ __ ___   __ _ _ __ (_)_ __ ___  
** | __| | | | '_ ` _ \ / _` | '_ \| | '_ ` _ \ 
** | |_| |_| | | | | | | (_| | | | | | | | | | |
**  \__|\__,_|_| |_| |_|\__,_|_| |_|_|_| |_| |_|
**                                              
*/
#include <stdlib.h>
#include <math.h>
#include "tumanim-renderer.h"

static double _tuma_line_step_x = 0;
static double _tuma_line_step_y = 0;
static double _tuma_line_total_x = 0;
static double _tuma_line_total_y = 0;

void
tuma_line_animate(SDL_Renderer* renderer, int sx, int sy, int dx, int dy, int duration, int width)
{
  if (duration <= 0)
  {
    for (int i = 0; i < width; i++) 
    {
      SDL_RenderDrawLine(renderer,
                         sx + (i % 2 == 0 ? i : -i), 
                         sy + (i % 2 == 0 ? -i : i), 
                         dx + (i % 2 == 0 ? i : -i),
                         dy + (i % 2 == 0 ? -i : i));   
    }   
    return;
  }
  if (_tuma_line_step_x == 0.0 && _tuma_line_step_y == 0.0)
  {
    _tuma_line_step_x = (double)(dx - sx) / (duration / 30);
    _tuma_line_step_y = (double)(dy - sy) / (duration / 30);
  } 
  for (int i = 0; i < width; i++) 
  {
    SDL_RenderDrawLine(renderer,
                       sx + (i % 2 == 0 ? i : -i), 
                       sy + (i % 2 == 0 ? i : -i), 
                       sx + _tuma_line_total_x + (i % 2 == 0 ? i : -i),
                       sy + _tuma_line_total_y + (i % 2 == 0 ? i : -i));   
  }
  _tuma_line_total_x += _tuma_line_step_x;
  _tuma_line_total_y += _tuma_line_step_y;
  if (dx > sx) 
  {
    if (sx + _tuma_line_total_x >= dx) 
    {
      _tuma_line_step_x = 0;
      _tuma_line_step_y = 0;
      _tuma_line_total_x = 0;
      _tuma_line_total_y = 0;
    }
  }
  else
  {
    if (sx + _tuma_line_total_x <= dx) 
    {
      _tuma_line_step_x = 0;
      _tuma_line_step_y = 0;
      _tuma_line_total_x = 0;
      _tuma_line_total_y = 0;
    }
  }
  
} 