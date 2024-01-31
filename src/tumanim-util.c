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
#include "tumanim-util.h"

void
tuma_point_to_circle_center(int sx, int sy, int tx, int ty, int radius, int* ex, int* ey)
{
  int a = abs(tx - sx);
  int b = abs(ty - sy);
  int c = sqrt(a * a + b * b);
  if (sx > tx) 
    *ex = radius * a / c + tx;
  else
    *ex = tx - radius * a / c;
  if (sy < ty)
    *ey = ty - radius * b / c ;  
  else
    *ey = ty + radius * b / c ;  
}
    
void
tuma_point_to_line_shortest(int sx, int sy, int tx, int ty, int px, int py, int* x, int* y)
{
  double x0 = px;
  double y0 = py;
  double x1 = sx;
  double y1 = sy;
  double x2 = tx;
  double y2 = ty;
  double t = ((x0 - x1) * (x2 - x1) + (y0 - y1) * (y2 - y1)) / ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

  *x = x1 + t * (x2 - x1);
  *y = y1 + t * (y2 - y1);
}